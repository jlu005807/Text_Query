#pragma once
#include"Query_base.h"

//Query_base类的接口类
class Query
{
	//这些运算符需要访问接受shared_ptr的构造函数，而该函数是私有的
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&,const Query&);

public:
	Query() = default;

	Query(const std::string&);//构建一个新的wordQuery
    
	QueryResult eval(const TextQuery& t)const
	{
		return q->eval(t);
	}

	std::string rep()const
	{
		return q->rep();
	}

private:
	Query(std::shared_ptr<Query_base> query) :q(query)
	{

	}

	std::shared_ptr<Query_base> q;
};


std::ostream& operator<<(std::streambuf& os, const Query& query)
{
	//Query::rep通过Query_base指针对rep()进行了虚调用
	return os << query.rep();
}