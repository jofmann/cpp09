/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:51:21 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/06 11:36:24 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <queue>

class RPN
{
private:
    std::string _notation;

public:
    RPN(const std::string &notation);
    RPN(const RPN &other);
    RPN &operator=(const RPN &other);
    ~RPN();
};