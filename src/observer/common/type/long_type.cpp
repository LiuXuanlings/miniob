/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "common/lang/comparator.h"
#include "common/lang/sstream.h"
#include "common/log/log.h"
#include "common/type/long_type.h"
#include "common/value.h"

int LongType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::LONGS, "left type is not long");
  ASSERT(right.attr_type() == AttrType::LONGS, "right type is not long");
  return common::compare_long((void *)&left.value_.long_value_, (void *)&right.value_.long_value_);
}

RC LongType::add(const Value &left, const Value &right, Value &result) const
{
  result.set_long(left.get_long() + right.get_long());
  return RC::SUCCESS;
}

RC LongType::subtract(const Value &left, const Value &right, Value &result) const
{
  result.set_long(left.get_long() - right.get_long());
  return RC::SUCCESS;
}

RC LongType::multiply(const Value &left, const Value &right, Value &result) const
{
  result.set_long(left.get_long() * right.get_long());
  return RC::SUCCESS;
}

RC LongType::negative(const Value &val, Value &result) const
{
  result.set_long(-val.get_long());
  return RC::SUCCESS;
}

RC LongType::set_value_from_str(Value &val, const string &data) const
{
  return RC::UNSUPPORTED;
}

RC LongType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << val.value_.long_value_;
  result = ss.str();
  return RC::SUCCESS;
}