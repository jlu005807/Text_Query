#pragma once
#include"OrQuery.h"
#include"AndQuery.h"
#include"NotQuery.h"
#include"WordQuery.h"

class Query_manager
{
public:
	void run(std::ifstream& file,std::string sentence)
	{
		
		TextQuery text(file);

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