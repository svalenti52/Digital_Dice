/**
 * \file dishwasher2.cpp
 * \date 13-Mar-2015
 *
 * \brief Probability that any of five dishwashers break 4 or 5 dishes
 * out of 5 broken, given equal skills.
 */

#include <random>
#include <iostream>
#include <algorithm>

int main()
{
	using dishwasher_t = std::vector<int>;

    std::default_random_engine dre;
    std::uniform_real_distribution<double> uniform_dist_over_unit(0,1);

    const int lower_bound_breakage = 3;
    int any_breaks_4_or_more = 0;
    const int nr_trials = 10'000'000;
    std::vector<int> dishes{1, 2, 3, 4, 5};

    for ( int ix = 0; ix < nr_trials; ++ix )
    {
        dishwasher_t dishwashers {0, 0, 0, 0, 0};

        for ( auto dish : dishes )
        {
            double rnd_val_in_unit_interval = uniform_dist_over_unit(dre);

            /**
             * Intervals of 0.2 taken from the unit interval represent the probability
             * a particular dishwasher out of five has broken a dish. Dishwasher #0
             * is assigned the [0, 0.2) interval, Dishwasher #1 is assigned the [0.2, 0.4)
             * interval, etc.
             */
            if ( rnd_val_in_unit_interval < 0.2 )
                ++dishwashers[0];
            else if ( rnd_val_in_unit_interval < 0.4 )
                ++dishwashers[1];
            else if ( rnd_val_in_unit_interval < 0.6 )
                ++dishwashers[2];
            else if ( rnd_val_in_unit_interval < 0.8 )
                ++dishwashers[3];
            else
                ++dishwashers[4];
        }
        int break_more_than_3 = static_cast<int>(std::count_if(dishwashers.begin(), dishwashers.end(),
            [] (int& dishes_broken) { return  (dishes_broken > lower_bound_breakage); } ));

        any_breaks_4_or_more += break_more_than_3;
    }

    std::cout << "Any breaks at least 4 dishes: " << any_breaks_4_or_more << '\n';
    std::cout << "Prob any breaks at least 4 dishes: " << static_cast<double>(any_breaks_4_or_more)/nr_trials << '\n';
}
