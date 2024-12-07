#pragma once

#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include <unordered_map>
#include "filter_stmt.h"

class Db;
class Table;

/**
 * @brief Join
 * @ingroup Statement
 */
class JoinStmt 
{
public:
  JoinStmt () = default;
  virtual ~JoinStmt ();

public:
  FilterStmt* join_condition() { return filter_; }
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
      JoinSqlNode &sql_node,  JoinStmt  *&stmt);

private:
  FilterStmt* filter_ = nullptr; 
};
