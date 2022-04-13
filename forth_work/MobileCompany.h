#pragma once
#ifndef _MOBILECOMPANY_H_
#define _MOBILECOMPANY_H_

#include <vector>
#include <algorithm>
#include "MobileTariff.h"
#include "ValueUOM.h"


class MobileCompany
{
private:
	std::vector<MobileTariff> tariff_list;
	size_t subscriber_amount;
public:
	MobileCompany(size_t size);

	void sort_tariff_list();
	void count_subscribers();
	void show_tariffs();

	void set_tariff_list(std::vector<MobileTariff> tariff);
	void set_subscriber_amount(const int& amount);

	std::vector<MobileTariff> get_tariff_list() const;
	size_t get_subscriber_amount() const;
};

#endif		// _MOBILECOMPANY_H_