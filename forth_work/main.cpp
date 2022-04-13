#include "MobileCompany.h"
#include "MobileTariff.h"


int main()
{
	setlocale(LC_ALL, "rus");

	size_t size = size_t();

	std::cout << "������� ���������� �������: ";
	while (!(std::cin >> size))
	{
		std::cin.clear();
		std::cin.ignore(INT16_MAX, '\n');
		std::cout << "������ ������� �����������, ���������� ��� ���: ";
	}

	MobileCompany mobile_company(size);
	mobile_company.show_tariffs();
	mobile_company.sort_tariff_list();
	std::cout << "������������� �� ����������� �����: " << std::endl;
	mobile_company.show_tariffs();
}