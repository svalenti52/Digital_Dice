/**
 * \file cointoss1.cpp
 * \date 17-Jun-2017
 *
 */

#include <random>
#include <iostream>
#include <algorithm>
#include <val/montecarlo/MCS_Integer.h>
#include <val/util.h>

int main(int argn, char* argv[])
{
    if ( argn != 5 )
    {
        std::cout << "the first 3 positions are number of coins for three players and 2 digits (%) for fairness\n";
        return 1;
    }

    int coins1 = atoi(argv[1]);
    int coins2 = atoi(argv[2]);
    int coins3 = atoi(argv[3]);
    int i_fairness = atoi(argv[4]);

    std::vector<int> i_state_vector {coins1, coins2, coins3};

    MCS_Integer mcs_integer(10'000'000, 1, 2, 3,
            [&mcs_integer](std::vector<int>& coin_toss, std::vector<int>& stake) -> bool {
                while ( std::none_of(
                        stake.begin(),
                        stake.end(),
                        [](int cash) { return cash == 0; } ) ) {
                    if ( coin_toss[0] == coin_toss[1] && coin_toss[1] == coin_toss[2] );
                    else if ( coin_toss[0] == coin_toss[1] ) {
                        --stake[0];
                        --stake[1];
                        ++stake[2];
                        ++stake[2];
                    }
                    else if ( coin_toss[0] == coin_toss[2] ) {
                        --stake[0];
                        --stake[2];
                        ++stake[1];
                        ++stake[1];
                    }
                    else if ( coin_toss[1] == coin_toss[2] ) {
                        --stake[1];
                        --stake[2];
                        ++stake[0];
                        ++stake[0];
                    }
                    mcs_integer.increment_interim_value();
                    mcs_integer.random_events.reload_random_values();
                }
                return true;
            } );

    mcs_integer.load_integer_state_vector(i_state_vector);

    mcs_integer.change_message("number of flips till one is out = ");

    StopWatch stopWatch;

    mcs_integer.run();

    std::cout << "three players have = ";
    for ( int i : mcs_integer.initial_state_vector )
        std::cout << i << " ";
    std::cout << "  coins\n\n";


    mcs_integer.print_result();

    stopWatch.stop();

}
