#pragma once
#ifndef _VALUEUOM_H_
#define _VALUEUOM_H_


struct ValueUOM
{
	size_t value = 0;
	std::string quantitative_measure;
	std::string temporary_measure;

	void input()
	{
		std::cout << "\nВведите число: ";
		while (!(std::cin >> value))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Данные введены некорректно, попробуйте еще раз: ";
		}

		bool uom_flag = false;

		std::cout << "\nПродолжить ввод единицы измерения?\n"
			<< "   1. Да\n" << "ELSE. Нет\n"
			<< "\nВведите ответ: ";

		std::string answer;
		std::cin >> answer;

		if (answer == "1")
		{
			std::cout << "\nВведите количественную меру: ";
			std::cin >> quantitative_measure;

			std::cout << "\nПродолжить ввод временной меры?\n"
				<< "   1. Да\n" << "ELSE. Нет\n"
				<< "\nВведите ответ: ";

			std::string temp_answer;
			std::cin >> temp_answer;

			if (temp_answer == "1")
			{
				std::cout << "\nВведите временную меру: ";
				std::cin >> temporary_measure;
			}
		}
	}

	void output()
	{
		if (temporary_measure.empty())
		{
			std::cout << value << ' ' << quantitative_measure;
		}
		else
		{
			std::cout << value << ' ' << quantitative_measure << '/' << temporary_measure;
		}
	}
};


#endif //_VALUEUOM_H_