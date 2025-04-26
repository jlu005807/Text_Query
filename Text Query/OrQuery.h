#pragma once
#include"BinaryQuery.h"

class OrQuery :public BinaryQuery
{
	friend Query operator|(const Query&, const Query&);

	OrQuery(const Query& left, const Query& right) :BinaryQuery(left, right, "|")
	{

	}

	//AndQuery作为具体的类，继承了rep并且定义了其他纯虚函数
	QueryResult eval(const TextQuery&)const;


};

inline Query operator|(const Query& lhs, const Query& rhs)
{
	return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResult OrQuery::eval(const TextQuery& text)const
{
	//通过Query成员lhs和rhs进行需调用
	//调用eval返回每个运算对象的QueryResult
	auto right = rhs.eval(text);
	auto left = lhs.eval(text);

	//拷贝左侧运算符对象的行号

	auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());

	//插入右侧运算符行号
	ret_lines->insert(right.begin(), right.end());

	//返回一个新的QueryResult,表示lhs和rhs的并集
	return QueryResult(rep(), ret_lines, left.get_file());

}