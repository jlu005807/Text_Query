#pragma once
#include"OrQuery.h"
#include"AndQuery.h"
#include"NotQuery.h"
#include"WordQuery.h"

class manager
{
public:
	//转换windows文件路径为c语言文件路径
	std::string convertAndTrim(const std::string& windowsPath) {
		std::string cPath = windowsPath;
		// 将反斜杠替换为正斜杠
		std::replace(cPath.begin(), cPath.end(), '\\', '/');
		// 去除引号
		cPath.erase(std::remove(cPath.begin(), cPath.end(), '"'), cPath.end());
		return cPath;
	}

	void run()
	{
		std::cout << "Please input the file path of text" << std::endl;
		//不做规范性检查
		std::string file_path;
		std::getline(std::cin, file_path);
		file_path = convertAndTrim(file_path);

		//getchar();//注意有getline时要吃掉回车符

		std::ifstream file(file_path);

		if (!file)
		{
			throw std::exception();
		}

		TextQuery text(file);

		std::cout << "Please input the word you want to find" << std::endl;
		std::cout << "E.g: word & ~word | word" << std::endl;//取反时没有空格
		//同样不做规范性检查
		std::string sentence;
		std::getline(std::cin,sentence);

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