#pragma once

#include "stdafx.h"


static const int names_amount = 13;

static const char* tariff_names[names_amount] =
{
	"Drive20", "Drive5", "Victory",
	"NoLimits20", "DataSharing", "GIGA30",
	"GIGA100", "UnlimXS", "NoExtraFees", "SmartUnlimited",
	"BuisnessClass", "EasierThanEasy", "Social"
};

struct Tariff
{
	int monthly_fee = 0;
	int internet_traffic = 0;
	std::string tariff_name;


	void random_data()
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<> monthly_fee_dist(100, 500);
		std::uniform_int_distribution<> int_traffic_dist(1000, 5000);
		std::uniform_int_distribution<> tariff_name_dist(0, names_amount - 1);

		this->monthly_fee = monthly_fee_dist(mt);
		this->internet_traffic = int_traffic_dist(mt);
		this->tariff_name = tariff_names[tariff_name_dist(mt)];
	}

	void manual_data()
	{
		std::cout << "Enter monthly fee: ";
		std::cin >> monthly_fee;
		std::cout << "\nEnter internet traffic: ";
		std::cin >> internet_traffic;
		std::cout << "\nEnter tariff name: ";
		std::cin >> tariff_name;
	}

	Tariff (int monthly_fee, int internet_traffic, std::string tariff_name) :
		monthly_fee(monthly_fee), internet_traffic(internet_traffic), tariff_name(tariff_name)
	{}

	Tariff(){}
};