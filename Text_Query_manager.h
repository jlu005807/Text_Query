#pragma once
#include"OrQuery.h"
#include"AndQuery.h"
#include"NotQuery.h"
#include"WordQuery.h"

class manager
{
public:
	//ת��windows�ļ�·��Ϊc�����ļ�·��
	std::string convertAndTrim(const std::string& windowsPath) {
		std::string cPath = windowsPath;
		// ����б���滻Ϊ��б��
		std::replace(cPath.begin(), cPath.end(), '\\', '/');
		// ȥ������
		cPath.erase(std::remove(cPath.begin(), cPath.end(), '"'), cPath.end());
		return cPath;
	}

	void run()
	{
		std::cout << "Please input the file path of text" << std::endl;
		//�����淶�Լ��
		std::string file_path;
		std::getline(std::cin, file_path);
		file_path = convertAndTrim(file_path);

		//getchar();//ע����getlineʱҪ�Ե��س���

		std::ifstream file(file_path);

		if (!file)
		{
			throw std::exception();
		}

		TextQuery text(file);

		std::cout << "Please input the word you want to find" << std::endl;
		std::cout << "E.g: word & ~word | word" << std::endl;//ȡ��ʱû�пո�
		//ͬ�������淶�Լ��
		std::string sentence;
		std::getline(std::cin,sentence);

		std::stringstream master(sentence);
		std::vector<std::string> words;
		std::vector<char> operators;
		std::string now_word;

		Query q;

		//'~'����
		auto f = [&](int k)->Query {
			if (words[k][0] == '~')
			{
				std::string real_word = words[k].substr(1);
				return ~Query(real_word);
			}
			else
			{
				return Query(words[k]);
			}
		};

		while (master >> now_word)
		{
			/*std::cout << now_word << std::endl;
			system("Pause");*/


			if (now_word != "|" && now_word != "&")
			{
				words.push_back(now_word);
			}
			else
			{
				operators.push_back(now_word[0]);
			}
		}
		
		//�����������Ϊ�㣬�ȴ���һ������
		if (words.size() != 0)
		{
			q = f(0);
		}

		//��Ԫ���㲻Ϊ��,�˴�������ʽ���,Ĭ����ȷ����������͵����������
		if (operators.size()!= 0)
		{
			//ָ��operators
			int i = 0;
			//ָ��words
			int j = 1;

			while (i != operators.size())
			{

				switch (operators[i++])
				{
				case '&':
					q = q & f(j++);
					break;
				case'|':
					q = q | f(j++);
				default:
					break;
				}


			}
		}

		//������
		print_t(std::cout, q.eval(text));
	}
};