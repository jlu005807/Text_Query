#pragma once
#include"BinaryQuery.h"

class AndQuery :public BinaryQuery
{
	friend Query operator&(const Query&, const Query&);

	AndQuery(const Query& left, const Query& right) :BinaryQuery(left, right, "&")
	{

	}

	//AndQuery作为具体的类，继承了rep并且定义了其他纯虚函数
	QueryResult eval(const TextQuery&)const;


};

inline Query operator&(const Query& lhs, const Query& rhs)
{
	return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

QueryResult AndQuery::eval(const TextQuery& text)const
{
	//获得运算对象的查询结果set
	auto left = lhs.eval(text);
	auto right = rhs.eval(text);

	//保存交集
	auto ret_lines = std::make_shared<std::set<line_no>>();

	//将两个范围的交集写入目的迭代器
	//本次调用的目的迭代器向ret添加元素
	std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));

	return QueryResult(rep(), ret_lines, left.get_file());


}