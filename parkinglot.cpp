/**
 * \file parkinglot.cpp
 * \date 24-Sep-14
 *
 */

#include <random>
#include <iostream>
#include <vector>
#include <algorithm>

void set_if_mutual_nearest_neighbors_begin(std::vector<std::pair<double,bool>>& p_lot)
    {
        if ( p_lot[1].first - p_lot[0].first <
             p_lot[2].first - p_lot[1].first )
            {
                p_lot[0].second = true;
                p_lot[1].second = true;
            }

    }

bool set_if_mutual_nearest_neighbors_end(std::vector<std::pair<double,bool>>& p_lot)
    {
        int end_pos = static_cast<int>(p_lot.size()-1);
        if ( p_lot[end_pos-1].first - p_lot[end_pos-2].first >
             p_lot[end_pos].first - p_lot[end_pos-1].first )
            {
                p_lot[end_pos-1].second = true;
                p_lot[end_pos].second = true;
                return true;
            }
        return false;
    }

void set_if_mutual_nearest_neighbors(std::vector<std::pair<double,bool>>& p_lot, int pos)
    {
        if ( (p_lot[pos].first - p_lot[pos-1].first >
              p_lot[pos+1].first - p_lot[pos].first)
              &&
             (p_lot[pos+1].first - p_lot[pos].first <
              p_lot[pos+2].first - p_lot[pos+1].first) )
            {
                p_lot[pos].second = true;
                p_lot[pos+1].second = true;
            }
    }

int main(int argn, char* argv[])
{

    if ( argn != 2 )
        {
            std::cout << "provide length of parking lot as argument\n";
            return 1;
        }

    int len_of_parking_lot = std::atoi(argv[1]);
//    std::cout << len_of_parking_lot << '\n';

    std::default_random_engine dre;
//    std::mt19937 dre;
    std::uniform_real_distribution<double> uniform_dist_over_unit(0,1);

    const int nr_trials = 10'000'000;
    int mutual_nearest_count = 0;

    for ( int ix = 0; ix < nr_trials; ++ix )
        {
            std::vector<std::pair<double,bool>> parking_lot;
            for (int jx=0; jx<len_of_parking_lot; ++jx)
                {
                    parking_lot.push_back(std::make_pair(uniform_dist_over_unit(dre), false));
                }

            std::sort(parking_lot.begin(), parking_lot.end());

            for (int kx=0; kx<parking_lot.size()-2; ++kx)
                {
                    if ( kx == 0 )
                        {
                            set_if_mutual_nearest_neighbors_begin(parking_lot);
                        }
                    else if ( kx == parking_lot.size()-3 )
                        {
                            if ( set_if_mutual_nearest_neighbors_end(parking_lot) );
                            else set_if_mutual_nearest_neighbors(parking_lot, kx);
                        }
                    else
                        {
                            set_if_mutual_nearest_neighbors(parking_lot, kx);
                        }
                }
/*
                for ( auto it = parking_lot.begin(); it != parking_lot.end(); ++it )
                    std::cout << it->first << " " << it->second << "   ";
                std::cout << '\n';
*/
                std::uniform_int_distribution<int> random_car(0,len_of_parking_lot-1);
                int location = random_car(dre);

                if ( parking_lot[location].second ) ++mutual_nearest_count;
        }

        std::cout << "probability of mutual_nearest_neighbor = " <<
            static_cast<double>(mutual_nearest_count) / static_cast<double>(nr_trials) << '\n';

}
