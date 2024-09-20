#pragma once
#include"Query.h"

class WordQuery:public Query_base
{
	friend class Query;//Queryʹ��WordQuery���캯��

	WordQuery(const std::string &s):query_word(s)
	{

	}

	//������ࣺWordQuery���������м̳еĴ��麯��

	QueryResult eval(const TextQuery& t)const
	{	
		return  t.query(query_word);
	}


	std::string rep()const
	{
		return query_word;
	}

	std::string query_word;//��Ҫ���ҵĵ���
};

inline Query::Query(const std::string& s) :q(new WordQuery(s)) 
{
}

