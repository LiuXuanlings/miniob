#include "common/log/log.h"
#include "common/types.h"
#include "sql/stmt/drop_table_stmt.h"
#include "event/sql_debug.h"

#include "storage/db/db.h"

RC DropTableStmt::create(Db *db, const DropTableSqlNode &drop_table, Stmt *&stmt)
{
  if (!db->find_table(drop_table.relation_name.c_str())) {
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  stmt = new DropTableStmt(drop_table.relation_name);
  sql_debug("drop table statement: table name %s", drop_table.relation_name.c_str());
  return RC::SUCCESS;
}