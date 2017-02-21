// steve_elevator.cpp

#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main(int argn, char* argv[])
{
	using namespace std::placeholders;

    if ( argn != 2 )
        {
            std::cout << "have number of riders\n";
            return 1;
        }

    const int nr_add_riders = atoi(argv[1]);
    if ( nr_add_riders <= 0 ) return 1;

    std::default_random_engine dre;
//    std::mt19937 dre;

    std::uniform_int_distribution<int> floor(1,11);

    const int nr_trials = 1000000;
    const double steve_floor = 9;

    int nr_stops = 0;

    for ( int ix = 0; ix < nr_trials; ++ix )
        {
            ++nr_stops; // counting Steve's stop
            std::vector<double> riders;

            for ( int ix=0; ix<nr_add_riders; ++ix )
                riders.push_back(floor(dre));

            std::sort(riders.begin(), riders.end());

            auto unq_end = std::unique(riders.begin(), riders.end());

            nr_stops += std::count_if(riders.begin(), unq_end, std::bind(std::less<int>(), _1, steve_floor));
        }

        std::cout << "average number of stops = " <<
            static_cast<double>(nr_stops)/static_cast<double>(nr_trials) << '\n';

}
