#pragma once
#include<iostream>
#include<fstream>//!!!�ļ�����
#include<sstream>//!!!string��
#include<string>
#include<vector>
#include<map>
#include<set>


std::string make_plural(size_t ctr, const std::string& word, const std::string& ending)
{
	return (ctr > 1) ? word + ending : word;
}


class QueryResult
{
	friend std::ostream& print(std::ostream&, const QueryResult&);

	using line_no = std::vector<std::string>::size_type;
public:
	QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f):sought(s),lines(p),file(f) {

	}

private:

	std::string sought;//��ѯ����

	std::shared_ptr<std::set<line_no>>lines;//���ֵ��к�

	std::shared_ptr<std::vector<std::string>> file;//�����ļ�
};

std::ostream& print(std::ostream& os, const QueryResult& qr)
{
	//����ҵ����ʣ���ӡ���ִ��������г��ֵ�λ��
	os << qr.sought << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), "time", "s") << std::endl;

	//��ӡ���ʳ��ֵ�ÿһ��
	for (auto num : *qr.lines)//��set��ÿһ������
		//�кŴ�һ��ʼ
		os << "\t(line " << num + 1 << ")" << *(qr.file->begin() + num) << std::endl;

	return os;
}