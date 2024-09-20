#pragma once
#include"QueryResult.h"


class TextQuery
{
public:
	using line_no = std::vector<std::string>::size_type;

	TextQuery(std::ifstream&);

	QueryResult query(const std::string&)const;

private:
	std::shared_ptr<std::vector<std::string>> file;//�����ļ�
	//ÿ�����ʵ������еļ��ϵ�ӳ��
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;

};

TextQuery::TextQuery(std::ifstream& is) :file(new std::vector<std::string>)
{
	std::string text;

	while (std::getline(is, text)/*���в���*/)
	{
		file->push_back(text);//��������ı�

		int n = file->size() - 1;//��ǰ�к�

		std::istringstream line(text);//�����ı��ֽ�Ϊ����

		std::string word;//��¼����

		while (line >> word)//������ÿ������
		{
			//������ʲ���wm�У���֮Ϊ�±���wm�����һ��
			auto& lines = wm[word];//lines��һ��shared_ptr
			
			if (!lines)//��һ�������������
				lines.reset(new std::set<line_no>);//����һ���µ�set

			lines->insert(n);//�����кŲ���set��
		}
	}
		

}

QueryResult TextQuery::query(const std::string& sought)const
{
	//���δ�ҵ����ʣ�����һ��ָ���set��ָ��
	static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);

	//ʹ��find,���⽫������ӵ�wm��!
	auto loc = wm.find(sought);

	if (loc == wm.end())//δ�ҵ�
	{
		return QueryResult(sought, nodata, file);
	}
	else
	{
		return QueryResult(sought, loc->second, file);
	}

}