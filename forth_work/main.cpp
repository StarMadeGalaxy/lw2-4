#include "MobileCompany.h"
#include "MobileTariff.h"


int main()
{
	setlocale(LC_ALL, "rus");

	size_t size = size_t();

	std::cout << "Введите количество тарифов: ";
	while (!(std::cin >> size))
	{
		std::cin.clear();
		std::cin.ignore(INT16_MAX, '\n');
		std::cout << "Данные введены некорректно, попробуйте еще раз: ";
	}

	MobileCompany mobile_company(size);
	mobile_company.show_tariffs();
	mobile_company.sort_tariff_list();
	std::cout << "Отсортировано по абонентской плате: " << std::endl;
	mobile_company.show_tariffs();
}