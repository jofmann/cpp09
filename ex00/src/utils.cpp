/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:51:08 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/02 11:27:25 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "validation.hpp"

float input_value_to_float(const std::string &str)
{
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

int date_to_int(const std::string &date)
{
    // Annahme: date = "YYYY-MM-DD"
    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));

    return year * 10000 + month * 100 + day;
}

std::string int_to_date(int date)
{
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;

    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << year << "-"
        << std::setw(2) << std::setfill('0') << month << "-"
        << std::setw(2) << std::setfill('0') << day;
    return oss.str();
}

void print_map(const std::map<int, float> &map)
{
    int i = 0;
    for (auto it = map.begin(); it != map.end(); it++)
    {
        if (i == 20)
            break;
        std::cout << int_to_date(it->first) << " | " << it->second << std::endl;
        i++;
    }
}

std::string trim_whitespaces(const std::string &str)
{
    size_t start = 0;
    while (start < str.size() && std::isspace(static_cast<unsigned char>(str[start])))
        start++;

    size_t end = str.size();
    while (end > start && std::isspace(static_cast<unsigned char>(str[end - 1])))
        end--;

    return str.substr(start, end - start);
}