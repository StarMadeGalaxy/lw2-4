#include "MobileCompany.h"


MobileCompany::MobileCompany(size_t size)
{
	if (size <= 0) { return; }

	subscriber_amount = size_t();

	int choice = int();

	for (size_t i = 0; i < size; i++)
	{
		std::cout << "\n�������� ����� ���������� ������ [" << i + 1 << "]:"
			<< "\n1. ������ ���������� �������"
			<< "\n2. ������������ ��������� ������"
			<< "\n3. ������������ ��������� ������ ��� ���� ���������� �������\n";

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		do {
			std::cout << "\n�������: ";
			std::cin >> choice;
		} while (choice > 3 || choice < 1);

		if (choice == 1)
		{
			ValueUOM monthly_fee;
			ValueUOM internet_traffic;
			ValueUOM out_calls_min;
			ValueUOM in_calls_min;
			int customers_amount = int();
			std::string tariff_name;

			std::cout << "\n������� ����������� �����: ";
			monthly_fee.input();
			std::cout << "\n������� ���������� �������� �������: ";
			internet_traffic.input();
			std::cout << "\n������� ���������� ����� ��� ����: ";
			out_calls_min.input();
			std::cout << "\n������� ���������� ����� ������ ����: ";
			in_calls_min.input();
			std::cout << "\n������� ���������� ���������: ";
			while (!(std::cin >> customers_amount))
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "������ ������� �����������, ���������� ��� ���: ";
			}
			std::cout << "\n������� �������� ������: ";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// delete \n from previous input
			std::getline(std::cin, tariff_name);


			tariff_list.emplace_back(monthly_fee, internet_traffic, out_calls_min,
				in_calls_min, customers_amount, tariff_name);
		}
		else if (choice == 2) {
			MobileTariff random_train;
			random_train.create_random_tariff();
			tariff_list.push_back(random_train);
		}
		else if (choice == 3) {
			for (size_t j = 0; j < size - i; i++)
			{
				MobileTariff random_tariff;
				random_tariff.create_random_tariff();
				tariff_list.push_back(random_tariff);
			}
			break;
		}
	}
}

void MobileCompany::sort_tariff_list()
{
	std::sort(tariff_list.begin(), tariff_list.end());
}

void MobileCompany::count_subscribers()
{
	size_t amount = 0;
	for (MobileTariff& tariff : tariff_list)
	{
		amount++;
	}
	subscriber_amount = amount;
}

void MobileCompany::show_tariffs()
{
	if (tariff_list.empty())
	{
		std::cout << "\nTariff list is empty.\n";
		return;
	}

	std::cout << "\n+--------------------------+------------+------------+-------------+-------------+------------------+"
		<< "\n|          �����           |   �����    |  ��������  | ������ ���� |   ��� ����  | ���-�� ��������� |"
		<< "\n+--------------------------+------------+------------+-------------+-------------+------------------+\n";

	for (MobileTariff& tariff : tariff_list)
	{
		tariff.show_information();
		std::cout << "\n+--------------------------+------------+------------+-------------+-------------+------------------+\n";
	}

}

void MobileCompany::set_tariff_list(std::vector<MobileTariff> tariff) { this->tariff_list = tariff; }
void MobileCompany::set_subscriber_amount(const int& amount) { this->subscriber_amount = amount; }

std::vector<MobileTariff> MobileCompany::get_tariff_list() const { return tariff_list; }
size_t MobileCompany::get_subscriber_amount() const { return subscriber_amount; }
