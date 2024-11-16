#include "sql/operator/update_physical_operator.h"
#include "common/log/log.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];

  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;

  while (OB_SUCC(rc = child->next())) {
    Tuple    *tuple     = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record   &record    = row_tuple->record();
    records_.emplace_back(std::move(record));
  }

  child->close();
  if (fields_->type() != values_->attr_type()) {
        //暂不支持Value::cast_to()
        LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",table_->name(),fields_->name(),fields_->type(),values_->attr_type());
        return RC::INVALID_ARGUMENT;
    } 
  // 先收集记录再删除
  // 记录的有效性由事务来保证，如果事务不保证删除的有效性，那说明此事务类型不支持并发控制，比如VacuousTrx
  int offset = fields_->offset();
  int len = std::min(fields_->len(), values_->length());
  for (Record &record : records_) {
	Record newRecord = record;
	memset(newRecord.data() + offset, 0, fields_->len());
	memcpy(newRecord.data() + offset, values_->data(), len);
    rc = trx_->update_record(table_, record, newRecord);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
  }

  return RC::SUCCESS;
}
RC UpdatePhysicalOperator::next() 
{ 
    return RC::RECORD_EOF; 
}
RC UpdatePhysicalOperator::close() 
{
     return RC::SUCCESS; 
}