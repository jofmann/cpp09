/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:49:40 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/14 17:56:04 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

class PmergeMe::PmergeMe_exception : public std::exception
{
    const char *what() const noexcept override
    {
        return "Error: PmergeMe";
    }
};

class PmergeMe::PmergeMe_invalid_arg : public std::invalid_argument
{
public:
    explicit PmergeMe_invalid_arg(const std::string &msg)
        : std::invalid_argument(msg) {}
    PmergeMe_invalid_arg(const PmergeMe_invalid_arg &) = default;
    PmergeMe_invalid_arg &operator=(const PmergeMe_invalid_arg &) = default;
    PmergeMe_invalid_arg(PmergeMe_invalid_arg &&) noexcept = default;
    PmergeMe_invalid_arg &operator=(PmergeMe_invalid_arg &&) noexcept = default;
    ~PmergeMe_invalid_arg() override = default;
};

class PmergeMe::PmergeMe_out_of_range : public std::out_of_range
{
public:
    explicit PmergeMe_out_of_range(const std::string &msg)
        : std::out_of_range(msg) {}
    PmergeMe_out_of_range(const PmergeMe_out_of_range &) = default;
    PmergeMe_out_of_range &operator=(const PmergeMe_out_of_range &) = default;
    PmergeMe_out_of_range(PmergeMe_out_of_range &&) noexcept = default;
    PmergeMe_out_of_range &operator=(PmergeMe_out_of_range &&) noexcept = default;
    ~PmergeMe_out_of_range() override = default;
};

PmergeMe::PmergeMe(char **seq)
{
    int num;
    size_t pos;
    for (int i = 0; seq[i] != NULL; i++)
    {
        std::string str = seq[i];
        try
        {
            num = std::stoi(seq[i], &pos);
            if (pos != str.length())
                throw std::invalid_argument("");
            if (num < 0)
                throw std::out_of_range("");
        }
        catch (const std::invalid_argument &e)
        {
            throw PmergeMe_invalid_arg("Error: invalid argument => " + str);
        }
        catch (const std::out_of_range &e)
        {
            throw PmergeMe_out_of_range("Error: argument out of range => " + str);
        }
        catch (const std::exception &e)
        {
            throw PmergeMe_exception();
        }
        _vec.push_back(num);
        _list.push_back(num);
    }
}

PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _list(other._list) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vec = other._vec;
        _list = other._list;
    }
    return *this;
}

PmergeMe::~PmergeMe()
{
}

void PmergeMe::print_vector()
{
    for (auto it = _vec.begin(); it != _vec.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::print_list()
{
    for (auto it = _list.begin(); it != _list.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
using vector = std::vector<unsigned int>;

void print_v(vector vec)
{
    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
void print_info(int lvl, int elements, int pairs, int element_size)
{
    std::cout << "lvl: " << lvl << " elements: " << elements << " pairs: " << pairs << " element_size: " << element_size << std::endl;
}

void step2(vector &main_chain, vector &pend, vector vec, size_t element_size, int elements)
{
    auto start = vec.begin();
    auto end = start + element_size * 2;
    main_chain.insert(main_chain.end(), start, end);
    start = end;
    end = start + element_size;
    // insert pairs in main or pend
    for (int i = 3; i <= elements; i++)
    {
        if (i % 2 == 0)
        {
            main_chain.insert(main_chain.end(), start, end);
        }
        else
        {
            pend.insert(pend.end(), start, end);
        }
        start += element_size;
        end = start + element_size;
    }
}

unsigned int jacobsthal(unsigned int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

std::iterator left_bound(const vector &main_chain, int element_size, int target)
{
    size_t elements = main_chain.size() / element_size;

    if (target >= elements)
        return main_chain.end();

    auto start = main_chain.begin() + (element_size * 2);

    for (auto it = start; it != main_chain.end(); it += element_size)
    {
        }
}

void step3(vector &main_chain, vector &pend, int element_size)
{
    unsigned int n = 3;
    unsigned int insertions = jacobsthal(n) - jacobsthal(n - 1);

    unsigned int i = 1;
    auto it = pend.begin();
    while (it != pend.end() && i < n)
    {
        it += element_size;
        i++;
    }

    size_t elements_in_main = main_chain.size() / element_size;
    if (elements_in_main >)
        while (pend.size() > element_size * insertions)
        {
            insertions--;
        }
}

void step1(vector &vec, int depth)
{

    size_t element_size = static_cast<int>(std::pow(2, depth - 1));
    if (element_size * 2 > vec.size())
        return;

    int elements = vec.size() / element_size;
    int pairs = vec.size() / element_size - ((vec.size() / element_size) % 2);
    auto start = vec.begin();
    auto end = start + pairs * element_size;

    for (; start != end; start += element_size * 2)
    {
        unsigned int left_end = start[element_size - 1];
        unsigned int right_end = start[element_size * 2 - 1];
        if (left_end > right_end)
            std::swap_ranges(start, start + element_size, start + element_size);
    }
    step1(vec, depth + 1);
    vector main_chain;
    vector pend;
    print_info(depth, elements, pairs, element_size);

    step2(main_chain, pend, vec, element_size, elements);
    std::cout << "main: ";
    print_v(main_chain);
    std::cout << "pend: ";
    print_v(pend);
    std::cout << std::endl;
}

void PmergeMe::sort()
{
    step1(_vec, 1);
}
