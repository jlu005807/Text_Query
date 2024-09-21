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

QueryResult AndQuery::eval(const TextQuery& text)const
{
	//����������Ĳ�ѯ���set
	auto left = lhs.eval(text);
	auto right = rhs.eval(text);

	//���潻��
	auto ret_lines = std::make_shared<std::set<line_no>>();

	//��������Χ�Ľ���д��Ŀ�ĵ�����
	//���ε��õ�Ŀ�ĵ�������ret���Ԫ��
	std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));

	return QueryResult(rep(), ret_lines, left.get_file());


}