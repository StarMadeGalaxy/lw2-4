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
		std::cout << "\n������� �����: ";
		while (!(std::cin >> value))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "������ ������� �����������, ���������� ��� ���: ";
		}

		bool uom_flag = false;

		std::cout << "\n���������� ���� ������� ���������?\n"
			<< "   1. ��\n" << "ELSE. ���\n"
			<< "\n������� �����: ";

		std::string answer;
		std::cin >> answer;

		if (answer == "1")
		{
			std::cout << "\n������� �������������� ����: ";
			std::cin >> quantitative_measure;

			std::cout << "\n���������� ���� ��������� ����?\n"
				<< "   1. ��\n" << "ELSE. ���\n"
				<< "\n������� �����: ";

			std::string temp_answer;
			std::cin >> temp_answer;

			if (temp_answer == "1")
			{
				std::cout << "\n������� ��������� ����: ";
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