#pragma once
#include"Query_base.h"

//Query_base��Ľӿ���
class Query
{
	//��Щ�������Ҫ���ʽ���shared_ptr�Ĺ��캯�������ú�����˽�е�
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&,const Query&);

public:
	Query() = default;

	Query(const std::string&);//����һ���µ�wordQuery
    
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
	//Query::repͨ��Query_baseָ���rep()�����������
	return os << query.rep();
}