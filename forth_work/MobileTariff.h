#pragma once
#ifndef _MOBILETARIFF_H_
#define _MOBILETARIFF_H_

#include <string>
#include <iostream>
#include <iomanip>
#include <random>
#include "tariff_names.cpp"
#include "ValueUOM.h"

class MobileTariff
{
private:
	ValueUOM monthly_fee;			// Ежемесячный платеж
	ValueUOM internet_traffic;		// Количество интернета
	ValueUOM out_calls_min;				// Минуты на звонки вне сети
	ValueUOM in_calls_min;				// Минуты на звонки внутри сети
	int customers_number;			// Количество абонентов 
	std::string tariff_name;		// Название тарифа
public:
	MobileTariff();
	MobileTariff(ValueUOM monthly_fee, ValueUOM internet_traffic, ValueUOM out_calls_min,
		ValueUOM in_calls_min, int customers_number, std::string tariff_name);

	void show_information();
	void create_random_tariff();

	bool operator<(const MobileTariff& fee) const;

	ValueUOM get_monthly_fee();
	std::string get_tariff_name();

	void set_monthly_fee(const ValueUOM& monthly_fee);
	void set_internet_traffic(const ValueUOM& internet_traffic);
	void set_out_calls_min(const ValueUOM& out_calls_min);
	void set_in_calls_min(const ValueUOM& in_calls_min);
	void set_customers_number(const int& number);
	void set_tariff_name(const std::string& tariff_name);

	ValueUOM get_monthly_fee() const;
	ValueUOM get_internet_traffic() const;
	ValueUOM get_out_calls_min() const;
	ValueUOM get_in_calls_min() const;
	int get_customers_number() const;
	std::string get_tariff_name() const;
};
#endif	// _MOBILETARIFF_H_