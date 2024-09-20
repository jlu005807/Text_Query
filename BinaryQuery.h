#pragma once
#include"Query.h"

class BinaryQuery :public Query_base
{
protected:
	BinaryQuery(const Query& l, const Query& r, std::string s) :lhs(l), rhs(r), opSym(s)
	{

	}

	//BinaryQuery作为抽象类不定义eval
	std::string rep()const
	{
		return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
	}


	//左右条件单词
	Query lhs;

	Query rhs;

	std::string opSym;//运算符名字

};