#pragma once
#include"BinaryQuery.h"

class OrQuery :public BinaryQuery
{
	friend Query operator|(const Query&, const Query&);

	OrQuery(const Query& left, const Query& right) :BinaryQuery(left, right, "|")
	{

	}

	//AndQuery��Ϊ������࣬�̳���rep���Ҷ������������麯��
	QueryResult eval(const TextQuery&)const;


};

inline Query operator|(const Query& lhs, const Query& rhs)
{
	return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResult OrQuery::eval(const TextQuery& text)const
{
	//ͨ��Query��Աlhs��rhs���������
	//����eval����ÿ����������QueryResult
	auto right = rhs.eval(text);
	auto left = lhs.eval(text);

	//������������������к�

	auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());

	//�����Ҳ�������к�
	ret_lines->insert(right.begin(), right.end());

	//����һ���µ�QueryResult,��ʾlhs��rhs�Ĳ���
	return QueryResult(rep(), ret_lines, left.get_file());

}