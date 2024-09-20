#pragma once
#include"Query.h"

class WordQuery:public Query_base
{
	friend class Query;//Query使用WordQuery构造函数

	WordQuery(const std::string &s):query_word(s)
	{

	}

	//具体的类：WordQuery将定义所有继承的纯虚函数

	QueryResult eval(const TextQuery& t)const
	{	
		return  t.query(query_word);
	}


	std::string rep()const
	{
		return query_word;
	}

	std::string query_word;//需要查找的单词
};

inline Query::Query(const std::string& s) :q(new WordQuery(s)) 
{
}

