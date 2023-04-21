#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "extism/extism-pdk.h"
#include "sqlite3.h"
#include "sqlite3ext.h"

// TODO: clean this up

static char* out_start;
static char* out_head;

static void errorLogCallback(void* pStatement, int iErrCode, const char* zMsg) {
  out_head +=
      snprintf(out_head, 1024 - (out_head - out_start),
               "statement: %s\n(%d) %s\n", *(char**)pStatement, iErrCode, zMsg);
}

int lstat_ignore_enotcapable(const char* path, struct stat* buf) {
  int err = lstat(path, buf);
  if (err && errno == ENOTCAPABLE) {
    *buf = (struct stat){0};
    return 0;
  }
  return err;
}

int sqlite3_memvfs_init(sqlite3* db,
                        char** pzErrMsg,
                        const sqlite3_api_routines* pApi);
int core_init(const char* dummy) {
  int nErr = 0;
  nErr += sqlite3_auto_extension((void*)sqlite3_memvfs_init);
  return nErr ? SQLITE_ERROR : SQLITE_OK;
}

int32_t count_vowels() {
  uint64_t length = extism_input_length();
  uint8_t* input = malloc(length);
  extism_load_input(input, length);

  char out[1024];
  int rc;

  out_start = out;
  out_head = out;
  sqlite3_config(SQLITE_CONFIG_LOG, errorLogCallback, NULL);

  sqlite3_vfs* default_vfs = sqlite3_vfs_find(NULL);
  default_vfs->xSetSystemCall(NULL, "lstat", (void*)lstat_ignore_enotcapable);

  // struct stat st;
  // stat("/path/to/your.db", &st);
  // off_t size = st.st_size;
  // if (size > 0) {
  //   int n = snprintf(out, 128, "sup: %d\n", size);
  //   uint64_t offs_ = extism_alloc(n);
  //   extism_store(offs_, (const uint8_t *)out, n);
  //   extism_output_set(offs_, n);
  //   return 0;
  // }

  sqlite3* db;

  rc = sqlite3_open("/path/to/your.db", &db);
  if (rc != SQLITE_OK) {
    // int n = snprintf(out, 128, "open failed: %s (log size: %d)\n",
    // sqlite3_errmsg(db), out_head-out_start);
    int n = out_head - out_start;
    uint64_t offs_ = extism_alloc(n);
    extism_store(offs_, (const uint8_t*)out, n);
    extism_output_set(offs_, n);
    return 0;
  }

  sqlite3_stmt* stmt;
  if (sqlite3_prepare_v2(db, "SELECT name FROM sqlite_schema", -1, &stmt,
                         NULL) != SQLITE_OK) {
    int n = snprintf(out, 128, "prepare: %s\n", sqlite3_errmsg(db));
    uint64_t offs_ = extism_alloc(n);
    extism_store(offs_, (const uint8_t*)out, n);
    extism_output_set(offs_, n);

    return 0;
  }

  int n;
  n = snprintf(out, 128, "input: %s", input);
  for (int rc = sqlite3_step(stmt); rc == SQLITE_ROW; rc = sqlite3_step(stmt)) {
    n = snprintf(out, 128, "hello%s\n", sqlite3_column_text(stmt, 0));
  }

  uint64_t offs_ = extism_alloc(n);
  extism_store(offs_, (const uint8_t*)out, n);
  extism_output_set(offs_, n);

  return 0;
}

int main() {
  count_vowels();
}
