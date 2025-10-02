/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:09:01 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/02 14:21:23 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btc.hpp"

void print_bitcoin_price_at_date(const std::map<int, float> &db, const std::string &filepath)
{
    std::ifstream input_file(filepath);
    if (!input_file.is_open())
        throw std::runtime_error("Error: Can not open input file '" + filepath + "'");
    std::string line;
    int line_pos = 0;
    while (std::getline(input_file, line))
    {
        line_pos++;
        if (!is_valid_line(line, '|'))
        {
            std::cerr << "Error: bad input => " + line << std::endl;
            continue;
        }
        if (line_pos == 1)
            continue;
        try
        {
            auto [input_date, value] = get_key_value(line, '|');
            auto [db_date, exchange_rate] = get_db_entry(db, input_date);
            std::cout << int_to_date(db_date) << " => " << value << " = " << (exchange_rate * value) << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}
