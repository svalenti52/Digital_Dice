/**
 * \file dishwasher_MCS.cpp
 * \date 24-Jun-2017
 *
 * \brief Probability of a particular dishwasher breaking 4 or 5 dishes
 * out of 5 broken, given equal skills and a pool of 5 dishwashers in total.
 */

#include <algorithm>
#include <val/montecarlo/Chronology.h>
#include <val/montecarlo/MonteCarloSim_beta.h>

int main() {

    const double clumsy_id_interval = 0.2;
    const int clumsy_breakage_lower_bound = 3;

    Distribution<double, std::uniform_real_distribution> dishwashers_breaking_5_dishes(0.0, 1.0, 5);

    //-------------------------------------------------------------------------
    auto condition_met = [clumsy_id_interval, clumsy_breakage_lower_bound]
            (Distribution<double, std::uniform_real_distribution>& _dishwashers_breaking_5,
            double& event_clumsy_breaks_gt_3,
            DRE& dre) -> bool
    { ///> condition met? if so, then event_clumsy_breaks_gt_3 gets added to cumulative_value
        /// event_clumsy_breaks_gt_3 is one by default which is all we need here
        return std::count_if(_dishwashers_breaking_5.events.begin(),
                _dishwashers_breaking_5.events.end(),
                [clumsy_id_interval, clumsy_breakage_lower_bound](double who_broke_this_dish)
                {
                    return who_broke_this_dish < clumsy_id_interval;
                }
        ) > clumsy_breakage_lower_bound;
    };
    //-------------------------------------------------------------------------

    MonteCarloSimulation<double, double, std::uniform_real_distribution> monteCarloSimulation(
            10'000'000, ///> number of trials
            1,          ///> seed for dre
            condition_met,  ///> condition met?
            dishwashers_breaking_5_dishes);  ///> lower bound, upper bound, nr_events for primary distribution, seed primary

    StopWatch stopWatch;

    monteCarloSimulation.run();

    stopWatch.stop();

    monteCarloSimulation.print_result();

}
