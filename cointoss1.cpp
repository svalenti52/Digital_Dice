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
            [&mcs_integer](std::vector<int>& random_vec, std::vector<int>& state) -> bool {
                while ( std::none_of(
                        state.begin(),
                        state.end(),
                        [](double d) { return d == 0; } ) ) {
                    if ( random_vec[0] == random_vec[1] && random_vec[1] == random_vec[2] );
                    else if ( random_vec[0] == random_vec[1] ) {
                        --state[0];
                        --state[1];
                        ++state[2];
                        ++state[2];
                    }
                    else if ( random_vec[0] == random_vec[2] ) {
                        --state[0];
                        --state[2];
                        ++state[1];
                        ++state[1];
                    }
                    else if ( random_vec[1] == random_vec[2] ) {
                        --state[1];
                        --state[2];
                        ++state[0];
                        ++state[0];
                    }
                    mcs_integer.interim_count += 1.0;
                    mcs_integer.random_event.reload_random_values();
                }
                return true;
            } );

    mcs_integer.load_integer_state_vector(i_state_vector);

    StopWatch stopWatch;

    mcs_integer.run();

    std::cout << "state vector = ";
    for ( int i : mcs_integer.permanent_state_vector )
        std::cout << i << " ";
    std::cout << "\n\n";


    mcs_integer.print_result();

    stopWatch.stop();

}
