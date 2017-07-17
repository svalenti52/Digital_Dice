/** \file dishwasher.cpp
 *
 */

#include <random>
#include <iostream>

int main()
{

    std::default_random_engine dre;
    std::uniform_real_distribution<double> uniform_dist_over_unit(0,1);

    int clumsy_breaks_4_or_more = 0;
    const int nr_trials = 10000000;
    const int dishes_broken = 5;
    const double probability_clumsy_breaks_if_random = 0.2;

    for ( int ix = 0; ix < nr_trials; ++ix )
    {
        int clumsy_break_count = 0;

        for ( int jx = 0; jx < dishes_broken; ++jx )
        {
            double rnd_val_in_unit_interval = uniform_dist_over_unit(dre);

            if ( rnd_val_in_unit_interval < probability_clumsy_breaks_if_random )
                /// no magic code allowed in conditional check! - MarekC
                ++clumsy_break_count;
        }

        if ( clumsy_break_count > 3 )
            ++clumsy_breaks_4_or_more;
    }

    std::cout << "Clumsy breaks at least 4 dishes: " << clumsy_breaks_4_or_more << '\n';
    std::cout << "Prob Clumsy breaks at least 4 dishes: " << static_cast<double>(clumsy_breaks_4_or_more)/nr_trials << '\n';
}
