#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<assert.h>


class History_manager
{
public:
	int size;//��ʷ��¼����

	std::shared_ptr<std::vector<std::string>> history_document;//��ʷ��¼��������ѯ��¼��ʱ�䣩
	std::shared_ptr<std::vector<std::string>> file_history;//��ʷ�ļ�·��

	History_manager():history_document(new std::vector<std::string>), file_history(new std::vector<std::string>)
	{
		size = 0;
		load();
	}


	void load()//���ؼ�¼
	{
		std::fstream file("history.txt");

		if (!file)
		{
			throw std::exception();
		}

		std::string sentence;//һ�м�¼

		int i = 0;
		while(std::getline(file, sentence))
		{

			if(i%2==0)//ż��Ϊ��ѯ���
			{
				history_document->push_back(sentence+"\n");
				i++;
			}
			else//����Ϊ�ļ�·��
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



	void show_history(int k)//����������Ƿ�淶
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