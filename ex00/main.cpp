/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:41:06 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/01 15:40:20 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btc.hpp"

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
        auto db = create_db("./db/data.csv");

        print_bitcoin_price_at_date(db, filepath);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}