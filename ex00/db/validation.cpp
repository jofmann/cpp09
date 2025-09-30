/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:53:36 by phhofman          #+#    #+#             */
/*   Updated: 2025/09/30 16:44:30 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <regex>
#include <iostream>

bool is_valid_date(const std::string &date) // TODO: Add checks for logical  months days years
{
    static const std::regex pattern(R"(^\d{4}-\d{2}-\d{2}$)");
    return std::regex_match(date, pattern);
}

bool is_valid_exchange_rate(const std::string &exchange_rate)
{
    size_t pos;
    int value = std::stof(exchange_rate, &pos);
    if (pos != exchange_rate.length())
        return false;

    if (value < 0) // TODO: value > 1000 ???
        return false;
    return true;
}

bool is_valid_line(const std::string &line)
{
    size_t pos = line.find(',');
    if (pos == std::string::npos)
        return false;
    if (line.find(',', pos + 1) != std::string::npos)
        return false;
    if (pos == 0 || pos == line.size() - 1)
        return false;
    return true;
}