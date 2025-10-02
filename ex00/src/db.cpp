/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:19:10 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/02 14:30:10 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "db.hpp"
#include "validation.hpp"
#include "utils.hpp"
#include "DatabaseError.hpp"

std::map<int, float> create_db(const std::string &filepath)
{
    std::ifstream db_file(filepath);
    if (!db_file.is_open())
        throw DatabaseError("Database Error: Can not open file => " + filepath);

    std::map<int, float> db_map;
    std::string line;
    int line_pos = 0;
    while (std::getline(db_file, line))
    {
        line_pos++;
        if (!is_valid_line(line, ','))
            throw DatabaseError("Database Error:  Invalid line => " + line + " on line " + std::to_string(line_pos));
        if (line_pos == 1) // TODO: header in csv file necessary ???
            continue;
        try
        {
            auto [date, exchange_rate] = get_key_value(line, ',');
            auto [it, succes] = db_map.insert({date, exchange_rate});
            if (!succes)
                throw std::runtime_error("Error: date already exists => " + int_to_date(date) + " on line " + std::to_string(line_pos));
        }
        catch (const std::exception &e)
        {
            throw DatabaseError("Database " + std::string(e.what()) + " on line " + std::to_string(line_pos));
        }
    }
    return db_map;
}

std::pair<int, float> get_db_entry(const std::map<int, float> &db, int date)
{
    auto it = db.lower_bound(date);

    if (it != db.end() && it->first == date)
        return {it->first, it->second};

    if (it != db.begin())
    {
        it--;
        return {it->first, it->second};
    }
    throw DatabaseError("Error: No entry with => " + int_to_date(date));
}