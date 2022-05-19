#include "stdafx.h"
#include "dbchanger.h"

int main()
{
	DatabaseAPI database;

	while (true)
	{
		system("CLS");

		std::cout << "TARIFF DATABASE\n\n"
			<< "   1. Create record\n"
			<< "   2. Read records\n"
			<< "   3. Update record\n"
			<< "   4. Delete record\n"
			<< "   5. Exit\n\n"
			<< "Type here : ";

		int result = 0;

		std::cin >> result;
		std::cin.ignore(10, '\n');

		switch (result)
		{
		case 1:	// create
		{
			Tariff tariff;
			bool creation = true;

			while (creation)
			{
				system("CLS");

				std::cout << "Choose creation type: \n\n"
					<< "   1. Manual\n"
					<< "   2. Random\n\n"
					<< "Type here: ";

				int c_result = 0;
				std::cin >> c_result;
				std::cin.ignore(10, '\n');
				system("CLS");

				switch (c_result)
				{
				case 1:
					tariff.manual_data();
					database.add_record(tariff);
					creation = false;
					std::cin.ignore(10, '\n');
					break;
				case 2:
					tariff.random_data();
					database.add_record(tariff);
					creation = false;
					break;
				default:
					break;
				}
			}

			std::cout << "\n\nPress enter to continue...";
			std::cin.get();
			break;
		}
		case 2:	// record
		{
			system("CLS");
			database.read_records();
			std::cout << "\n\nPress enter to continue...";
			std::cin.get();
			break;
		}
		case 3:	// update
		{
			system("CLS");

			database.read_records();

			std::cout << "\nEnter id of the row you would like to update: ";

			int id = 0;
			std::cin >> id;
			std::cin.ignore(10, '\n');

			database.update_record(id);

			std::cout << "\n\nPress enter to continue...";
			std::cin.ignore(10, '\n');
			std::cin.get();
			break;
		}
		case 4:	// delete
		{
			system("CLS");
			database.read_records();
			std::cout << "\nEnter id of the row you would like to delete: ";
			int id;
			std::cin >> id;
			database.delete_record(id);
			std::cout << "\n\nPress enter to continue...";
			std::cin.ignore(10, '\n');
			std::cin.get();
			break;
		}
		case 5:
		{
			return EXIT_SUCCESS;
			break;
		}
		default:
		{
			break;
		}
		}
	}

	return EXIT_SUCCESS;
}