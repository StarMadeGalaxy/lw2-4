#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


struct Pair
{
    char symbol;
    int amount = 0;

    bool operator<(const Pair& a) const
    {
        return amount < a.amount;
    }
};


class File {
private:
    std::fstream file;
    std::string m_filedata;
    std::string m_filename;
public:
    File(const char* filename)
    {
        file.open(filename, std::fstream::in | std::fstream::out | std::ios::out);
        m_filename = filename;

        if (file.fail())
        {
            std::cerr << "File '" << filename << "' has failed to open.";
        }
    }

    void read_from_file()
    {
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        m_filedata.reserve(size);
        file.seekg(0, std::ios::beg);
        while (file)
        {
            std::string line_buffer;
            std::getline(file, line_buffer);
            m_filedata.append(line_buffer);
        }
        std::cout << m_filedata << std::endl;
    }

    std::string get_filedata()
    {
        return m_filedata;
    }

    void individual_task(const std::string& filedata)
    {
        std::vector<Pair> letters_amount;

        for (size_t i = 0; i < filedata.size(); i++)
        {
            char current_symbol = filedata[i];
            bool in_vector = false;

            for (size_t j = 0; j < letters_amount.size(); j++)
            {
                if (current_symbol == letters_amount[j].symbol)
                {
                    letters_amount[j].amount += 1;
                    in_vector = true;
                    break;
                }
            }

            if (!in_vector)
            {
                Pair pair{ current_symbol, 1 };
                letters_amount.push_back(pair);
            }
        }
        std::sort(letters_amount.begin(), letters_amount.end());

        int amount = 0;
        do {
            std::cout << "\nВведите сколько символом вывести: ";
            std::cin >> amount;
        } while (amount <= 0 || amount > letters_amount.size());

        if (file) {
            for (size_t i = letters_amount.size() - 1; i > letters_amount.size() - 1 - amount; i--)
            {
                std::cout << letters_amount[i].symbol << " - " << letters_amount[i].amount << std::endl;
                file << letters_amount[i].symbol << " - " << letters_amount[i].amount << std::endl;
            }
        }
    }

    void encrypt()
    {
        std::string new_string;
        new_string.reserve(m_filedata.size());
        for (size_t i = 0; i < m_filedata.size(); i++)
        {
            char character = m_filedata[i] + 1;
            new_string.push_back(character);
        }
        std::cout << "\nПеред шифрованием: " << m_filedata << std::endl;
        m_filedata = new_string;
        std::cout << "\nПосле шифрования: " << m_filedata << std::endl;
    }

    void decrypt()
    {
        std::string new_string;
        new_string.reserve(m_filedata.size());
        for (size_t i = 0; i < m_filedata.size(); i++)
        {
            char character = m_filedata[i] - 1;
            new_string.push_back(character);
        }
        std::cout << "\nДо расшифровки: " << m_filedata << std::endl;
        m_filedata = new_string;
        std::cout << "\nПосле расшифровки: " << m_filedata << std::endl;
    }

    ~File()
    {
        file.close();
    }
};


int main()
{
    setlocale(LC_ALL, "rus");

    File input_file("text.txt");
    File output_file("letters.txt");

    input_file.read_from_file();
    input_file.encrypt();
    input_file.decrypt();

    output_file.individual_task(input_file.get_filedata());
    
    return 0;
}

