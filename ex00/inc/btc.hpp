/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:34:56 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/01 15:40:27 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "validation.hpp"
#include "utils.hpp"
#include "db.hpp"

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdexcept>
#include <utility>

void print_bitcoin_price_at_date(const std::map<int, float> &db, const std::string &filepath);
