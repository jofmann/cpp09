/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:33:46 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/06 13:32:13 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

class BitcoinExchange::BitcoinExchangeException : public std::runtime_error
{

public:
    explicit BitcoinExchangeException(const std::string &msg)
        : std::runtime_error(msg) {}
    BitcoinExchangeException(const BitcoinExchangeException &) = default;
    BitcoinExchangeException &operator=(const BitcoinExchangeException &) = default;
    BitcoinExchangeException(BitcoinExchangeException &&) noexcept = default;
    BitcoinExchangeException &operator=(BitcoinExchangeException &&) noexcept = default;
    ~BitcoinExchangeException() override = default;
};

BitcoinExchange::BitcoinExchange(const std::string &filepath)
{
    std::ifstream db_file(filepath);
    if (!db_file.is_open())
        throw BitcoinExchangeException("Database Error: Can not open file => " + filepath);

    std::string line;
    int line_pos = 0;
    while (std::getline(db_file, line))
    {
        line_pos++;
        if (!is_valid_line(line, ','))
            throw BitcoinExchangeException("Database Error:  Invalid line => " + line + " on line " + std::to_string(line_pos));
        if (line_pos == 1 && line != "date,exchange_rate")
            throw BitcoinExchangeException("Database Error: Header wrong! Must be 'date,exchange_rate'");
        else if (line_pos == 1)
            continue;
        try
        {
            auto [date, exchange_rate] = get_key_value(line, ',');
            auto [it, succes] = _db.insert({date, exchange_rate});
            if (!succes)
                throw BitcoinExchangeException("Error: date already exists => " + int_to_date(date) + " on line " + std::to_string(line_pos));
        }
        catch (const std::exception &e)
        {
            throw BitcoinExchangeException("Database " + std::string(e.what()) + " on line " + std::to_string(line_pos));
        }
    }
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _db(other._db) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        _db = other._db;
    return *this;
}

std::pair<int, float>
BitcoinExchange::get_entry(int date) const
{
    auto it = _db.lower_bound(date);

    if (it != _db.end() && it->first == date)
        return {it->first, it->second};

    if (it != _db.begin())
    {
        it--;
        return {it->first, it->second};
    }
    throw BitcoinExchangeException("Error: No entry with => " + int_to_date(date));
}

BitcoinExchange::~BitcoinExchange() {}