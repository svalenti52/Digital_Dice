/** \file cointoss.cpp
 *
 */

#include <random>
#include <iostream>
#include <algorithm>

int main(int argn, char* argv[])
{
    if ( argn != 5 )
        {
            std::cout << "the first 3 positions are number of coins for three players and 2 digits (%) for fairness\n";
            return 1;
        }

//    const std::string s4 {argv[4]};
//    std::cout << s4 << '\n';

//    const int i_fairness = std::stoi(s4);
    const int i_fairness = atoi(argv[4]);
    const double fairness = static_cast<double>(i_fairness)/100.0;
    double total_rolls = 0.0;

    std::default_random_engine dre;
//    std::mt19937 dre;
//    std::uniform_int_distribution<int> coin_flip(0,1);
    std::uniform_real_distribution<double> coin_flip(0,1);

    const int nr_trials = 1'000'000;


    for ( int ix = 0; ix < nr_trials; ++ix )
        {
            int coins1 = atoi(argv[1]);
            int coins2 = atoi(argv[2]);
            int coins3 = atoi(argv[3]);

            int nr_rolls_till_out = 0;
            while ( coins1 > 0 && coins2 > 0 && coins3 > 0 )
            {
                ++nr_rolls_till_out;

                int toss1 = coin_flip(dre) < fairness ? 0 : 1;
                int toss2 = coin_flip(dre) < fairness ? 0 : 1;
                int toss3 = coin_flip(dre) < fairness ? 0 : 1;

                //std::cout << ix << " " << nr_rolls_till_out << " " << toss1 << " " << toss2 << " " << toss3 << '\n';

                if ( toss1 == toss2 && toss2 == toss3 ) continue;

                else if ( toss1 == toss2 )
                    {
                        --coins1, --coins2, ++coins3, ++coins3;
                    }
                else if ( toss1 == toss3 )
                    {
                        --coins1, ++coins2, ++coins2, --coins3;
                    }
                else
                    {
                        ++coins1, ++coins1, --coins2, --coins3;
                    }
            }
            total_rolls += static_cast<double>(nr_rolls_till_out);
            //std::cout << total_rolls << '\n';
        }

        std::cout << "number of coin tosses on avg till out = " <<
            total_rolls/static_cast<double>(nr_trials) << '\n';


}
