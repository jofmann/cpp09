/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:09:01 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/02 11:28:32 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btc.hpp"

std::string extract_input_date(const std::string &line, size_t idx)
{
    std::string date = trim_whitespaces(line.substr(0, idx));
    if (!is_valid_db_date(date))
        throw std::runtime_error("Error: invalid date => " + date);
    return date;
}

float extract_input_value(const std::string &line, size_t idx)
{
    std::string str = trim_whitespaces(line.substr(idx));

    size_t pos;
    float value = std::stof(str, &pos);
    if (pos != str.length())
        throw std::runtime_error("Error: not a number => " + str);
    if (value < 0)
        throw std::runtime_error("Error: not a positive number => " + str);
    if (value > 1000)
        throw std::runtime_error("Error: too large a number => " + str);
    return value;
}

std::pair<int, float> get_key_value(const std::string &line)
{
    size_t idx = line.find('|');
    std::string date = extract_input_date(line, idx);
    float value = extract_input_value(line, idx + 1);
    return {date_to_int(date), value};
}

void print_bitcoin_price_at_date(const std::map<int, float> &db, const std::string &filepath)
{
    std::ifstream input_file(filepath);
    if (!input_file.is_open())
        throw std::runtime_error("Can not open input file '" + filepath + "'");
    std::string line;
    int line_pos = 0;
    while (std::getline(input_file, line))
    {
        line_pos++;
        if (!is_valid_input_line(line))
        {
            std::cerr << "Error: bad input => " + line << std::endl;
            continue;
        }
        if (line_pos == 1)
            continue;
        try
        {
            auto [input_date, value] = get_key_value(line);
            auto [db_date, exchange_rate] = get_db_entry(db, input_date);
            std::cout << int_to_date(db_date) << " => " << value << " = " << (exchange_rate * value) << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}
