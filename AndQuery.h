#pragma once
#include"BinaryQuery.h"

class AndQuery :public BinaryQuery
{
	friend Query operator&(const Query&, const Query&);

	AndQuery(const Query& left, const Query& right) :BinaryQuery(left, right, "&")
	{

	}

	//AndQuery��Ϊ������࣬�̳���rep���Ҷ������������麯��
	QueryResult eval(const TextQuery&)const;


};

inline Query operator&(const Query& lhs, const Query& rhs)
{
	return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

