/**
 * \file parrondo.cpp
 * \brief Demonstrating that Game A+B wins.
 *
 * \details
 */

#include <random>
#include <iostream>
#include <set>
#include <algorithm>
#include <functional>
#include "utilities.hpp"

enum SelectGame { SlightlyBadCoin, VeryBadCoin, FavorableCoin, FairCoin };

template<SelectGame S>
bool is_heads(double coin_flip)
{
    const double epsilon = 0.005;
    switch (S)
    {
        case SlightlyBadCoin:
            if ( coin_flip > 0.5 + epsilon )
                return true;
            break;
        case VeryBadCoin:
            if ( coin_flip > 0.9 + epsilon )
                return true;
            break;
        case FavorableCoin:
            if ( coin_flip > .25 + epsilon )
                return true;
            break;
        case FairCoin:
            if ( coin_flip > 0.5 )
                return true;
            break;
    }
    return false;
}

int main(int argc, char* argv[])
{

    std::default_random_engine dre;
    std::uniform_real_distribution<double> coin_flip(0.0,1.0);

    const int nr_trials = 100000;
    const int len_sequence = 100;

    int capital = 0;
    std::vector<double> avg_capital_seq;
    for ( int ix = 0; ix < len_sequence; ++ix )
        avg_capital_seq.push_back(0.0);

    for ( int ix = 0; ix < nr_trials; ++ix )
    {
        for ( int jx = 0; jx < len_sequence; ++jx )
        {
            if (is_heads<FairCoin>(coin_flip(dre)))  // FairCoin decides which to play
                {
                    capital += is_heads<SlightlyBadCoin>(coin_flip(dre)) ? 1 : -1;
                }
            else
                {
                    if ( capital % 3 == 0 )
                        {
                            capital += is_heads<VeryBadCoin>(coin_flip(dre)) ? 1 : -1;
                        }
                    else
                        {
                            capital += is_heads<FavorableCoin>(coin_flip(dre)) ? 1 : -1;
                        }
                }
            avg_capital_seq[jx] += static_cast<double>(capital) / static_cast<double>(nr_trials);
        }
        capital = 0;
    }

    print_elements(avg_capital_seq, "\nAverage Progress of Capital\n");
}
