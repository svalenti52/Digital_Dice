// forget_burglar.cpp

#include <random>
#include <iostream>
#include <set>
#include <algorithm>
#include <functional>
#include "utilities.hpp"

int main(int argn, char* argv[])
{
    std::default_random_engine dre;
    std::uniform_real_distribution<double> visit_next_sel(0,1);

    const int nr_trials = 1000000;

    std::vector<double> prob_visit_nr_houses { 0.0, 0.0, 0.0, 0.0, // prob visit 1 house, 2 houses, etc.
                                               0.0, 0.0, 0.0, 0.0 }; // 8 houses is considered other (8, 9, 10, etc.)

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
            //tot_nr_houses += static_cast<double>(houses_visited.size());
            if ( houses_visited.size() >= 8 ) prob_visit_nr_houses[8-1] += 1.0;
            else prob_visit_nr_houses[houses_visited.size()-1] += 1.0;
        }

        for ( auto& elem : prob_visit_nr_houses ) elem /= static_cast<double>(nr_trials);
        print_elements(prob_visit_nr_houses, "Probability of number of houses visited 1-7, with 8 being the rest\n");

}
