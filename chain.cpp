// chain.cpp

#include <random>
#include <iostream>
#include <vector>
#include <algorithm>

/*--------------------------------------------------------------------------*/

std::default_random_engine dre;
std::uniform_real_distribution<double> det_nr_descendants(0,1);


class Generation_Grid_Elt
{
public:
	Generation_Grid_Elt(int ix, double i_lb, double i_ub) : number_of_descendants(ix), prob_lb(i_lb), prob_ub(i_ub)
	    {
	    }
	double get_ub() { return prob_ub; }
	bool operator ^(const double& prob)
	    {
            return prob_lb < prob && prob < prob_ub;
	    }
	void nr_descendants() { std::cout << "nr descendants = " << number_of_descendants << '\n'; }
    int get_nr_descendants() { return number_of_descendants; }
    friend std::ostream& operator << (std::ostream& o, Generation_Grid_Elt& g);
private:
    int number_of_descendants;
    double prob_lb;
    double prob_ub;
};

std::ostream& operator << (std::ostream& o, Generation_Grid_Elt& g)
    {
        o << "lb=" << g.prob_lb << "  ub=" << g.prob_ub << '\n';
        return o;
    }

typedef std::vector<Generation_Grid_Elt> Generation_Prob_Grid;

/*--------------------------------------------------------------------------*/

double p_nr_descendants(int nr_descendants)
{
    return (0.2126 * pow(0.5893, nr_descendants-1));
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

class Generation;

std::vector<Generation> g_vec;

class Generation
{
public:
    Generation(int i_generation, double i_progeny_prob, Generation_Prob_Grid& p_i) :
        generation(i_generation), progeny_prob(i_progeny_prob)
        {
//            std::cout << "generation " << generation << "  progeny prob=" << progeny_prob << '\n';
            if ( generation < 3 )
                {
                    auto idx_it = std::find_if(p_i.begin(), p_i.end(), [i_progeny_prob](Generation_Grid_Elt& g) { return g ^ i_progeny_prob; } );
                    if ( idx_it == p_i.end() );
                    else
                        {
                            for (int ix=0; ix<(idx_it->get_nr_descendants()); ix++)
                            {
                                g_vec.push_back(Generation(generation+1, det_nr_descendants(dre), p_i));
                            }

                        }
                }
        }
    bool if_generation(int which_generation) { return ( which_generation == generation ); }
private:
    int generation;
    double progeny_prob;
};

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

int main(int argn, char* argv[])
{
    using namespace std;

//    vector<Generation_Grid_Elt>
    Generation_Prob_Grid generation_prob_grid { Generation_Grid_Elt(0, 0.0, 0.4825) };
    for ( int ix = 1; ix < 8; ++ix )
        generation_prob_grid.push_back( Generation_Grid_Elt(ix, generation_prob_grid[ix-1].get_ub(), generation_prob_grid[ix-1].get_ub() + p_nr_descendants(ix)) );

    for ( Generation_Grid_Elt& g : generation_prob_grid )
        cout << g;

    const int nr_trials = 1000000;
    double avg_progeny_number = 0.0;
    double avg_2_males_in_2nd_gen = 0.0;
    double avg_4_males_in_2nd_gen = 0.0;
    double avg_6_males_in_3rd_gen = 0.0;

    for ( int ix = 0; ix < nr_trials; ++ix )
    {
        double nr_descendants = det_nr_descendants(dre);

        auto idx_it = find_if(generation_prob_grid.begin(), generation_prob_grid.end(), [nr_descendants](Generation_Grid_Elt& g) { return g ^ nr_descendants; } );
        if ( idx_it == generation_prob_grid.end() ) cout << "DID NOT FIND\n";
        else
            {
                // idx_it->nr_descendants();
                for ( int jx = 0; jx < idx_it->get_nr_descendants(); ++jx )
                    g_vec.push_back(Generation(1, det_nr_descendants(dre), generation_prob_grid));
            }
//        cout  << "descendants number to 3rd generation = " << g_vec.size() << '\n';
        avg_progeny_number += static_cast<double>(g_vec.size());
        long progeny_count_2_gen = count_if(g_vec.begin(), g_vec.end(), [](Generation& g) -> bool { return g.if_generation(2); } );
        if ( progeny_count_2_gen == 2 ) avg_2_males_in_2nd_gen += 1.0;
        if ( progeny_count_2_gen == 4 ) avg_4_males_in_2nd_gen += 1.0;

        long progeny_count_3_gen = count_if(g_vec.begin(), g_vec.end(), [](Generation& g) -> bool { return g.if_generation(3); } );
        if ( progeny_count_3_gen == 6 ) avg_6_males_in_3rd_gen += 1.0;

//        progeny_count_2_gen = count_if(g_vec.begin(), g_vec.end(), [](Generation& g) -> bool { return g.if_generation(2); } );
  //      if ( progeny_count_2_gen == 4 ) avg_2_males_in_2nd_gen += 1.0;
        g_vec.clear();
    }
    cout << "average progeny number = " << avg_progeny_number/static_cast<double>(nr_trials) << '\n';
    cout << "prob 2 males 2nd generation = " << avg_2_males_in_2nd_gen/static_cast<double>(nr_trials) << '\n';
    cout << "prob 4 males 2nd generation = " << avg_4_males_in_2nd_gen/static_cast<double>(nr_trials) << '\n';
    cout << "prob 6 males 3rd generation = " << avg_6_males_in_3rd_gen/static_cast<double>(nr_trials) << '\n';
}
