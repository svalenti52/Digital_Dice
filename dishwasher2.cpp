/** \file dishwasher.cpp
 *
 */

#include <random>
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	using dishwasher_t = std::vector<int>;

    std::default_random_engine dre;
    std::uniform_real_distribution<double> uniform_dist_over_unit(0,1);

    int any_breaks_4_or_more = 0;
    const int nr_trials = 10'000'000;
    std::vector<int> dishes{1, 2, 3, 4, 5};

    for ( int ix = 0; ix < nr_trials; ++ix )
    {
        dishwasher_t dishwashers {0, 0, 0, 0, 0};

        for ( auto dish : dishes )
        {
            double rnd_val_in_unit_interval = uniform_dist_over_unit(dre);

            if ( rnd_val_in_unit_interval < .2 )
                ++dishwashers[0];
            else if ( rnd_val_in_unit_interval < .4 )
                ++dishwashers[1];
            else if ( rnd_val_in_unit_interval < .6 )
                ++dishwashers[2];
            else if ( rnd_val_in_unit_interval < .8 )
                ++dishwashers[3];
            else
                ++dishwashers[4];
        }
        int break_more_than_3 = std::count_if(dishwashers.begin(), dishwashers.end(),
            [] (int& i) { if (i > 3) return true; return false; } );

        any_breaks_4_or_more += break_more_than_3;
    }

    std::cout << "Any breaks at least 4 dishes: " << any_breaks_4_or_more << '\n';
    std::cout << "Prob any breaks at least 4 dishes: " << static_cast<double>(any_breaks_4_or_more)/nr_trials << '\n';
}
