#pragma once
#include"TextQuery.h"


class Query_base
{
	friend class Query;

protected:
	using line_no = TextQuery::line_no;//����eval����
	
	virtual ~Query_base() = default;

private:
	//eval�����뵱ǰQueryƥ���QueryResult
	virtual QueryResult eval(const TextQuery&)const = 0;

	//rep�Ǳ�ʾ��ѯ��һ��string
	virtual std::string rep()const = 0;


};