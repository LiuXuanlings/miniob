#include "sql/stmt/join_stmt.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

JoinStmt::~JoinStmt()
{
   if (filter_ != nullptr) {
      delete filter_;
    }
}

RC JoinStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    JoinSqlNode &sql_node, JoinStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;

  JoinStmt *tmp_stmt = new JoinStmt();
  // 创建过滤语句
  rc = FilterStmt::create(db, default_table, tables, sql_node.conditions, tmp_stmt->filter_);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }
  
  stmt = tmp_stmt;
  return rc;
}
