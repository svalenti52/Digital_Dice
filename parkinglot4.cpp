// parkinglot4.cpp

#include <random>
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{

    std::default_random_engine dre;
//    std::mt19937 dre;
    std::uniform_real_distribution<double> uniform_dist_over_unit(0,1);

    const int nr_trials = 1'000'000;
    double accum_prob = 0.0;

    for ( int ix = 0; ix < nr_trials; ++ix )
        {
            std::vector<double> parking_lot
                {
                    uniform_dist_over_unit(dre),
                    uniform_dist_over_unit(dre),
                    uniform_dist_over_unit(dre),
                    uniform_dist_over_unit(dre)
                };

            std::sort(parking_lot.begin(), parking_lot.end());

            std::vector<double> diffs
                {
                    parking_lot[1] - parking_lot[0],
                    parking_lot[2] - parking_lot[1],
                    parking_lot[3] - parking_lot[2]
                };

            if ( diffs[0] < diffs[1] && diffs[1] > diffs[2] )
                accum_prob += 1.0;
            else
                {
                    accum_prob += 0.5;
                }
        }

        std::cout << "probability of mutual_nearest_neighbor = " <<
            accum_prob / static_cast<double>(nr_trials) << '\n';


}
