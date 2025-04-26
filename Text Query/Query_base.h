#pragma once
#include"TextQuery.h"


class Query_base
{
	friend class Query;

protected:
	using line_no = TextQuery::line_no;//用于eval函数
	
	virtual ~Query_base() = default;

private:
	//eval返回与当前Query匹配的QueryResult
	virtual QueryResult eval(const TextQuery&)const = 0;

	//rep是表示查询的一个string
	virtual std::string rep()const = 0;


};