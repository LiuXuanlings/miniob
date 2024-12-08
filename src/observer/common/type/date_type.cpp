#include "common/lang/comparator.h"
#include "common/lang/sstream.h"
#include "common/log/log.h"
#include "common/type/date_type.h"
#include "common/value.h"
#include <sstream>
#include <iomanip>

int DateType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::DATES && right.attr_type() == AttrType::DATES, "Invalid type");
  return common::compare_int((void *)&left.value_.int_value_, (void *)&right.value_.int_value_);
}

RC DateType::max(const Value &left, const Value &right, Value &result) const
{
  int cmp = common::compare_int((void *)&left.value_.int_value_, (void *)&right.value_.int_value_);
  if (cmp > 0) {
    result.set_int(left.value_.int_value_);
  } else {
    result.set_int(right.value_.int_value_);
  }
  return RC::SUCCESS;
}
RC DateType::min(const Value &left, const Value &right, Value &result) const
{
  int cmp = common::compare_int((void *)&left.value_.int_value_, (void *)&right.value_.int_value_);
  if (cmp < 0) {
    result.set_int(left.value_.int_value_);
  } else {
    result.set_int(right.value_.int_value_);
  }
  return RC::SUCCESS;
}

RC DateType::add(const Value &left, const Value &right, Value &result) const
{
  return RC::UNSUPPORTED;
}

RC DateType::subtract(const Value &left, const Value &right, Value &result) const
{
  return RC::UNSUPPORTED;
}

RC DateType::multiply(const Value &left, const Value &right, Value &result) const
{
  return RC::UNSUPPORTED;
}

RC DateType::negative(const Value &val, Value &result) const
{
  return RC::UNSUPPORTED;
}


RC DateType::set_value_from_str(Value &val, const string &data) const
{
  RC                rc = RC::SUCCESS;
  stringstream deserialize_stream;
  char               year_str[5], month_str[3], day_str[3];
  int                year, month, day;
  deserialize_stream.clear();  // 清理stream的状态，防止多次解析出现异常
  deserialize_stream.str(data);
  deserialize_stream >> year_str >> month_str >> day_str;
  year  = atoi(year_str);
  month = atoi(month_str);
  day   = atoi(day_str);

  if (!deserialize_stream || !deserialize_stream.eof()) {
    rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
  } else {
    int date_int = year * 10000 + month * 100 + day;
    val.set_date(date_int);
  }
  return rc;
}

RC DateType::to_string(const Value &val, string &result) const
{
  int               date_int = val.get_int();
  std::stringstream ss;
  //setw ：需要填充多少个字符,默认填充的字符为' '空格。
  //setfill：设置std::setw将填充什么样的字符
  ss << std::setw(4) << std::setfill('0') << date_int / 10000 << "-" << std::setw(2) << std::setfill('0')
     << (date_int / 100 % 100) << "-" << std::setw(2) << std::setfill('0') << (date_int % 100);
  result = ss.str();
  return RC::SUCCESS;
}