// matches_banach.cpp

#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main(int argn, char* argv[])
{

    std::default_random_engine dre;
    std::uniform_int_distribution<int> matchbook_sel(0,1);

    const int nr_trials = 1000000;
    const int matches_full = 40;

    int nr_matches_removed = 0;

    for ( int ix = 0; ix < nr_trials; ++ix )
        {
            std::vector<int> matchbook;
            matchbook.push_back(matches_full);
            matchbook.push_back(matches_full);

            while ( matchbook[0] != 0 && matchbook[1] != 0 )
                {
                    --matchbook[matchbook_sel(dre)];
                }

            while (true)
                {
                    int matchbook_selected = matchbook_sel(dre);
                    if ( matchbook[matchbook_selected] == 0 ) break;
                    else --matchbook[matchbook_selected];
                }

            nr_matches_removed += 2 * matches_full - matchbook[0] - matchbook[1];

        }

        std::cout << "average number of matches removed = " <<
            static_cast<double>(nr_matches_removed)/static_cast<double>(nr_trials) << '\n';

}
