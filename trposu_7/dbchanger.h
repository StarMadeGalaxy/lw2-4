#pragma once

#include "connector.h"
#include "tariff.h"
#include "stdafx.h"


struct DatabaseAPI : ConnectCreate
{
	const std::string table_name = "tariffs";

	bool add_record(Tariff& tariff)
	{
		
		int monthly_fee = tariff.monthly_fee;
		int internet_traffic = tariff.internet_traffic;
		std::string tariff_name = tariff.tariff_name;

		std::string query = "INSERT INTO " + table_name + 
			" (monthly_fee, internet_traffic, tariff_name) VALUES (" + std::to_string(monthly_fee) +", " +
			std::to_string(internet_traffic) + ", \'" + tariff_name + "\')";

		system("CLS");
		std::cout << "[COMMAND]: " << query << std::endl;

		const char* c_query = query.c_str();
		int query_state = mysql_query(connection, c_query);

		if (!query_state)
		{
			std::cout << "\nQuery added successfully\n";
			return true;
		}
		else
		{
			fprintf(stderr, "\nFailed to create query: Error: %s\n", mysql_error(connection));
			return false;
		}
	}

	bool delete_record(int id)
	{
		std::string query = "DELETE FROM tariffs where id = " + std::to_string(id);
		const char* c_query = query.c_str();
		int query_state = mysql_query(connection, c_query);

		system("CLS");
		std::cout << "[COMMAND]: " << query;

		if (!query_state)
		{
			std::cout << "\n\nQuery added successfully\n";
		}
		else
		{
			fprintf(stderr, "\n\nFailed to create query: Error: %s\n", mysql_error(connection));
			return false;
		}

		std::cout << "\nSuccessfully deleted.";
		return true;
	}

	bool update_record(int id)
	{
		std::cout << "\nChoose the column you would like to change: \n\n"
			<< "   1. monthly_fee\n"
			<< "   2. internet_traffic\n"
			<< "   3. tariff_name\n\n"
			<< "Type here : ";

		std::string query = "UPDATE " + table_name + " SET ";

		int column = 0;
		std::cin >> column;

		std::cout << "\nType new value: ";

		switch (column)
		{
		case 1:
		{
			int new_monthly_fee = 0;
			std::cin >> new_monthly_fee;
			query += "monthly_fee = " + std::to_string(new_monthly_fee) +
				" WHERE id = " + std::to_string(id);
			break;
		}
		case 2:
		{
			int new_internet_traffic = 0;
			std::cin >> new_internet_traffic;
			query += "internet_traffic = " + std::to_string(new_internet_traffic) +
				" WHERE id = " + std::to_string(id);
			break;
		}
		case 3:
		{
			std::string new_tariff_name;
			std::cin >> new_tariff_name;
			query += "tariff_name = \'" + new_tariff_name +
				"\' WHERE id = " + std::to_string(id);
			break;
		}
		default:
			break;
		}

		const char* c_query = query.c_str();
		int query_state = mysql_query(connection, c_query);
		std::cout << "\n[COMMAND]: " << query;

		if (!query_state)
		{
			std::cout << "\n\nQuery added successfully\n";
		}
		else
		{
			fprintf(stderr, "\n\nFailed to create query: Error: %s\n", mysql_error(connection));
			return false;
		}

		//std::cin.ignore(10, '\n');
		return true;
	}

	bool read_records()
	{
		const char* query = "SELECT * FROM tariffs";
		int query_state = mysql_query(connection, query);
		std::cout << "[COMMAND]: " << query;

		if (!query_state)
		{
			std::cout << "\n\nQuery added successfully\n";
		}
		else
		{
			fprintf(stderr, "\n\nFailed to create query: Error: %s\n", mysql_error(connection));
			return false;
		}

		MYSQL_RES* result = mysql_store_result(connection);
		unsigned int field_number = mysql_num_fields(result);

		if (result == NULL)
		{
			fprintf(stderr, "\nFailed to read: Error: %s\n", mysql_error(connection));
			return false;
		}

		printf("\n+-----+--------------------+--------------------+--------------------+\n");
		printf("| ID  |     monthly_fee    |  internet_traffic  |     tariff_name    |\n");
		printf("+-----+--------------------+--------------------+--------------------+\n");

		while (MYSQL_ROW row = mysql_fetch_row(result))
		{
			for (unsigned int i = 0; i < field_number; i++)
			{
				if (i == 0)
				{
					putchar('|');
					printf("%5s", row[i]);
				} else {
					putchar('|');
					printf("%20s", row[i]);
				}
			}
			printf("|\n+-----+--------------------+--------------------+--------------------+\n");
		}

		mysql_free_result(result);
		return true;
	}
};


//enum class CREATION_TYPE
//{
//	RANDOM, MANUAL, NONE
//};