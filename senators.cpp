/**
 * \file senators.cpp
 *
 */

#include <random>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>

class senator
{
    bool vote;
    bool present_for_vote;
public:
    senator() : vote(false), present_for_vote(true) {}
    senator(bool i_vote) : vote(i_vote), present_for_vote(true) {}
    void present() { present_for_vote = true; }
    void absent() { present_for_vote = false; }
    bool is_absent() { return !present_for_vote; }
    bool for_bill () { return vote; }
};

int main(int argn, char* argv[])
{

    if ( argn != 3 )
        {
            std::cout << "have number of senators against bill, number missing\n";
            return 1;
        }

    const int nr_senators = 100;
    const int nr_vote_against = atoi(argv[1]);
    const int nr_missing_senators = atoi(argv[2]);

    std::default_random_engine dre;
    std::uniform_int_distribution<int> missing_senators(0,99);

    const int nr_trials = 10'000'000;

    int voted_down_count = 0;
    for ( int ix = 0; ix < nr_trials; ++ix )
    {
        std::vector<senator> senators;

        for ( int jx=0; jx<nr_vote_against; ++jx )
            senators.push_back(senator(false));

        for ( int jx=nr_vote_against; jx<nr_senators; ++jx )
            senators.push_back(senator(true));

        std::set<int> index_of_missing;
        for ( int jx=0; jx<nr_missing_senators; ++jx )
        {
            while ( !index_of_missing.insert(missing_senators(dre)).second );
        }

        std::for_each ( index_of_missing.begin(), index_of_missing.end(),
            [&senators] (int kx) { senators[kx].absent(); } );

        int nr_for_bill = std::count_if ( senators.begin(), senators.end(),
            [] (senator s) { return (!s.is_absent() && s.for_bill()); } );

        if ( nr_for_bill < nr_senators - nr_missing_senators - nr_for_bill )
            ++voted_down_count;
    }

        std::cout << "probability of being voted down = " <<
            static_cast<double>(voted_down_count)/static_cast<double>(nr_trials) << '\n';

}
