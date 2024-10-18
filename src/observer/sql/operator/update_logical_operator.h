
#pragma once

#include "sql/operator/logical_operator.h"
#include "storage/field/field_meta.h"

/**
 * @brief 逻辑算子，用于执行update语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table,Value *values,FieldMeta *fields);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }
  
  Table     *table() const { return table_; }
  Value     *values() { return values_; }
  FieldMeta *fields() { return fields_; }
private:
  Table *table_ = nullptr;
  Value     *values_;
  FieldMeta *fields_;
};