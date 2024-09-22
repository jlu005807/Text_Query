#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<assert.h>


class History_manager
{
public:
	int size;//历史记录条数

	std::shared_ptr<std::vector<std::string>> history_document;//历史记录（包括查询记录和时间）
	std::shared_ptr<std::vector<std::string>> file_history;//历史文件路径

	History_manager():history_document(new std::vector<std::string>), file_history(new std::vector<std::string>)
	{
		size = 0;
		load();
	}


	void load()//下载记录
	{
		std::fstream file("history.txt");

		if (!file)
		{
			throw std::exception();
		}

		std::string sentence;//一行记录

		int i = 0;
		while(std::getline(file, sentence))
		{

			if(i%2==0)//偶数为查询结果
			{
				history_document->push_back(sentence+"\n");
				i++;
			}
			else//技术为文件路径
			{
				file_history->push_back(sentence);
				i++;
				size++;
			}
		}

		file.close();

	}


	void add_document(std::string sentence,std::string file_path)
	{
		history_document->push_back(sentence);
		file_history->push_back(file_path);
		size++;
	}


	void save()
	{
		std::fstream file("history.txt");

		if (!file)
		{
			throw std::exception();
		}

		/*std::cout << size << std::endl;
		system("pause");*/

		for (auto i = history_document->begin(); i != history_document->end(); i++)
		{
			auto j = file_history->begin();
			file << *i;
			file << *j << std::endl;
			j++;
		}

		file.close();
	}



	void show_history(int k)//不检查输入是否规范
	{
		std::cout << "HISTORY:" << std::endl;
		if(k==0)
		{
			for (int i = 0; i < size; i++)
			{
				std::cout << "historical record " << i+1 << " :" << std::endl;
				std::cout << (*history_document)[i];
				std::cout << (*file_history)[i] << std::endl;
			}
		}
		else
		{
			assert(k > 0);
			std::cout << "historical record " << k << " :" << std::endl;
			std::cout << (*history_document)[k-1];
			std::cout << (*file_history)[k-1] << std::endl;
		}




	}

};