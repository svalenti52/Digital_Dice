/**
 * \file forget_burglar.cpp
 *
 */

#include <random>
#include <iostream>
#include <set>
#include <algorithm>
#include <functional>
#include <chrono>
#include "utilities.hpp"
#include <val/montecarlo/Chronology.h>

int main(int argn, char* argv[])
{
    std::default_random_engine dre;
    std::uniform_real_distribution<double> visit_next_sel(0,1);

    const int nr_trials = 10'000'000;

    std::vector<double> prob_revisit_in_steps { 0.0, 0.0, 0.0, 0.0, // probability of revisiting a house in 1-7 steps
                                               0.0, 0.0, 0.0, 0.0 }; // 8 steps is considered other (8, 9, 10, etc.)

    StopWatch stopWatch;

    for ( int ix = 0; ix < nr_trials; ++ix )
        {
            std::set<int> houses_visited;
            houses_visited.insert(0);
            int pos = 0;

            while ( true )
            {
                double dir_and_nr_hops = visit_next_sel(dre);

                if ( dir_and_nr_hops < 0.25 ) --pos, --pos;
                else if ( dir_and_nr_hops < 0.5 ) --pos;
                else if ( dir_and_nr_hops < 0.75 ) ++pos;
                else ++pos, ++pos;

                if ( std::find(houses_visited.begin(), houses_visited.end(), pos) != houses_visited.end() )
                    break;
                else
                    houses_visited.insert(pos);
            }
            if ( houses_visited.size() >= 8 ) prob_revisit_in_steps[8-1] += 1.0;
            else prob_revisit_in_steps[houses_visited.size()-1] += 1.0;
        }

    stopWatch.stop();


    for ( auto& elem : prob_revisit_in_steps ) elem /= static_cast<double>(nr_trials);

    print_elements(prob_revisit_in_steps,
                "Probability of that he revisits house for 1-7 steps, with 8 being the rest\n");

        double tot_prob = 0.0;
        for (auto& elem : prob_revisit_in_steps )
            tot_prob += elem;
        std::cout << "\n\nProbabilities sum to = " << tot_prob << '\n';
}
