#pragma once
#include"Query.h"

class NotQuery :public Query_base
{
	friend Query operator~(const Query&);

	NotQuery(const Query& q):query(q)
	{ 

	}

	std::string rep()const
	{
		return "~(" + query.rep() + ")";
	}

	QueryResult eval(const TextQuery&)const;

	Query query;
};

inline Query operator~(const Query& operand)
{
	return std::shared_ptr<Query_base>(new NotQuery(operand));
}

QueryResult NotQuery::eval(const TextQuery& text)const
{
	//虚调用
	auto result = query.eval(text);
	//开始时结果set为空
	auto ret_lines = std::make_shared<std::set<line_no>>();

	//所有行迭代
	auto beg = result.begin(), end = result.end();
	//对于每一行，如果该行不在result当中，则将其添加到ret_lines
	auto sz = result.get_file()->size();

	for (size_t n = 0; n != sz; n++)
	{
		//如果未处理完result的所有行
		//检查当前行是否存在
		if (beg == end || *beg != n)
		{
			//如果不在result当中，添加行号
			ret_lines->insert(n);
		}
		else if (beg != end)
		{
			++beg;//否则继续下一行
		}
	}

	return QueryResult(rep(), ret_lines, result.get_file());
}