/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:51:12 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/06 11:39:11 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(const std::string &notation) : _notation(notation)
{
}

RPN::RPN(const RPN &other) : _notation(other._notation) {}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
        _notation = other._notation;
    return *this;
}

RPN::~RPN() {}