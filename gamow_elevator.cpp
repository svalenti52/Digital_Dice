// gamow_elevator.cpp

#include <random>
#include <iostream>
#include <vector>
#include <algorithm>

int main(int argn, char* argv[])
{
    if ( argn != 2 )
        {
            std::cout << "have number of independent elevators\n";
            return 1;
        }

    const int nr_elevators = atoi(argv[1]);
    if ( nr_elevators == 0 ) return 1;

    std::default_random_engine dre;
//    std::mt19937 dre;

    std::uniform_real_distribution<double> elevator_pos(0,1);

    const int nr_trials = 10'000'000;
    const double second_floor = 0.16666667;

    int count_above_arrive_first = 0;

    for ( int ix = 0; ix < nr_trials; ++ix )
        {
            std::vector<double> elevators;

            for ( int ix=0; ix<nr_elevators; ++ix )
                elevators.push_back(elevator_pos(dre));

            std::sort(elevators.begin(), elevators.end());

            if ( elevators[0] > second_floor )
                {
                    ++count_above_arrive_first;
                    continue;
                }

            if ( elevators[elevators.size()-1] <= second_floor )
                continue;

            int last_one_below_second_floor = 0;
            for ( int jx = 0; elevators[jx] <= second_floor; ++jx )
                last_one_below_second_floor = jx;


            if ( ( elevators[last_one_below_second_floor+1] - second_floor ) <
                 ( second_floor - elevators[last_one_below_second_floor] ) )
                {
                    ++count_above_arrive_first;
                }
        }

        std::cout << "average time elevator arrives and is going down = " <<
            static_cast<double>(count_above_arrive_first)/static_cast<double>(nr_trials) << '\n';

}
