/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:49:40 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/09 10:44:13 by phhofman         ###   ########.fr       */
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

void step1(std::vector<unsigned int> &vec, int depth)
{

    size_t pair_size = static_cast<int>(std::pow(2, depth - 1));
    if (pair_size * 2 > vec.size())
        return;

    int pairs = vec.size() / pair_size - ((vec.size() / pair_size) % 2);
    auto start = vec.begin();
    auto end = start + pairs * pair_size;

    for (; start != end; start += pair_size * 2)
    {
        unsigned int left_end = start[pair_size - 1];
        unsigned int right_end = start[pair_size * 2 - 1];
        if (left_end > right_end)
            std::swap_ranges(start, start + pair_size, start + pair_size);
    }
    step1(vec, depth + 1);
    std::vector<unsigned int> the_main;
}

void PmergeMe::sort()
{
    step1(_vec, 1);
}
