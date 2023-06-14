#pragma once

static ERL_NIF_TERM ATOM_ABBREV;
static ERL_NIF_TERM ATOM_ADD;
static ERL_NIF_TERM ATOM_ADDED;
static ERL_NIF_TERM ATOM_ALL;
static ERL_NIF_TERM ATOM_ANCESTOR;
static ERL_NIF_TERM ATOM_ANY;
static ERL_NIF_TERM ATOM_APP;
static ERL_NIF_TERM ATOM_AUTHOR;
static ERL_NIF_TERM ATOM_BADARG;
static ERL_NIF_TERM ATOM_BARE;
static ERL_NIF_TERM ATOM_BLOB;
static ERL_NIF_TERM ATOM_CHMOD_CALLS;
static ERL_NIF_TERM ATOM_COMMIT;
static ERL_NIF_TERM ATOM_COMMITS;
static ERL_NIF_TERM ATOM_COMMITTER;
static ERL_NIF_TERM ATOM_CONFLICT;
static ERL_NIF_TERM ATOM_CREATE;
static ERL_NIF_TERM ATOM_CTIME;
static ERL_NIF_TERM ATOM_DATA;
static ERL_NIF_TERM ATOM_DATE_ORDER;
static ERL_NIF_TERM ATOM_DEFAULT;
static ERL_NIF_TERM ATOM_DELETE;
static ERL_NIF_TERM ATOM_DIR;
static ERL_NIF_TERM ATOM_DRY_RUN;
static ERL_NIF_TERM ATOM_ENCODING;
static ERL_NIF_TERM ATOM_ENOCALLBACK;
static ERL_NIF_TERM ATOM_ENOMEM;
static ERL_NIF_TERM ATOM_ENOPROCESS;
static ERL_NIF_TERM ATOM_ERROR;
static ERL_NIF_TERM ATOM_FALSE;
static ERL_NIF_TERM ATOM_FETCH;
static ERL_NIF_TERM ATOM_FIELDS;
static ERL_NIF_TERM ATOM_FILEM;
static ERL_NIF_TERM ATOM_FILES;
static ERL_NIF_TERM ATOM_FORCE;
static ERL_NIF_TERM ATOM_FROM;
static ERL_NIF_TERM ATOM_FULLNAME;
static ERL_NIF_TERM ATOM_GLOBAL;
static ERL_NIF_TERM ATOM_HEADER;
static ERL_NIF_TERM ATOM_HIGHEST;
static ERL_NIF_TERM ATOM_LIMIT;
static ERL_NIF_TERM ATOM_LINES;
static ERL_NIF_TERM ATOM_LIST;
static ERL_NIF_TERM ATOM_LOCAL;
static ERL_NIF_TERM ATOM_MERGE_BASE;
static ERL_NIF_TERM ATOM_MESSAGE;
static ERL_NIF_TERM ATOM_MKDIR_CALLS;
static ERL_NIF_TERM ATOM_MODE;
static ERL_NIF_TERM ATOM_MTIME;
static ERL_NIF_TERM ATOM_NAME;
static ERL_NIF_TERM ATOM_NEW_NAME;
static ERL_NIF_TERM ATOM_NIL;
static ERL_NIF_TERM ATOM_NONE;
static ERL_NIF_TERM ATOM_NORMAL;
static ERL_NIF_TERM ATOM_NOT_FOUND;
static ERL_NIF_TERM ATOM_NOT;
static ERL_NIF_TERM ATOM_OBJECT;
static ERL_NIF_TERM ATOM_OID;
static ERL_NIF_TERM ATOM_OK;
static ERL_NIF_TERM ATOM_OURS;
static ERL_NIF_TERM ATOM_OVERWRITE;
static ERL_NIF_TERM ATOM_PARENTS;
static ERL_NIF_TERM ATOM_PATH;
static ERL_NIF_TERM ATOM_PATTERN;
static ERL_NIF_TERM ATOM_PERF;
static ERL_NIF_TERM ATOM_PULL;
static ERL_NIF_TERM ATOM_PUSH;
static ERL_NIF_TERM ATOM_REMOTE;
static ERL_NIF_TERM ATOM_RENAME;
static ERL_NIF_TERM ATOM_REVERSE;
static ERL_NIF_TERM ATOM_SETURL;
static ERL_NIF_TERM ATOM_SHA;
static ERL_NIF_TERM ATOM_SIZE;
static ERL_NIF_TERM ATOM_STAGE;
static ERL_NIF_TERM ATOM_STAT_CALLS;
static ERL_NIF_TERM ATOM_SUMMARY;
static ERL_NIF_TERM ATOM_SYSTEM;
static ERL_NIF_TERM ATOM_TAG;
static ERL_NIF_TERM ATOM_TAGGER;
static ERL_NIF_TERM ATOM_TARGET;
static ERL_NIF_TERM ATOM_THEIRS;
static ERL_NIF_TERM ATOM_TIME_OFFSET;
static ERL_NIF_TERM ATOM_TIME;
static ERL_NIF_TERM ATOM_TO;
static ERL_NIF_TERM ATOM_TOPO_ORDER;
static ERL_NIF_TERM ATOM_TOTAL_STEPS;
static ERL_NIF_TERM ATOM_TREE_ID;
static ERL_NIF_TERM ATOM_TREE;
static ERL_NIF_TERM ATOM_TRUE;
static ERL_NIF_TERM ATOM_TYPE;
static ERL_NIF_TERM ATOM_UPDATE;
static ERL_NIF_TERM ATOM_VERBOSE;
static ERL_NIF_TERM ATOM_XDG;

inline void init_atoms(ErlNifEnv* env)
{
  ATOM_ABBREV      = enif_make_atom(env, "abbrev");
  ATOM_ADD         = enif_make_atom(env, "add");
  ATOM_ADDED       = enif_make_atom(env, "added");
  ATOM_ALL         = enif_make_atom(env, "all");
  ATOM_ANCESTOR    = enif_make_atom(env, "ancestor");
  ATOM_ANY         = enif_make_atom(env, "any");
  ATOM_APP         = enif_make_atom(env, "app");
  ATOM_AUTHOR      = enif_make_atom(env, "author");
  ATOM_BADARG      = enif_make_atom(env, "badarg");
  ATOM_BARE        = enif_make_atom(env, "bare");
  ATOM_BLOB        = enif_make_atom(env, "blob");
  ATOM_CHMOD_CALLS = enif_make_atom(env, "chmod_calls");
  ATOM_COMMIT      = enif_make_atom(env, "commit");
  ATOM_COMMITS     = enif_make_atom(env, "commits");
  ATOM_COMMITTER   = enif_make_atom(env, "committer");
  ATOM_CONFLICT    = enif_make_atom(env, "conflict");
  ATOM_CREATE      = enif_make_atom(env, "create");
  ATOM_CTIME       = enif_make_atom(env, "ctime");
  ATOM_DATA        = enif_make_atom(env, "data");
  ATOM_DATE_ORDER  = enif_make_atom(env, "date_order");
  ATOM_DEFAULT     = enif_make_atom(env, "default");
  ATOM_DELETE      = enif_make_atom(env, "delete");
  ATOM_DIR         = enif_make_atom(env, "dir");
  ATOM_DRY_RUN     = enif_make_atom(env, "dry_run");
  ATOM_ENCODING    = enif_make_atom(env, "encoding");
  ATOM_ENOCALLBACK = enif_make_atom(env, "enocallback");
  ATOM_ENOMEM      = enif_make_atom(env, "enomem");
  ATOM_ENOPROCESS  = enif_make_atom(env, "enoprocess");
  ATOM_ERROR       = enif_make_atom(env, "error");
  ATOM_FALSE       = enif_make_atom(env, "false");
  ATOM_FETCH       = enif_make_atom(env, "fetch");
  ATOM_FIELDS      = enif_make_atom(env, "fields");
  ATOM_FILEM       = enif_make_atom(env, "filem");
  ATOM_FILES       = enif_make_atom(env, "files");
  ATOM_FORCE       = enif_make_atom(env, "force");
  ATOM_FROM        = enif_make_atom(env, "from");
  ATOM_FULLNAME    = enif_make_atom(env, "fullname");
  ATOM_GLOBAL      = enif_make_atom(env, "global");
  ATOM_HEADER      = enif_make_atom(env, "header");
  ATOM_HIGHEST     = enif_make_atom(env, "highest");
  ATOM_LIMIT       = enif_make_atom(env, "limit");
  ATOM_LINES       = enif_make_atom(env, "lines");
  ATOM_LIST        = enif_make_atom(env, "list");
  ATOM_LOCAL       = enif_make_atom(env, "local");
  ATOM_MERGE_BASE  = enif_make_atom(env, "merge_base");
  ATOM_MESSAGE     = enif_make_atom(env, "message");
  ATOM_MKDIR_CALLS = enif_make_atom(env, "mkdir_calls");
  ATOM_MODE        = enif_make_atom(env, "mode");
  ATOM_MTIME       = enif_make_atom(env, "mtime");
  ATOM_NAME        = enif_make_atom(env, "name");
  ATOM_NEW_NAME    = enif_make_atom(env, "new_name");
  ATOM_NIL         = enif_make_atom(env, "nil");
  ATOM_NONE        = enif_make_atom(env, "none");
  ATOM_NORMAL      = enif_make_atom(env, "normal");
  ATOM_NOT         = enif_make_atom(env, "not");
  ATOM_NOT_FOUND   = enif_make_atom(env, "not_found");
  ATOM_OBJECT      = enif_make_atom(env, "object");
  ATOM_OID         = enif_make_atom(env, "oid");
  ATOM_OK          = enif_make_atom(env, "ok");
  ATOM_OURS        = enif_make_atom(env, "ours");
  ATOM_OVERWRITE   = enif_make_atom(env, "overwrite");
  ATOM_PARENTS     = enif_make_atom(env, "parents");
  ATOM_PATH        = enif_make_atom(env, "path");
  ATOM_PATTERN     = enif_make_atom(env, "pattern");
  ATOM_PERF        = enif_make_atom(env, "perf");
  ATOM_PULL        = enif_make_atom(env, "pull");
  ATOM_PUSH        = enif_make_atom(env, "push");
  ATOM_REMOTE      = enif_make_atom(env, "remote");
  ATOM_RENAME      = enif_make_atom(env, "rename");
  ATOM_REVERSE     = enif_make_atom(env, "reverse");
  ATOM_SETURL      = enif_make_atom(env, "seturl");
  ATOM_SHA         = enif_make_atom(env, "sha");
  ATOM_SIZE        = enif_make_atom(env, "size");
  ATOM_STAGE       = enif_make_atom(env, "stage");
  ATOM_STAT_CALLS  = enif_make_atom(env, "stat_calls");
  ATOM_SUMMARY     = enif_make_atom(env, "summary");
  ATOM_SYSTEM      = enif_make_atom(env, "system");
  ATOM_TAG         = enif_make_atom(env, "tag");
  ATOM_TAGGER      = enif_make_atom(env, "tagger");
  ATOM_TARGET      = enif_make_atom(env, "target");
  ATOM_THEIRS      = enif_make_atom(env, "theirs");
  ATOM_TIME        = enif_make_atom(env, "time");
  ATOM_TIME_OFFSET = enif_make_atom(env, "time_offset");
  ATOM_TO          = enif_make_atom(env, "to");
  ATOM_TOPO_ORDER  = enif_make_atom(env, "topo_order");
  ATOM_TOTAL_STEPS = enif_make_atom(env, "total_steps");
  ATOM_TREE        = enif_make_atom(env, "tree");
  ATOM_TREE_ID     = enif_make_atom(env, "tree_id");
  ATOM_TRUE        = enif_make_atom(env, "true");
  ATOM_TYPE        = enif_make_atom(env, "type");
  ATOM_UPDATE      = enif_make_atom(env, "update");
  ATOM_VERBOSE     = enif_make_atom(env, "verbose");
  ATOM_XDG         = enif_make_atom(env, "xdg");
}
