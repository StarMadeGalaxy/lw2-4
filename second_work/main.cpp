#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <map>
#include "Places.cpp"


using namespace std;


struct Datetime
{
	int hours;
	int minutes;
	int seconds;
	int day;
	int month;
	int year;
};


class Train
{
private:
	string m_destination;
	int m_train_number;
	Datetime m_departure_time;

	int m_coupe_number;			// купе
	int m_lux_number;			// люкс
	int m_reserved_number;		// плацкарт
	int m_common_number;		// обычные
public:
	Train() : m_destination("None"), m_train_number(0), m_coupe_number(0), 
		m_lux_number(0), m_reserved_number(0), m_common_number(0)
	{
		m_departure_time.day = 12;
		m_departure_time.month = 12;
		m_departure_time.year = 2012;
		m_departure_time.minutes = 59;
		m_departure_time.hours = 23;
		m_departure_time.seconds = 59;
	}

	Train(string destination, int train_number, Datetime departure_time,
		int coupe, int lux, int reserved, int common)
	{
		m_destination = destination;
		m_train_number = train_number;
		m_departure_time = departure_time;
		m_coupe_number = coupe;
		m_lux_number = lux;
		m_reserved_number = reserved;
		m_common_number = common;
	}

	void create_random_train()
	{
		map<int, int> month_days = {
					{1, 31},
					{2, 28},
					{3, 31},
					{4, 30},
					{5, 31},
					{6, 30},
					{7, 31},
					{8, 31},
					{9, 30},
					{10, 31},
					{11, 30},
					{12, 31}
		};

		std::random_device rd;
		std::mt19937 mt(rd());

		// Время
		std::uniform_int_distribution<> dist_day(1, 31);
		std::uniform_int_distribution<> dist_month(1, 12);
		std::uniform_int_distribution<> dist_year(2022, 2030);

		// Дата
		std::uniform_int_distribution<> dist_hours(0, 23);
		std::uniform_int_distribution<> dist_minutes(0, 59);
		std::uniform_int_distribution<> dist_seconds(0, 59);

		// Места и номер поезда
		std::uniform_int_distribution<> dist_train_number(0, 999);
		std::uniform_int_distribution<> dist_common(0, 999);
		std::uniform_int_distribution<> dist_lux(0, 999);
		std::uniform_int_distribution<> dist_reserved(0, 999);
		std::uniform_int_distribution<> dist_coupe(0, 999);

		// Ключ для места 
		std::uniform_int_distribution<> dist_place(0, places_number - 1);

		int place_key = dist_place(mt);

		int hours = dist_hours(mt);
		int minutes = dist_minutes(mt);
		int seconds = dist_seconds(mt);
		int year = dist_year(mt);
		int month = dist_month(mt);
		int day = dist_day(mt);

		m_train_number = dist_train_number(mt);
		m_common_number = dist_common(mt);
		m_lux_number = dist_lux(mt);
		m_reserved_number = dist_reserved(mt);
		m_coupe_number = dist_coupe(mt);

		do {
			day = dist_day(mt);
		} while (day > month_days[month]);

		string new_destination = places[place_key];

		Datetime datetime_to_add = { hours, minutes, seconds, day, month, year };

		m_departure_time = datetime_to_add;
		m_destination = new_destination;
	}

	void show_information()
	{
		map<int, string>number_month = {
				{1,  "Январь"},
				{2,  "Февраль"},
				{3,  "Март"},
				{4,  "Апрель"},
				{5,  "Май"},
				{6,  "Июнь"},
				{7,  "Июль"},
				{8,  "Август"},
				{9,  "Сентябрь"},
				{10, "Октябрь"},
				{11, "Ноябрь"},
				{12, "Декабрь"},
		};

		const char separator = ' ';

		string date = to_string(m_departure_time.day) + ' ' + number_month[m_departure_time.month] + ' ' +
			to_string(m_departure_time.year);

		cout << '|' << left << setw(3) << setfill(separator) << m_train_number
			<< '|' << left << setw(32) << setfill(separator) << m_destination
			<< '|' << right << setw(2) << setfill('0') << to_string(m_departure_time.hours)
			<< ':' << right << setw(2) << setfill('0') << to_string(m_departure_time.minutes) 
			<< ':' << right << setw(2) << setfill('0') << to_string(m_departure_time.seconds)
			<< '|' << left << setw(16) << setfill(separator) << date
			<< '|' << left << setw(6) << setfill(separator) << m_coupe_number
			<< '|' << left << setw(6) << setfill(separator) << m_lux_number
			<< '|' << left << setw(10) << setfill(separator) << m_reserved_number
			<< '|' << left << setw(7) << setfill(separator) << m_common_number << '|';
	}

	string get_destination() { return m_destination; }

	int get_hour() { return m_departure_time.hours; }

	int get_common() { return m_common_number; }
};

class Trainpark
{
private:
	Train* m_trainpark;
	int m_size;
public:
	Trainpark(int size)
	{
		m_trainpark = new Train[size];
		m_size = size;

		int choice = int();

		for (size_t i = 0; i < size; i++)
		{
			cout << "\nВыберите метод добавления поезда [" << i + 1 << "]:"
				<< "\n1. Ввести информацию вручную"
				<< "\n2. Использовать случайные данные"
				<< "\n3. Использовать случайные данные для всех оставшихся поездов\n";

			do {
				cout << "\nВведите: ";
				cin >> choice;
			} while (choice > 3 || choice < 1);

			if (choice == 1)
			{
				string destination = string();
				int train_number = int();
				int hour = int();
				int minute = int();
				int second = int();
				int day = int();
				int year = int();
				int month = int();
				int lux = int();
				int common = int();
				int reserved = int();
				int coupe = int();


				cout << "\nВведите пункт назначения: ";
				cin >> destination;
				cout << "\nВведите номер поезда: ";
				cin >> train_number;
				cout << "\nВведите час отправления: ";
				cin >> hour;
				cout << "\nВведите минуту отправления: ";
				cin >> minute;
				cout << "\nВведите секунда отправления: ";
				cin >> second;
				cout << "\nВведите день отправления: ";
				cin >> day;
				cout << "\nВведите номер месяц отправления: ";
				cin >> month;
				cout << "\nВведите год отправления: ";
				cin >> year;
				cout << "\nВведите количесто люкс мест: ";
				cin >> lux;
				cout << "\nВведите количество плацкартных мест: ";
				cin >> reserved;
				cout << "\nВведите количество общих мест: ";
				cin >> common;
				cout << "\nВведите количество купейных мест: ";
				cin >> coupe;

				Datetime datetime_to_add = { hour, minute, second, day, month, year };

				Train train_to_add(destination, train_number, datetime_to_add, coupe, lux,
					reserved, common);

				m_trainpark[i] = train_to_add;
			}
			else if (choice == 2) {
				Train random_train;
				random_train.create_random_train();
				m_trainpark[i] = random_train;
			}
			else if (choice == 3) {
				for (size_t j = 0; j < size - i; i++)
				{
					Train random_train;
					random_train.create_random_train();
					m_trainpark[i] = random_train;
				}
				break;
			}
		}
	}

	void show_trainpark()
	{
		if (m_trainpark == nullptr)
		{
			cout << "\nTrainpark is empty.\n";
			return;
		}

		cout << "\n+---+--------------------------------+--------+----------------+------+------+----------+-------+"
			 << "\n| № |             Маршрут            | Время  |      Дата      | Купе | Люкс | Плацкарт | Общие |"
			 << "\n+---+--------------------------------+--------+----------------+------+------+----------+-------+\n";

		for (size_t i = 0; i < m_size; i++)
		{
			m_trainpark[i].show_information();
			cout << "\n+---+--------------------------------+--------+----------------+------+------+----------+-------+\n";
		}

	}

	void show_till_destintaion(string dest)
	{
		cout << "\nПоезда которые едут до " << dest << ":"
			<< "\n+---+--------------------------------+--------+----------------+------+------+----------+-------+\n";
		for (size_t i = 0; i < m_size; i++)
		{
			if (m_trainpark[i].get_destination() == dest)
			{
				m_trainpark[i].show_information();
				cout << "\n+---+--------------------------------+--------+----------------+------+------+----------+-------+\n";
			}
		}
	}

	void show_till_after(string dest, int hour)
	{
		cout << "\nПоезда которые едут до " << dest << " после " << hour <<" часа(ов):"
			<< "\n+---+--------------------------------+--------+----------------+------+------+----------+-------+\n";
		for (size_t i = 0; i < m_size; i++)
		{
			Train train = m_trainpark[i];
			if (train.get_destination() == dest && train.get_hour() > hour)
			{
				m_trainpark[i].show_information();
				cout << "\n+---+--------------------------------+--------+----------------+------+------+----------+-------+\n";
			}
		}
	}
	
	void show_till_common(string dest)
	{
		cout << "\nПоезда которые едут до " << dest << " и имеют общие места:"
			<< "\n+---+--------------------------------+--------+----------------+------+------+----------+-------+\n";
		for (size_t i = 0; i < m_size; i++)
		{
			Train train = m_trainpark[i];
			if (train.get_destination() == dest && train.get_common() > 0)
			{
				m_trainpark[i].show_information();
				cout << "\n+---+--------------------------------+--------+----------------+------+------+----------+-------+\n";
			}
		}
	}

	Trainpark() : m_trainpark(nullptr), m_size(0)
	{}

	~Trainpark()
	{
		delete[] m_trainpark;
	}
};



int main()
{
	setlocale(LC_ALL, "rus");

	int size = int();

	do {
		cout << "Введите количество поездов которое хотите добавить: ";
		cin >> size;
	} while (size <= 0);

	Trainpark trainpark(size);

	trainpark.show_trainpark();
	trainpark.show_till_destintaion("Аляска");
	trainpark.show_till_after("Аляска", 14);
	trainpark.show_till_common("Аляска");

	return 0;
}