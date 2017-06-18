/**
 * \file cointoss1.cpp
 * \date 17-Jun-2017
 *
 */

#include <random>
#include <iostream>
#include <algorithm>
#include <val/montecarlo/MCS_Integer.h>

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
            [&mcs_integer](std::vector<int>& vi, std::vector<int>& state) -> bool {
                while ( std::none_of(
                        state.begin(),
                        state.end(),
                        [](double d) { return d == 0; } ) ) {
                    //for ( int i : vi )
                    //    std::cout << i << " ";
                    if ( vi[0] == vi[1] && vi[1] == vi[2] );
                    else if ( vi[0] == vi[1] ) {
                        --state[0];
                        --state[1];
                        ++state[2];
                        ++state[2];
                    }
                    else if ( vi[0] == vi[2] ) {
                        --state[0];
                        --state[2];
                        ++state[1];
                        ++state[1];
                    }
                    else if ( vi[1] == vi[2] ) {
                        --state[1];
                        --state[2];
                        ++state[0];
                        ++state[0];
                    }
                    mcs_integer.interim_count += 1.0;
                    //for ( int i : state )
                      //  std::cout << i << " ";
                    //std::cout << "roll ";
                    mcs_integer.random_event.reload_random_integers();
                }
                //std::cout << "\n";
                //std::string s;
                //std::cin >> s;
                return true;
            } );


    mcs_integer.load_integer_state_vector(i_state_vector);


    mcs_integer.run();

    std::cout << "state vector = ";
    for ( int i : mcs_integer.permanent_state_vector )
        std::cout << i << " ";
    std::cout << "\n\n";


    mcs_integer.print_result();


//    const std::string s4 {argv[4]};
//    std::cout << s4 << '\n';

//    const int i_fairness = std::stoi(s4);
/*    const int i_fairness = atoi(argv[4]);
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
*/

}
