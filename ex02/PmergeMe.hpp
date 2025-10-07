/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phhofman <phhofman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:14:59 by phhofman          #+#    #+#             */
/*   Updated: 2025/10/07 16:53:17 by phhofman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <cstring>

class PmergeMe
{
private:
    std::vector<unsigned int> _vec;
    std::list<unsigned int> _list;

public:
    class PmergeMe_exception;
    class PmergeMe_invalid_arg;
    class PmergeMe_out_of_range;

    PmergeMe(char **seq);
    ~PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);

    void sort();
};
