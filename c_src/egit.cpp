#include <stdio.h>
#include <cstring>
#include <cassert>
#include <memory>
#include <tuple>
#include <vector>
#include <atomic>
#include <git2.h>
#include "egit_utils.hpp"
#include "egit_cat_file.hpp"

static ErlNifResourceType* GIT_REPO_RESOURCE;

struct GitRepoPtr {
  static GitRepoPtr* create(git_repository* p) {
    auto rp = static_cast<GitRepoPtr*>(enif_alloc_resource(GIT_REPO_RESOURCE, sizeof(GitRepoPtr)));
    if (!rp) [[unlikely]]
      return nullptr;

    new (rp) GitRepoPtr(p);
    return rp;
  }

  ~GitRepoPtr() { if (m_ptr) { git_repository_free(m_ptr); m_ptr = nullptr; } }

  git_repository const* get() const { return m_ptr; }
  git_repository*       get()       { return m_ptr; }

private:
  GitRepoPtr(git_repository* p) : m_ptr(p) {}

  git_repository* m_ptr;
};

struct GitCommit {
  explicit GitCommit(git_commit* p = nullptr) : m_ptr(p) {}
  ~GitCommit() {
    if (m_ptr) {
      git_commit_free(m_ptr);
      m_ptr = nullptr;
    }
  }

  git_commit const* get() const { return m_ptr; }
  git_commit*       get()       { return m_ptr; }
  git_commit**      ptr()       { assert(!m_ptr); return &m_ptr; }

  git_commit const* operator->() const { return m_ptr; }
private:
  git_commit* m_ptr;
};

static ERL_NIF_TERM to_monitored_resource(ErlNifEnv* env, git_repository* p)
{
  ErlNifMonitor mon;
  ErlNifPid pid;
  enif_self(env, &pid);

  auto rp = GitRepoPtr::create(p);

  if (!rp) [[unlikely]] {
    assert(p);
    git_repository_free(p);
    return enif_raise_exception(env, ATOM_ENOMEM);
  }

  auto result = enif_monitor_process(env, rp, &pid, &mon);

  if (result != 0) [[unlikely]] {
    if (result > 0) {
      // Process no longer alive
      return enif_raise_exception(env, ATOM_ENOPROCESS);
    } else {
      assert(result < 0);
      // mon callback is not specified
      return enif_raise_exception(env, ATOM_ENOCALLBACK);
    }
  }

  ERL_NIF_TERM resource = enif_make_resource(env, (void*)rp);
  enif_release_resource((void*)rp); // Grant ownership to the resource

  return resource;
}

static ERL_NIF_TERM oid_to_bin(ErlNifEnv* env, git_oid const* oid, size_t len = GIT_OID_SHA1_HEXSIZE)
{
  char buf[GIT_OID_SHA1_HEXSIZE+1];
  len = std::min(len, sizeof(buf)-1);
  git_oid_tostr(buf, len, oid);
  return make_binary(env, buf);
}

static ERL_NIF_TERM
commit_lookup_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  assert(argc == 3);

  GitRepoPtr* repo;
  if (!enif_get_resource(env, argv[0], GIT_REPO_RESOURCE, (void**)&repo)) [[unlikely]]
    return enif_make_badarg(env);

  ErlNifBinary bsha;

  if (!enif_inspect_binary(env, argv[1], &bsha)) [[unlikely]]
    return enif_make_badarg(env);

  std::string sha((char*)bsha.data, bsha.size);

  git_oid oid;
  if (git_oid_fromstr(&oid, sha.c_str()) < 0)
    return ATOM_NIL;

  std::vector<ERL_NIF_TERM> keys, vals;

  auto push = [&keys, &vals, env](ERL_NIF_TERM key, const char* val) {
    keys.push_back(key);
    vals.push_back(val ? make_binary(env, val) : ATOM_NIL);
  };

  auto pushi = [&keys, &vals, env](ERL_NIF_TERM key, int64_t val) {
    keys.push_back(key);
    vals.push_back(enif_make_int64(env, val));
  };

  auto pusht = [&keys, &vals, env](ERL_NIF_TERM key, ERL_NIF_TERM val) {
    keys.push_back(key);
    vals.push_back(val);
  };

  auto push_sign = [&, env](ERL_NIF_TERM key, git_signature const* val) {
    keys.push_back(key);
    vals.push_back(enif_make_tuple2(env, make_binary(env, val->name), make_binary(env, val->email)));
  };

  // Smart pointer that will automatically free the commit object
  GitCommit pcommit;

  if (git_commit_lookup(pcommit.ptr(), repo->get(), &oid) < 0)
    return raise_error(env, "Failed to find git commit " + sha); 

  auto commit = pcommit.get();
 
  ERL_NIF_TERM  head, list = argv[2];

  while (enif_get_list_cell(env, list, &head, &list)) {
    if      (enif_is_identical(head, ATOM_ENCODING))      push(ATOM_ENCODING,       git_commit_message_encoding(commit));
    else if (enif_is_identical(head, ATOM_MESSAGE))       push(ATOM_MESSAGE,        git_commit_message         (commit));
    else if (enif_is_identical(head, ATOM_SUMMARY))       push(ATOM_SUMMARY,        git_commit_summary         (commit));
    else if (enif_is_identical(head, ATOM_TIME))          pushi(ATOM_TIME,          git_commit_time            (commit));
    else if (enif_is_identical(head, ATOM_TIME_OFFSET))   pushi(ATOM_TIME_OFFSET,   git_commit_time_offset     (commit) * 60L);
    else if (enif_is_identical(head, ATOM_COMMITTER))     push_sign(ATOM_COMMITTER, git_commit_committer       (commit));
    else if (enif_is_identical(head, ATOM_AUTHOR))        push_sign(ATOM_AUTHOR,    git_commit_author          (commit));
    else if (enif_is_identical(head, ATOM_HEADER))        push(ATOM_HEADER,         git_commit_raw_header      (commit));
    else if (enif_is_identical(head, ATOM_TREE_ID))       pusht(ATOM_TREE_ID,       oid_to_bin(env, git_commit_tree_id(commit)));
    else [[unlikely]]
      return enif_make_badarg(env);
  }

  ERL_NIF_TERM map;
  if (!enif_make_map_from_arrays(env, &keys.front(), &vals.front(), keys.size(), &map)) [[unlikely]]
    return enif_raise_exception(env, ATOM_ENOMEM);

  return map;
}

static ERL_NIF_TERM clone_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  ErlNifBinary url, path;
  assert(argc == 2);

  if (!enif_inspect_binary(env, argv[0], &url) ||
      !enif_inspect_binary(env, argv[1], &path)) [[unlikely]]
    return enif_make_badarg(env);

  std::string surl((char*)url.data,   url.size);
  std::string spath((char*)path.data, path.size);

  git_repository* p{};

  if (git_clone(&p, surl.c_str(), spath.c_str(), nullptr) < 0) [[unlikely]]
    return raise_error(env, "Failed to clone git repo " + surl); 

  return to_monitored_resource(env, p);
}

static ERL_NIF_TERM open_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  ErlNifBinary path;
  assert(argc == 1);

  if (!enif_inspect_binary(env, argv[0], &path)) [[unlikely]]
    return enif_make_badarg(env);

  std::string spath((char*)path.data, path.size);

  git_repository* p{};

  if (git_repository_open(&p, spath.c_str()) < 0) [[unlikely]]
    return raise_error(env, "Failed to open git repo " + spath); 

  return to_monitored_resource(env, p);
}

static ERL_NIF_TERM fetch_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  GitRepoPtr* repo;
  if (!enif_get_resource(env, argv[0], GIT_REPO_RESOURCE, (void**)&repo)) [[unlikely]]
    return enif_make_badarg(env);

  const char* fetch_or_pull = nullptr;

  if (enif_is_identical(argv[1], ATOM_FETCH))
    fetch_or_pull = "fetch";
  else if (enif_is_identical(argv[1], ATOM_PULL))
    fetch_or_pull = "pull";
  else
    return enif_make_badarg(env);

  std::string remote_name("origin");

  if (argc > 2) {
    ErlNifBinary bin;
    if (!enif_inspect_binary(env, argv[2], &bin)) [[unlikely]]
      return enif_make_badarg(env);

    remote_name = std::string((char*)bin.data, bin.size);
  }

  git_remote* remote;

  if (git_remote_lookup(&remote, repo->get(), remote_name.c_str()) < 0)
    return make_error(env, "Failed to lookup remote " + remote_name);
  if (git_remote_fetch(remote,
                       NULL,               // refspecs, NULL to use the configured ones
                       NULL,               // options, empty for defaults
                       fetch_or_pull) < 0) // reflog mesage, "fetch" (or NULL) or "pull"
    return make_error(env, "Failed to fetch from " + remote_name);

  return ATOM_OK;
}

static ERL_NIF_TERM cat_file_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  assert(argc == 3);

  GitRepoPtr* repo;
  if (!enif_get_resource(env, argv[0], GIT_REPO_RESOURCE, (void**)&repo)) [[unlikely]]
    return enif_make_badarg(env);

  ErlNifBinary bin;
  if (!enif_inspect_binary(env, argv[1], &bin) || bin.size == 0) [[unlikely]]
    return enif_make_badarg(env);

  std::string filename((char*)bin.data, bin.size);

  return cat_file(env, repo->get(), filename, argv[2]);
}

static void resource_dtor(ErlNifEnv* env, void* arg)
{
  assert(arg);
  //fprintf(stderr, "--> Releasing resource %p\r\n", arg);
  static_cast<GitRepoPtr*>(arg)->~GitRepoPtr();
}

static void resource_down(ErlNifEnv* env, void* obj, ErlNifPid*, ErlNifMonitor*)
{
  //fprintf(stderr, "--> Decrement resource ref %p\r\n", obj);
  enif_release_resource(obj);
}

static int load(ErlNifEnv* env, void** priv_data, ERL_NIF_TERM load_info)
{
  init_atoms(env);

  auto flags                 = (ErlNifResourceFlags)(ERL_NIF_RT_CREATE | ERL_NIF_RT_TAKEOVER);
  ErlNifResourceTypeInit rti = {.dtor = &resource_dtor, .down = &resource_down};
  GIT_REPO_RESOURCE          = enif_open_resource_type_x(env, "git_repo_resource", &rti, flags, nullptr);

  git_libgit2_init();

  return 0;
}

static int upgrade(ErlNifEnv* env, void** priv_data, void** old_priv_data, ERL_NIF_TERM load_info) {
  //if (old_priv_data)
  //  enif_release_resource(old_priv_data);
  return 0;
}

static ErlNifFunc egit_funcs[] =
{
  {"clone",         2, clone_nif,         ERL_NIF_DIRTY_JOB_IO_BOUND},
  {"open",          1, open_nif,          ERL_NIF_DIRTY_JOB_IO_BOUND},
  {"fetch_or_pull", 2, fetch_nif,         ERL_NIF_DIRTY_JOB_IO_BOUND},
  {"fetch_or_pull", 3, fetch_nif,         ERL_NIF_DIRTY_JOB_IO_BOUND},
  {"cat_file",      3, cat_file_nif,      ERL_NIF_DIRTY_JOB_IO_BOUND},
  {"commit_lookup", 3, commit_lookup_nif, 0},
};

ERL_NIF_INIT(egit, egit_funcs, load, NULL, upgrade, NULL);