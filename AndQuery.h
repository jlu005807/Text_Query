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

