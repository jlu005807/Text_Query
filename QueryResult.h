#pragma once
#include<iostream>
#include<fstream>//!!!文件操作
#include<sstream>//!!!string流
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

	std::string sought;//查询单词

	std::shared_ptr<std::set<line_no>>lines;//出现的行号

	std::shared_ptr<std::vector<std::string>> file;//输入文件
};

std::ostream& print(std::ostream& os, const QueryResult& qr)
{
	//如果找到单词，打印出现次数和所有出现的位置
	os << qr.sought << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), "time", "s") << std::endl;

	//打印单词出现的每一行
	for (auto num : *qr.lines)//对set中每一个单词
		//行号从一开始
		os << "\t(line " << num + 1 << ")" << *(qr.file->begin() + num) << std::endl;

	return os;
}