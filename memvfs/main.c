#include <stdio.h>

#include "extism/extism-pdk.h"
#include "sqlite3.h"
#include "sqlite3ext.h"

// TODO: clean this up

static const char dbbytes[] = {0/*redacted*/};

int sqlite3_memvfs_init(
  sqlite3 *db, 
  char **pzErrMsg, 
  const sqlite3_api_routines *pApi
);
int core_init(const char* dummy)
{
    int nErr = 0;
    nErr += sqlite3_auto_extension((void *)sqlite3_memvfs_init);
    return nErr ? SQLITE_ERROR : SQLITE_OK;
}

int32_t count_vowels()
{
  uint64_t length = extism_input_length();
  uint8_t *input = malloc(length);
  extism_load_input(input, length);

  char out[128];
  int rc;

  
  char *memuri = sqlite3_mprintf("file:whatever?ptr=0x%p&sz=%d&freeonclose=1",
                                 &dbbytes, sizeof(dbbytes));

  sqlite3 *db;
  sqlite3_db_config(db, SQLITE_DBCONFIG_ENABLE_LOAD_EXTENSION, 1, NULL);
	if (sqlite3_memvfs_init(db, NULL, NULL) != SQLITE_OK_LOAD_PERMANENTLY)
	{
    int n = snprintf(out, 128, "error loading memvfs");
    uint64_t offs_ = extism_alloc(n);
    extism_store(offs_, (const uint8_t *)out, n);
    extism_output_set(offs_, n);
    return 0;
	}

  rc = sqlite3_open_v2(memuri, &db, SQLITE_OPEN_READONLY | SQLITE_OPEN_URI, "memvfs");
  if (rc != SQLITE_OK) {
    int n = snprintf(out, 128, "open memvfs: %s\n", sqlite3_errmsg(db));
    uint64_t offs_ = extism_alloc(n);
    extism_store(offs_, (const uint8_t *)out, n);
    extism_output_set(offs_, n);
    return 0;
  }
  //sqlite3_free(memuri);

  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(db, "SELECT * FROM sqlite_schema", -1, &stmt, NULL) !=
      SQLITE_OK) {
    int n = snprintf(out, 128, "prepare: %s\n", sqlite3_errmsg(db));
    uint64_t offs_ = extism_alloc(n);
    extism_store(offs_, (const uint8_t *)out, n);
    extism_output_set(offs_, n);

    return 0;
  }

  //int n = snprintf(out, 128, "{\"count\": %lld}", count);
  //int n = snprintf(out, 128, "input: %s", input);

  int n;
  n = snprintf(out, 128, "input: %s, uri=%s", input, memuri);
  for (int rc = sqlite3_step(stmt); rc == SQLITE_ROW; rc = sqlite3_step(stmt)) {
    n = snprintf(out, 128, "hello%s\n", sqlite3_column_text(stmt, 0));
  }

  uint64_t offs_ = extism_alloc(n);
  extism_store(offs_, (const uint8_t *)out, n);
  extism_output_set(offs_, n);

  return 0;
}

int main() {}
