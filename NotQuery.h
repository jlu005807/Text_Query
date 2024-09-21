#pragma once
#include"Query.h"

class NotQuery :public Query_base
{
	friend Query operator~(const Query&);

	NotQuery(const Query& q):query(q)
	{ 

	}

	std::string rep()const
	{
		return "~(" + query.rep() + ")";
	}

	QueryResult eval(const TextQuery&)const;

	Query query;
};

inline Query operator~(const Query& operand)
{
	return std::shared_ptr<Query_base>(new NotQuery(operand));
}

QueryResult NotQuery::eval(const TextQuery& text)const
{
	//�����
	auto result = query.eval(text);
	//��ʼʱ���setΪ��
	auto ret_lines = std::make_shared<std::set<line_no>>();

	//�����е���
	auto beg = result.begin(), end = result.end();
	//����ÿһ�У�������в���result���У�������ӵ�ret_lines
	auto sz = result.get_file()->size();

	for (size_t n = 0; n != sz; n++)
	{
		//���δ������result��������
		//��鵱ǰ���Ƿ����
		if (beg == end || *beg != n)
		{
			//�������result���У�����к�
			ret_lines->insert(n);
		}
		else if (beg != end)
		{
			++beg;//���������һ��
		}
	}

	return QueryResult(rep(), ret_lines, result.get_file());
}