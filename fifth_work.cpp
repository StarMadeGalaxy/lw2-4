// trposu_5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <random>


struct Polynomial
{
    std::vector<int> сoefficients;
    size_t degree;

    Polynomial(size_t degree)
    {
        for (int i = static_cast<int>(degree); i >= 0; i--)
        {
            std::cout << "\nEnter coefficient for x" << i << ": ";
            int coefficient = 0;
            std::cin >> coefficient;
            сoefficients.push_back(coefficient);
        }
        this->degree = degree;
    }

    Polynomial()
    {
        std::random_device rd;
        std::mt19937 mt(rd());

        std::uniform_int_distribution<int> random_coefficient(-10, 10);
        std::uniform_int_distribution<size_t> random_degree(0, 10);

        size_t degree = random_degree(mt);

        for (size_t i = 0; i <= degree; i++)
            сoefficients.push_back(random_coefficient(mt));

        this->degree = degree;
    }

    void print()
    {
        for (size_t i = 0; i <= degree; i++)
        {
            if (i == degree)
                if (сoefficients[i] > 0)
                    if (degree != 0)
                        std::cout << "+" << сoefficients[i];
                    else
                        std::cout << сoefficients[i];
                else 
                    std::cout << сoefficients[i];
            else if (сoefficients[i] > 0 && i == 0)
                std::cout << сoefficients[i] << 'x' << degree - i;
            else if (сoefficients[i] > 0)
                std::cout << "+" << сoefficients[i] << 'x' << degree - i;
            else if (сoefficients[i] == 0)
                ;
            else
                std::cout << сoefficients[i] << 'x' << degree - i;
        }
    }


    Polynomial operator*(int const& number)
    {
        Polynomial temp_poly = *this;

        for (int& coef : temp_poly.сoefficients)
            coef *= number;

        return temp_poly;
    }

    Polynomial operator*(Polynomial const& other)
    {
        Polynomial multiplied = *this;
        multiplied.degree += other.degree;
        multiplied.сoefficients.clear();
        multiplied.сoefficients.resize(multiplied.degree + 1);

        for (size_t i = 0; i <= this->degree; i++)
            for (size_t j = 0; j <= other.degree; j++)
                multiplied.сoefficients[i + j] += this->сoefficients[i] * other.сoefficients[j];

        return multiplied;
    }
    
    void operator=(Polynomial const& other)
    {
        this->degree = other.degree;
        this->сoefficients = other.сoefficients;
    }
};


int main()
{
    size_t poly_num = 0;

    std::cout << "Enter amount of pairs: ";
    std::cin >> poly_num;

    std::vector<Polynomial> poly_vec;

    for (size_t i = 0; i < poly_num * 2; i++)
        poly_vec.emplace_back(Polynomial());
    
    for (size_t i = 0; i < poly_vec.size(); i += 2)
    {
        std::cout << "\nFirst polynomial: ";
        poly_vec[i].print();
        std::cout << "\nsecond polynomial: ";
        poly_vec[i + 1].print();
        std::cout << "\nMultiplied: ";
        (poly_vec[i] * poly_vec[i + 1]).print();
        std::cout << std::endl;
    }
    return EXIT_SUCCESS;
}