#include "MobileTariff.h"


MobileTariff::MobileTariff() : customers_number(0)
{}

MobileTariff::MobileTariff(ValueUOM monthly_fee, ValueUOM internet_traffic, ValueUOM out_calls_min,
	ValueUOM in_calls_min, int customers_number, std::string tariff_name)
{
	this->monthly_fee = monthly_fee;
	this->internet_traffic = internet_traffic;
	this->out_calls_min = out_calls_min;
	this->in_calls_min = in_calls_min;
	this->customers_number = customers_number;
	this->tariff_name = tariff_name;
}

void MobileTariff::show_information()
{
	using namespace std;

	char separator = ' ';
	cout << '|' << left << setw(26) << setfill(separator) << tariff_name << "|" << left << setw(12)
		<< setfill(separator) << monthly_fee.value;

	cout << "|" << left << setw(12) << setfill(separator)
		<< internet_traffic.value;

	cout << "|" << left << setw(13) << setfill(separator)
		<< out_calls_min.value;

	cout << "|" << left << setw(13) << setfill(separator)
		<< in_calls_min.value;

	cout << "|" << left << setw(18) << setfill(separator) << customers_number << "|";
}


void MobileTariff::create_random_tariff()
{
	std::random_device rd;
	std::mt19937 mt(rd());

	std::uniform_int_distribution<> dist_fee(0, 1000);
	std::uniform_int_distribution<> dist_internet(0, 1000);
	std::uniform_int_distribution<> dist_out_calls(0, 1000);
	std::uniform_int_distribution<> dist_in_calls(0, 1000);
	std::uniform_int_distribution<> dist_customers_number(0, 1000);
	std::uniform_int_distribution<> dist_tariff(0, names_amount - 1);

	ValueUOM fee;
	fee.value = static_cast<float>(dist_fee(mt));
	ValueUOM internet;
	internet.value = static_cast<float>(dist_internet(mt));
	ValueUOM out_calls;
	out_calls.value = static_cast<float>(dist_out_calls(mt));
	ValueUOM in_calls;
	in_calls.value = static_cast<float>(dist_in_calls(mt));
	int customers_number = dist_customers_number(mt);
	std::string tariff = tariff_names[dist_tariff(mt)];

	this->monthly_fee = fee;
	this->internet_traffic = internet;
	this->out_calls_min = out_calls;
	this->in_calls_min = in_calls;
	this->customers_number = customers_number;
	this->tariff_name = tariff;
}

bool MobileTariff::operator<(const MobileTariff& fee) const
{
	return monthly_fee.value < fee.monthly_fee.value;
}

ValueUOM MobileTariff::get_monthly_fee() { return monthly_fee; }
std::string MobileTariff::get_tariff_name() { return tariff_name; }

void MobileTariff::set_monthly_fee(const ValueUOM& monthly_fee) { this->monthly_fee = monthly_fee; }
void MobileTariff::set_internet_traffic(const ValueUOM& internet_traffic) { this->internet_traffic = internet_traffic; }
void MobileTariff::set_out_calls_min(const ValueUOM& out_calls_min) { this->out_calls_min = out_calls_min; }
void MobileTariff::set_in_calls_min(const ValueUOM& in_calls_min) { this->in_calls_min = in_calls_min; }
void MobileTariff::set_customers_number(const int& number) { this->customers_number = number; }
void MobileTariff::set_tariff_name(const std::string& tariff_name) { this->tariff_name = tariff_name; }

ValueUOM MobileTariff::get_monthly_fee() const { return monthly_fee; }
ValueUOM MobileTariff::get_internet_traffic() const { return internet_traffic; }
ValueUOM MobileTariff::get_out_calls_min() const { return out_calls_min; }
ValueUOM MobileTariff::get_in_calls_min() const { return in_calls_min; }
int MobileTariff::get_customers_number() const { return customers_number; }
std::string MobileTariff::get_tariff_name() const { return tariff_name; }
