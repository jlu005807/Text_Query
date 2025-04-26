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

		//'~'处理
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
		
		//如果单词数不为零，先处理一个单词
		if (words.size() != 0)
		{
			q = f(0);
		}

		//二元运算不为零,此处不做算式检查,默认正确，即运算符和单词数量相符
		if (operators.size()!= 0)
		{
			//指向operators
			int i = 0;
			//指向words
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
		//输出结果
		print_t(std::cout, q.eval(text));
	}
};