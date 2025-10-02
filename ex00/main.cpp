/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:41:06 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/02 17:00:32 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void print_bitcoin_price_at_date(const BitcoinExchange &btc, const std::string &filepath)
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
        if (line_pos == 1 && line != "date | value")
            throw std::runtime_error("Error: Error: Header wrong! Must be 'date | value'");
        else if (line_pos == 1)
            continue;
        try
        {
            auto [input_date, value] = get_key_value(line, '|');
            auto [db_date, exchange_rate] = btc.get_entry(input_date);
            std::cout << int_to_date(db_date) << " => " << value << " = " << (exchange_rate * value) << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        std::cerr << "Error: Invalid number of arguments" << std::endl;
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    const std::string filepath = argv[1];
    if (!check_extension(filepath, ".txt"))
    {
        std::cerr << "Error: Filename <" << filepath << "> has wrong extension." << std::endl;
        std::cerr << "Extension must be .txt" << std::endl;
        return 1;
    }

    try
    {
        BitcoinExchange btc("./db/data.csv");
        print_bitcoin_price_at_date(btc, filepath);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}