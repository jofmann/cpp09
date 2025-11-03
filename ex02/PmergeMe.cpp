/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:49:40 by phhofman          #+#    #+#             */
/*   Updated: 2025/11/03 13:47:31 by phhofman         ###   ########.fr       */
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

class PmergeMe::PmergeMe_not_sorted : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Error: Container is not sorted!";
    }
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
        _deque.push_back(num);
    }
}

PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _deque(other._deque) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vec = other._vec;
        _deque = other._deque;
    }
    return *this;
}

PmergeMe::~PmergeMe()
{
}

vector PmergeMe::get_vector() const
{
    return _vec;
}
deque PmergeMe::get_deque() const
{
    return _deque;
}

void PmergeMe::print_vector(size_t limit) const
{
    for (auto it = _vec.begin(); it != _vec.end(); it++)
    {
        if (limit <= 0)
        {
            std::cout << "...";
            break;
        }
        std::cout << *it << " ";
        limit--;
    }
    std::cout << std::endl;
}

void PmergeMe::print_deque(size_t limit) const
{
    for (auto it = _deque.begin(); it != _deque.end(); it++)
    {
        if (limit <= 0)
        {
            std::cout << "...";
            break;
        }
        std::cout << *it << " ";
        limit--;
    }
    std::cout << std::endl;
}

void PmergeMe::sort_vector()
{
    size_t old_size = _vec.size();
    std::cout << "Before : ";
    print_vector(15);

    auto start = std::chrono::high_resolution_clock::now();
    ford_johnson(_vec, 1);
    auto end = std::chrono::high_resolution_clock::now();

    if (!std::is_sorted(_vec.begin(), _vec.end()))
        throw PmergeMe_not_sorted();

    if (old_size != _vec.size())
        throw PmergeMe_exception();

    std::cout << "After  : ";
    print_vector(15);

    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double duration_us = duration_ns / 1000.0;

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << _vec.size() << " with std::vector : " << duration_us << " us" << std::endl;
}

void PmergeMe::sort_deque()
{
    size_t old_size = _deque.size();
    std::cout << "Before : ";
    print_deque(15);

    auto start = std::chrono::high_resolution_clock::now();
    ford_johnson(_deque, 1);
    auto end = std::chrono::high_resolution_clock::now();

    if (!std::is_sorted(_deque.begin(), _deque.end()))
        throw PmergeMe_not_sorted();

    if (old_size != _deque.size())
        throw PmergeMe_exception();

    std::cout << "After  : ";
    print_deque(15);

    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double duration_us = duration_ns / 1000.0;

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << _deque.size() << " with std::deque : " << duration_us << " us" << std::endl;
}
