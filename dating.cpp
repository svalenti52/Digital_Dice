/** \file dating.cpp
 *
 */

#include <random>
#include <iostream>
#include <vector>
#include <algorithm>

/*--------------------------------------------------------------------------*/

class Wife_Candidate
{
public:
		Wife_Candidate(int i_suitability) : suitability(i_suitability) {}
		int get_suitability() { return suitability; }
private:
		int suitability;
};

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

int main(int argn, char* argv[])
{
    using namespace std;

    if ( argn != 4 )
        {
            cout << "usage: ./a <Population> <BestSelection> <TrialDatingSize>\n";
            return 1;
        }

    const int nr_trials = 1000000;
    const int population_size = atoi(argv[1]);
    const int best_sel_size = atoi(argv[2]);
    const int dating_trial_size = atoi(argv[3]);

    vector<Wife_Candidate> wc;

    for ( int ix = 0; ix < population_size; ++ix )
        wc.push_back(ix);

    double best_cat_selected = 0.0;

    for ( int jx = 0; jx < nr_trials; ++jx )
    {

        random_shuffle(wc.begin(), wc.end());

/*        for ( Wife_Candidate& w : wc )
            std::cout << w.get_suitability() << " ";
        std::cout << '\n';
*/
        int considered_best = 1000000;

        for ( int ix = 0; ix < dating_trial_size; ++ix )
        {
            if ( considered_best > wc[ix].get_suitability() )  considered_best = wc[ix].get_suitability();
        }

        for ( int ix = dating_trial_size; ix < wc.size(); ++ix )
        {
//            std::cout << considered_best << " ";
            if ( considered_best > wc[ix].get_suitability() )
            {
                considered_best = wc[ix].get_suitability();
                break;
            }
            if ( ix == wc.size() - 1 ) considered_best = wc[ix].get_suitability();
        }
//        std::cout << '\n';

        if ( considered_best < best_sel_size )
//            std::cout << "Best Selected = " << considered_best << '\n';
            best_cat_selected += 1.0;
//        else
//            std::cout << "Not the best = " << considered_best << '\n';
    }

    std::cout << "probability best selected = "
        << best_cat_selected / static_cast<double>(nr_trials) << '\n';
}
