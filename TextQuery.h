#pragma once
#include"QueryResult.h"


class TextQuery
{
public:
	using line_no = std::vector<std::string>::size_type;

	TextQuery(std::ifstream&);

	QueryResult query(const std::string&)const;

private:
	std::shared_ptr<std::vector<std::string>> file;//输入文件
	//每个单词到所在行的集合的映射
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;

};

TextQuery::TextQuery(std::ifstream& is) :file(new std::vector<std::string>)
{
	std::string text;

	while (std::getline(is, text)/*逐行操作*/)
	{
		file->push_back(text);//保存此行文本

		int n = file->size() - 1;//当前行号

		std::istringstream line(text);//将行文本分解为单词

		std::string word;//记录单词

		while (line >> word)//对行中每个单词
		{
			//如果单词不在wm中，以之为下标在wm中添加一项
			auto& lines = wm[word];//lines是一个shared_ptr
			
			if (!lines)//第一次遇到这个单词
				lines.reset(new std::set<line_no>);//分配一个新的set

			lines->insert(n);//将此行号插入set中
		}
	}
		

}

QueryResult TextQuery::query(const std::string& sought)const
{
	//如果未找到单词，返回一个指向此set的指针
	static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);

	//使用find,避免将单词添加到wm中!
	auto loc = wm.find(sought);

	if (loc == wm.end())//未找到
	{
		return QueryResult(sought, nodata, file);
	}
	else
	{
		return QueryResult(sought, loc->second, file);
	}

}