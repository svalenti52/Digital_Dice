/**
 * \file dating_MCS.cpp
 * \date 17-July-2017
 *
 * \brief Probability of finding the right one to marry as a function of the
 * pre-decision dating pool size.
 *
 *\details There is no marrying somebody in the pre-decision dating pool - once
 * the pre-decision phase is complete, the pool is used to marry the next one
 * from the remaining population that is better. Thus if the pre-decision pool
 * is too small, the next better one is likely not as good as it could be; if the
 * pre-decision pool is too large, the best one may have already been dated and
 * will be use to eliminate all subsequent ones till the last.
 * Note: if none have been previously selected, the last member in the population
 * must be selected (you will essentially be at the mercy of random selection).
 * Also, the "suitability" of the spouses is in order from least (best) to most
 * (worst).
 */

#include <val/montecarlo/MonteCarloSim.h>
#include <val/montecarlo/Chronology.h>
#include <val/montecarlo/List_Without_Repetition.h>
#include <algorithm>

//-----------------------------------------------------------------------------
class Spouse_Candidate
{
public:
    Spouse_Candidate(int i_suitability) : suitability(i_suitability) {}
    int operator ()() { return suitability; }
private:
    int suitability;
};
//-----------------------------------------------------------------------------

int main(int argc, char*argv[])
{
    using namespace std;

    if (argc!=4) {
        cout << "usage: ./a <Population> <BestSelection> <TrialDatingSize>\n";
        return 1;
    }

    const int nr_trials = 1'000'000;
    const int population_size = atoi(argv[1]);
    const int best_sel_size = atoi(argv[2]);
    const int dating_trial_size = atoi(argv[3]);

    if ( population_size <= dating_trial_size ) {
        cout << "population size must be larger than dating pool size";
        return 2;
    }

    auto condition_met = [best_sel_size, dating_trial_size, population_size](
            std::deque<int>& spouse_population, double& successful_selection
        ) -> bool {

        int most_suitable = 100; ///> value that is the upper bound of worst

        if ( dating_trial_size+1 == population_size )
            most_suitable = spouse_population[spouse_population.size()-1];
        else {
            /// PRE-DECISION PHASE DATING
            for (int ix = 0; ix<dating_trial_size; ++ix)
                if (most_suitable>spouse_population[ix]) most_suitable = spouse_population[ix];
            /// replace if better, i.e., lower in value

            /// SELECTION PHASE (i.e., next one better or else last)
            /// choose next one that is better than the best of the pre-decision phase
            for (int ix = dating_trial_size; ix<spouse_population.size(); ++ix) {
                if ( most_suitable > spouse_population[ix] )
                {
                    most_suitable = spouse_population[ix];
                    break;
                }
                if ( ix == spouse_population.size() - 1 )
                    most_suitable = spouse_population[ix];
            }
        }

        return most_suitable < best_sel_size;
    };

    List_Without_Repetition list_without_repetition(1'000'000, 100, 100, condition_met);

    StopWatch stopWatch;

    list_without_repetition.run();

    stopWatch.stop();

    list_without_repetition.print_result();

}