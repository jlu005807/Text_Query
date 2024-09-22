#pragma once
#include<ctime>
#include"Query_manager.h"
#include"History_manager.h"


class General_manager
{
public:
	Query_manager query_manager;
	History_manager history_manager;

	//ת��windows�ļ�·��Ϊc�����ļ�·��
	std::string convertAndTrim(const std::string& windowsPath) {
		std::string cPath = windowsPath;
		// ����б���滻Ϊ��б��
		std::replace(cPath.begin(), cPath.end(), '\\', '/');
		// ȥ������
		cPath.erase(std::remove(cPath.begin(), cPath.end(), '"'), cPath.end());
		return cPath;
	}

	void show_menu()
	{
		std::cout << "Please select your choice:" << std::endl;
		std::cout << "          1-query         " << std::endl;
		std::cout << "          2-history       " << std::endl;
		std::cout << "          0-exit          " << std::endl;
	}

	void open_query()
	{
		std::cout << "Please input the file path of text" << std::endl;
		//�����淶�Լ��
		std::string file_path;
		std::getline(std::cin, file_path);
		file_path = convertAndTrim(file_path);

		std::cout << "Please input the word you want to find" << std::endl;
		std::cout << "E.g: word & ~word | word" << std::endl;//ȡ��ʱû�пո�
		//ͬ�������淶�Լ��
		std::string sentence;
		std::getline(std::cin, sentence);

		time_t now = time(0);

		std::string query_time(ctime(&now));

		std::string document = sentence + "      time:" + query_time;

		history_manager.add_document(document, file_path);

		query_manager.run(file_path, sentence);

	}

	void open_history()
	{

		if (history_manager.size == 0)
		{
			std::cout << "history record is empty" << std::endl;
			return;
		}

		std::cout << "Please input the history record you want to see(0-all)";//���������淶��
		std::cout << "( size from 1 to " << history_manager.size << " ):";
		int k;
		std::cin >> k;
		getchar();


		if (k > history_manager.size)
		{
			std::cout << "out of range" << std::endl;
			return;
		}

		history_manager.show_history(k);

	}


	void text_query()
	{		

		while (true)
		{
			show_menu();
			int select;
			std::cin >> select;//���������淶�ԣ���������Ų�����
		
			//getchar();//ע����getlineʱҪ�Ե��س���
			getchar();

			switch (select)
			{
			case 0:
			{
				std::cout << "successfully exit!" << std::endl;
				history_manager.save();
				system("pause");
				exit(0);
			}
			
			case 1:
				open_query();
				break;
			case 2:
				open_history();
				break;
			default:
				std::cout << "No Zuo No Died!" << std::endl;
				history_manager.save();
				system("pause");
				exit(0);
			}
			
			system("pause");
			system("cls");


		}

	}

};