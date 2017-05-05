// umbrella.cpp

#include <vector>
#include <iostream>
#include <random>
#include <string>
#include "utilities.hpp"

int main()
{
    std::default_random_engine dre;
    std::uniform_real_distribution<double> is_raining_cmp(0.0, 100.0);
    bool is_raining;
    const int nr_trials = 10'000;
    std::vector<double> avg_days_till_soaked;

	for ( int rain_pct = 1; rain_pct < 100; ++rain_pct )
	{
        int tot_nr_days_dry = 0;

		for (int j = 0; j < nr_trials; j++)
		{
            int nr_umbrellas_at_home = 2;
            int nr_umbrellas_at_office = 2;
            bool at_home = true;
            int nr_days_dry = 0;

			while (true)
			{
			    if ( is_raining_cmp(dre) < rain_pct ) is_raining = true;
			    else is_raining = false;

                if ( is_raining )
                    {
                        if ( at_home )
                            {
                                 if ( nr_umbrellas_at_home == 0 ) break;
                                 else
                                    {
                                        --nr_umbrellas_at_home;
                                        ++nr_umbrellas_at_office;
                                    }
                            }
                        else if ( !at_home )
                            {
                                if ( nr_umbrellas_at_office == 0 ) break;
                                else
                                    {
                                        --nr_umbrellas_at_office;
                                        ++nr_umbrellas_at_home;
                                    }
                            }
                    }
                 at_home = !at_home;
                 ++nr_days_dry;
			}
            tot_nr_days_dry += nr_days_dry;
		}
        avg_days_till_soaked.push_back(static_cast<double>(tot_nr_days_dry)/static_cast<double>(nr_trials));
        std::cout << rain_pct << '\n';
	}

    print_elements(avg_days_till_soaked,"\n\nAVG DAYS TILL SOAKED BY INC PCT PROB WILL RAIN\n");
}
