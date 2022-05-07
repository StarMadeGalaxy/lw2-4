// trposu_6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// 10. Биржа. На торгах брокеры предлагают акции нескольких фирм. На бирже совершаются 
// действия по купле - продаже акций.В зависимости от количества проданных - купленных 
// акций их цена изменяется.Брокеры предлагают к продаже некоторую часть акций. От активности
// и роста - падения котировок акций изменяется индекс биржи.Биржа может приостановить торги 
// при резком падении индекса.


#include <iostream>
#include <iomanip>
#include <thread>
#include <random>
#include <vector>
#include <mutex>
#include <map>


namespace broker_constants
{
    std::mutex broker_log_mutex;
    const size_t TRADING_TIME = 10;
    const size_t BROKERS_MAX_AMOUNT = 50;
    bool trades_open = false;
}


namespace companies_constants
{
    const size_t AMOUNT = 11;

    const std::string names[AMOUNT] = {
        "Tesla, Inc.", "Advanced Micro Devices, Inc.", "NVIDIA Corporation", "Amazon.com, Inc.", 
        "Meta Platforms, Inc.", "SoundHound AI, Inc.", "Redbox Entertainment Inc.", "Kymera Therapeutics, Inc.",
        "Credit Acceptance Corporation", "EverQuote, Inc.", "IPG Photonics Corporation",
    };
}


struct Broker
{
    size_t id;
    std::map<std::string, size_t> stocks_catalog;

    Broker(size_t arg_id) : id(arg_id)
    {
        std::random_device rd;
        std::mt19937 mt(rd());

        std::uniform_int_distribution<size_t> companies_index_dist(0, companies_constants::AMOUNT - 1);   // индекс для списка имен компаний
        std::uniform_int_distribution<size_t> companies_amount_dist(1, companies_constants::AMOUNT);      // количество различных компаний у брокера
        std::uniform_int_distribution<> stocks_amount_dist(1, 1000000);                    // количество акций

        size_t companies_amount = companies_amount_dist(mt);

        for (size_t i = 0; i < companies_amount; i++)
        {
            size_t companies_index = companies_index_dist(mt);

            while (already_exists(stocks_catalog, companies_constants::names[companies_index]))
                companies_index = companies_index_dist(mt);

            stocks_catalog.insert(std::make_pair(companies_constants::names[companies_index], stocks_amount_dist(mt)));
        }
    }

    void catalog_info(const std::map<std::string, int>& stocks_quotes) const
    {
        using namespace std; 

        for (const auto& record : stocks_catalog)
        {
            auto it = stocks_quotes.find(record.first);
            
            cout << "Stock name: " << left << setw(30) << record.first;
            cout << "| Stock quote: " << left << setw(5) << it->second << '$';
            cout << "| Stocks number: " << left << setw(10) << record.second;
            cout << endl;
        }
    }


    void trade_stock(const std::map<std::string, int>& stocks_quotes, bool output_flag)
    {
    
        // Шанс того что брокер совершит сделку 50%, если число четное, то он купит рандомное число акций
        // если нечетное, то продаст

        while(broker_constants::trades_open)
        {
            std::random_device rd;
            std::mt19937 mt(rd());

            std::uniform_int_distribution<size_t> probability_dist(0, 100);
            size_t key = probability_dist(mt);
                
            if (key > 50)
            {
                std::uniform_int_distribution<size_t> how_much_stocks_dist(20, 99999);
                std::uniform_int_distribution<size_t> how_much_companies_dist(1, companies_constants::AMOUNT);
                std::uniform_int_distribution<size_t> indexes_dist(0, stocks_catalog.size() - 1);

                size_t how_much_companies = how_much_companies_dist(mt);        // количество компаний учавствующее в сделке
                std::vector<size_t> companies_stocks_number;                    // Количество акций для различных компаний
                std::vector<size_t> companies_indexes;                          // Индексы компаний, которые будут участвовать в торгах

                for (size_t i = 0; i < how_much_companies; i++)
                {
                    companies_stocks_number.emplace_back(how_much_stocks_dist(mt));    // Создаем вектор случайного количества акций
                    companies_indexes.emplace_back(indexes_dist(mt));                  // Создаем вектор индексов компаний
                }

                for (size_t i = 0; i < how_much_companies; i++)
                {
                    size_t company_index = companies_indexes[i];
                    size_t stock_number = companies_stocks_number[i];
                    std::string company_name = companies_constants::names[company_index];

                    auto it = stocks_quotes.find(company_name);


                    if (key % 2 == 0)
                    {
                        stocks_catalog[company_name] += stock_number;
                        if (output_flag)
                        {
                            const std::lock_guard<std::mutex> locker(broker_constants::broker_log_mutex);

                            using namespace std;
                            cout << ">>> Broker #" << left << setw(3) << id;
                            cout << " bought    " << left << setw(7) << stock_number;
                            cout << " stock of '" << left << setw(30) << company_name << '\'';
                            cout << " for " << stock_number * it->second << "$\n";
                        }
                    }
                    else
                    {
                        // operator [] inserts pair with zero-value if key does not exists
                        // so output that brokers sells all of broker's stocks
                        bool record_erased = false; 

                        size_t temp = stocks_catalog[company_name];     // Сохраняем начальное количество т.к. 
                        stocks_catalog[company_name] -= stock_number;   // нету отрицательных значений из-за size_t
                        
                        if ((static_cast<int>(temp) - static_cast<int>(stock_number)) <= 0) {  // удаляем полностью запись
                            stocks_catalog.erase(company_name);                                // если уходим в отрицательное количиство
                            record_erased = true;                             
                        }

                        if (output_flag)
                        {
                            const std::lock_guard<std::mutex> locker(broker_constants::broker_log_mutex);

                            using namespace std;
                            cout << ">>> Broker #" << left << setw(3) << id;
                            
                            if (record_erased)
                                cout << " sell      " << left << setw(7) << temp;
                            else
                                cout << " sell      " << left << setw(7) << stocks_catalog[company_name];

                            cout << " stock of '" << left << setw(30) << company_name << '\'';
                            cout << " for " << stock_number * it->second << "$\n";
                        }
                    }
                    key = probability_dist(mt);
                }
            }
        }

        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(2s);
    }


    bool already_exists(const std::map<std::string, size_t>& map, const std::string& string) const
    {
        for (const auto& record : map)
            if (record.first == string)
                return true;
        return false;
    }
};


struct StockExchange
{
    bool STOCK_EXCHANGE_COLLAPSE = false;       // Если true - прекратить торги

    double stock_index = 0.;
    double percentage_change = 0.;

    std::vector<Broker> broker_list;
    std::map<std::string, int> stock_quotes;    // биржа будет устанавливать изначальные значения котировок акций

    size_t broker_amount = 0;

    StockExchange()
    {
        std::random_device rd;
        std::mt19937 mt(rd());

        std::uniform_int_distribution<size_t> broker_amount_dist(5, broker_constants::BROKERS_MAX_AMOUNT);
        std::uniform_int_distribution<int> stock_quote_dist(100, 2500);

        broker_amount = broker_amount_dist(mt);

        // setting initial quotes
        for (size_t i = 0; i < companies_constants::AMOUNT; i++)
            stock_quotes.insert({ companies_constants::names[i], stock_quote_dist(mt) });


        for (size_t i = 0; i < broker_amount; i++)
            broker_list.emplace_back(i + 1);

        bool index_log_flag = false;
        update_index(index_log_flag); // initial stock index
    }

    void brokers_info() const
    {
        for (const auto& broker : broker_list)
        {
            const std::lock_guard<std::mutex> lock(broker_constants::broker_log_mutex);
            std::cout << "BROKER #" << broker.id << ":\n";
            broker.catalog_info(stock_quotes);
            std::cout << std::endl;
        }
    }

    void index_info() const
    {
        const std::lock_guard<std::mutex> lock(broker_constants::broker_log_mutex);

        std::cout << "\nStock index: " << stock_index << std::endl;
        std::cout << "Stock percentage_change: " << percentage_change << "%\n\n";

        if (STOCK_EXCHANGE_COLLAPSE)
            std::cout << "\nBREAKING NEWS! The stock exchange index is down " << std::fabs(percentage_change) << "%.\n";
    }


    void update_quotes()
    {
        ;   // still have no idea how to implement it
    }


    void update_index(bool output_call_flag)             // расчет по формуле арифметичского взвешенного
    {
        do
        {
            double stocks_amount = 0;                    // знаменатель формулы
            double formula_numerator = 0;

            std::map<std::string, size_t> overall_stocks_number;

            for (const auto& broker : broker_list)
            {
                for (const auto& stock : broker.stocks_catalog)
                {
                    stocks_amount += static_cast<double>(stock.second);
                    overall_stocks_number[stock.first] += stock.second;
                }
            }

            for (const auto& stock : overall_stocks_number)
            {
                double appendum = static_cast<double>(stock.second);
                appendum *= static_cast<double>(stock_quotes[stock.first]);
                formula_numerator += appendum;
            }

            double new_index = formula_numerator / stocks_amount;
            percentage_change = 100 - (100 * stock_index / new_index);

            if (percentage_change <= -40.0f)
            {
                STOCK_EXCHANGE_COLLAPSE = true;
                broker_constants::trades_open = false;
            }

            stock_index = new_index;

            if (output_call_flag)
                index_info();
        } while (broker_constants::trades_open);
    } 
};


struct TradeProcess : StockExchange
{
    bool trade_log_flag = true;
    bool index_log_flag = true;    // true - bloody catastrophy

    std::vector<std::thread> trading_process;

    void start_trades()
    {
        broker_constants::trades_open = true;

        // Добавляем брокеров на торги
        for (auto& broker : broker_list)
            trading_process.emplace_back(&Broker::trade_stock, &broker, stock_quotes, trade_log_flag);
        // Добавляем процесс обновления индекс биржи
        trading_process.emplace_back(&TradeProcess::update_index, this, index_log_flag);
    }

    void close_trades()
    {
        broker_constants::trades_open = false;

        for (auto& process : trading_process)
        {
            if (process.joinable())
                process.join();
        }
    }
};


int main()
{
    TradeProcess process;
    
    process.brokers_info();
    process.update_index(true);

    process.start_trades();

    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(2s);

    process.close_trades();
    process.brokers_info();
    process.update_index(true);


    return EXIT_SUCCESS;
}


