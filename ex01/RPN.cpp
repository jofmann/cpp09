/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:51:12 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/06 11:50:52 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &other) {}

RPN &RPN::operator=(const RPN &other)
{
    return *this;
}

RPN::~RPN() {}

double RPN::evaluate(const std::string &notation)
{
    std::stack<double> stack;
    std::istringstream stream(notation);
    std::string token;

    while (stream >> token)
    {
        if (std::isdigit(token[0]))
        {
            int num = std::stoi(token);
            if (num > 10)
            {
            }
        }
    }
}