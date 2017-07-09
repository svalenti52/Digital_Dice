/**
 * \file dishwasher_MCS.cpp
 * \date 24-Jun-2017
 *
 */

#include <algorithm>
#include <val/montecarlo/Chronology.h>
#include <val/montecarlo/MonteCarloSim.h>

using DIST = DistributionType;

int main() {

    auto condition_met = [](Distribution<double, DIST::UniformReal>& pd,
            Distribution<double, DIST::UniformReal>& sd,
            double& iv) -> bool { ///> condition met?
        /// iv is one by default which is all we need here
        return std::count_if(pd.events.begin(), pd.events.end(), [](double d) { return d < 0.2;} ) > 3;
    };

    MonteCarloSimulation<double, double, DIST::UniformReal, DIST::UniformReal> monteCarloSimulation(
            10'000'000, ///> number of trials
            condition_met,  ///> condition met?
            0.0, 1.0, 5, 1,  ///> lower bound, upper bound, nr_events for primary distribution, seed primary
            0.0, 1.0, 0, 2); ///> lower bound, upper bound, nr_events for secondary distribution, seed secondary

    StopWatch stopWatch;

    monteCarloSimulation.run();

    stopWatch.stop();

    monteCarloSimulation.print_result();

}
