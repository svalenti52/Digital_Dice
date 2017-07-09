/**
 * \file maltshop.cpp
 *
 */

#include <random>
#include <iostream>

int main()
{

    std::default_random_engine dre;
    std::uniform_real_distribution<double> uniform_dist_over_period(0,30);

    int bill_and_lil_meet = 0;
    const int nr_trials = 10'000'000;

    for ( int ix = 0; ix < nr_trials; ++ix )
        {
            double bill_arrives = uniform_dist_over_period(dre);
            double lil_arrives = uniform_dist_over_period(dre);

            if ( lil_arrives < bill_arrives )
                {
                    if ( (bill_arrives - lil_arrives) <= 5.0 )
                        ++bill_and_lil_meet;
                }
            else
                {
                    if ( (lil_arrives - bill_arrives) <= 7.0 )
                        ++bill_and_lil_meet;
                }
        }

    std::cout << "Bill and Lil Meet: " << bill_and_lil_meet << '\n';
    std::cout << "Prob Bill and Lil Meet: " << static_cast<double>(bill_and_lil_meet)/nr_trials << '\n';
}
