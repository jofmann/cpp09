/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:19:10 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/01 14:09:24 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "db.hpp"
#include "validation.hpp"
#include "utils.hpp"

std::string extract_date(const std::string &line, size_t idx, const std::string &line_pos)
{
    std::string date = line.substr(0, idx);
    if (!is_valid_db_date(date))
        throw std::runtime_error("Invalid date: '" + date + "' (expected YYYY-MM-DD) at pos: " + line_pos);
    return date;
}

float extract_exchange_rate(const std::string &line, size_t idx, const std::string &line_pos)
{
    std::string exchange_rate = line.substr(idx);
    if (!is_valid_db_exchange_rate(exchange_rate))
        throw std::runtime_error("Invalid exchange_rate: " + exchange_rate + " at pos: " + line_pos);
    return std::stof(exchange_rate);
}

std::pair<int, float> extract_key_value(const std::string &line, const std::string &line_pos)
{

    size_t idx = line.find(',');
    std::string date = extract_date(line, idx, line_pos);
    float exchange_rate = extract_exchange_rate(line, idx + 1, line_pos);
    return {date_to_int(date), exchange_rate};
}

std::map<int, float> create_db(const std::string &filepath)
{
    std::ifstream db_file(filepath);
    if (!db_file.is_open())
        throw std::runtime_error("Can not open db file '" + filepath + "'");

    std::map<int, float> db_map;
    std::string line;
    int line_pos = 0;
    while (std::getline(db_file, line))
    {
        if (!is_valid_db_line(line))
            throw std::runtime_error("Invalid line in " + filepath + ": '" + line + "'" + " at pos:" + std::to_string(line_pos));
        line_pos++;
        if (line_pos == 1) // TODO: header in csv file necessary ???
            continue;
        auto [date, exchange_rate] = extract_key_value(line, std::to_string(line_pos));
        auto [it, succes] = db_map.insert({date, exchange_rate});
        if (!succes)
            throw std::runtime_error(" Key already exists ");
    }
    return db_map;
}

std::map<int, float>::iterator get_db_entry(std::map<int, float> db, std::string date)
{
    auto it = db.lower_bound(date_to_int(date));

    if (it != db.end() && it->first == date_to_int(date))
        return it;
    if (it != db.begin())
    {
        it--;
        return it;
    }
    throw std::runtime_error("No earlier date '" + date + "' available");
}