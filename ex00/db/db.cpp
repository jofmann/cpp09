/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:19:10 by phhofman          #+#    #+#             */
/*   Updated: 2025/09/30 16:49:33 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdexcept>
#include <utility>
#include "db.hpp"

std::string get_date(const std::string &line, size_t idx, const std::string &line_pos)
{
    std::string date = line.substr(0, idx);
    if (!is_valid_date(date))
        throw std::runtime_error("Invalid date: '" + date + "' (expected YYYY-MM-DD) at pos: " + line_pos);
    return date;
}

float get_exchange_rate(const std::string &line, size_t idx, const std::string &line_pos)
{
    std::string exchange_rate = line.substr(idx);
    if (!is_valid_exchange_rate(exchange_rate))
        throw std::runtime_error("Invalid exchange_rate: " + exchange_rate + " at pos: " + line_pos);
    return std::stof(exchange_rate);
}

std::pair<std::string, float> get_key_value(const std::string &line, const std::string &line_pos)
{

    size_t idx = line.find(',');
    std::string key = get_date(line, idx, line_pos);
    float value = get_exchange_rate(line, idx + 1, line_pos);
    return {key, value};
}

std::map<std::string, float> create_db(const std::string &filename)
{
    std::ifstream db_file(filename);
    std::map<std::string, float> db_map;
    if (!db_file.is_open())
        throw std::runtime_error("Can not open '" + filename + "'");

    std::string line;
    int line_pos = 0;
    while (std::getline(db_file, line))
    {
        if (!is_valid_line(line))
            throw std::runtime_error("Invalid line: '" + line + "'" + " at pos:" + std::to_string(line_pos));
        line_pos++;
        if (line_pos == 1) // TODO: header in csv file necessary ???
            continue;
        auto [date, exchange_rate] = get_key_value(line, std::to_string(line_pos));
        auto [it, succes] = db_map.insert({date, exchange_rate});
        if (!succes)
            throw std::runtime_error(" Key already exists ");
    }
    return db_map;
}