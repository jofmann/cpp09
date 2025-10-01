/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:09:01 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/01 13:46:15 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.hpp"

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdexcept>
#include <utility>

// std::string get_date(const std::string &line, size_t idx, const std::string &line_pos)
// {
//     std::string date = line.substr(0, idx);
//     if (!is_valid_db_date(date))
//         throw std::runtime_error("Invalid date: '" + date + "' (expected YYYY-MM-DD) at pos: " + line_pos);
//     return date;
// }

// float get_value(const std::string &line, size_t idx, const std::string &line_pos)
// {
//     std::string value = line.substr(idx);
//     if (!is_valid_input_value(value))
//         throw std::runtime_error("Invalid value: " + value + " at pos: " + line_pos);
//     return std::stof(value);
// }

// std::pair<std::string, float> get_key_value(const std::string &line, const std::string &line_pos)
// {

//     size_t idx = line.find('|');
//     std::string key = get_date(line, idx, line_pos);
//     float value = get_value(line, idx + 1, line_pos);
//     return {key, value};
// }

// void _transactions(const std::string &filepath)
// {
//     std::ifstream input_file(filepath);

//     if (!input_file.is_open())
//         throw std::runtime_error("Can not open input file '" + filepath + "'");

//     std::string line;
//     int line_pos = 0;
//     while (std::getline(input_file, line))
//     {
//         if (!is_valid_input_value(line))
//             throw std::runtime_error("Invalid line in " + filepath + ": '" + line + "'" + " at pos:" + std::to_string(line_pos));
//         line_pos++;
//         if (line_pos == 1)
//             continue;
//         auto [date, value] = get_key_value(line, std::to_string(line_pos));
//         auto [it, succes] = input_map.insert({date, value});
//         if (!succes)
//             throw std::runtime_error(" Key already exists ");
//     }
// }