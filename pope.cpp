// pope.cpp

#include <random>
#include <iostream>
#include <vector>
#include <algorithm>

/*--------------------------------------------------------------------------*/

class Election_Candidate
{
public:
    Election_Candidate(double i_vote_lb, double i_vote_ub)
        : votes(0), vote_lb(i_vote_lb), vote_ub(i_vote_ub) {}
    int votes_rxd() { return votes; }
    void operator ++() { ++votes; }
    void reset_vote() { votes = 0; }
    void operator ^ (double i_vote_cast)
        {
            if ( vote_lb <= i_vote_cast && i_vote_cast < vote_ub )
                ++votes;
        }
    friend std::ostream& operator << (std::ostream& o, Election_Candidate& e);
private:
    int votes;
    double vote_lb;
    double vote_ub;
};

std::ostream& operator << (std::ostream& o, Election_Candidate& e)
{
    o << "votes rx = " << e.votes << '\n';
    return o;
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

int main(int argn, char* argv[])
{
    using namespace std;

    if ( argn != 4 )
        {
            cout << "usage: ./a <Population> <WinMajority> <ElectionPool>\n";
            return 1;
        }


    default_random_engine dre;
    uniform_real_distribution<double> voted_for_canonical;

    const int nr_trials = 100000;

    int population_size = atoi(argv[1]);
    int win_majority_size = atoi(argv[2]);
    int election_pool_size = atoi(argv[3]);

    double pope_elected = 0;
    double vote_portion = 1.0 / static_cast<double>(election_pool_size);

    vector<Election_Candidate> ecs;
    for ( int ix = 0; ix < election_pool_size; ++ix )
        ecs.push_back(Election_Candidate(ix*vote_portion, (ix+1)*vote_portion));


    for ( int ix = 0; ix < nr_trials; ++ix )
    {

        for ( int jx = 0; jx < population_size; ++jx )
            {
                double cast_vote = voted_for_canonical(dre);
                for ( Election_Candidate& ec : ecs )
                    ec ^ cast_vote;
            }

        auto did_win = find_if(ecs.begin(), ecs.end(),
            [win_majority_size](Election_Candidate& ec) -> bool
                { return (ec.votes_rxd() >= win_majority_size); } );

//        cout << *did_win << '\n';

        if ( did_win != ecs.end() ) pope_elected += 1.0;

/*        for ( Election_Candidate& ec : ecs )
            cout << ec;
        cout << "\n\n";
*/
        for ( Election_Candidate& ec : ecs )
            ec.reset_vote();

    }

    std::cout << "pope elected probability = "
        << pope_elected / static_cast<double>(nr_trials) << '\n';
}
