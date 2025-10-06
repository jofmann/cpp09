/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:51:12 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/06 15:26:58 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &other) { (void)other; }

RPN &RPN::operator=(const RPN &other)
{
    (void)other;
    return *this;
}

RPN::~RPN() {}

bool is_valid_operation(const std::string &op)
{
    if (op == "+" || op == "-" || op == "*" || op == "/")
        return true;
    return false;
}

bool is_negative_num(const std::string &num)
{
    if ((num.size() > 1 && num[0] == '-' && std::isdigit(num[1])))
        return true;
    return false;
}

int convert_token_to_int(const std::string &token)
{
    size_t pos;
    int num;

    try
    {
        num = std::stoi(token, &pos);
    }
    catch (const std::exception &e)
    {
        throw std::invalid_argument("Error: invalid number => " + token);
    }
    if (pos != token.length())
        throw std::invalid_argument("Error: invalid number => " + token);
    if (num > 10 || num < -10)
        throw std::invalid_argument("Error: number out of range => " + token);
    return num;
}

float RPN::evaluate(const std::string &notation)
{
    std::stack<float> stack;
    std::istringstream stream(notation);
    std::string token;

    while (stream >> token)
    {
        if (std::isdigit(token[0]) || is_negative_num(token))
        {
            int num = convert_token_to_int(token);
            stack.push(static_cast<float>(num));
        }
        else
        {
            if (!is_valid_operation(token))
                throw std::invalid_argument("Error: invalid operator => " + token);
            if (stack.size() < 2)
                throw std::invalid_argument("Error: not enough operands");
            float b = stack.top();
            stack.pop();
            float a = stack.top();
            stack.pop();
            if (token == "+")
                stack.push(a + b);
            else if (token == "-")
                stack.push(a - b);
            else if (token == "*")
                stack.push(a * b);
            else if (token == "/")
            {
                if (b == 0)
                    throw std::invalid_argument("Error: division by zero");
                stack.push(a / b);
            }
        }
    }
    if (stack.size() != 1)
        throw std::invalid_argument("Error: invalid expression");
    return stack.top();
}