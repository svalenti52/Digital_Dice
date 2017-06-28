/**
 * \file parkinglot.cpp
 * \date 24-Jun-2017
 *
 */

#include <val/util.h>
#include <val/montecarlo/MonteCarloSim.h>
#include <val/montecarlo/Differences.h>

using DIST = DistributionType;

int main()
{

    auto condition_met = [](Distribution<double, DIST::UniformReal>& pd,
            Distribution<int, DIST::UniformIntegral>& sd,
            double& iv) -> bool {
        std::sort(pd.events.begin(), pd.events.end()); ///> sort the data prior to forming the differences

        Differences<double> deque_of_difference(pd.events, 1.1, 1.1, 1.0);
        
        sd.reload_random_values();

        return deque_of_difference.member_of_mutually_closest
                (sd.events[0]);
    };

    MonteCarloSimulation<double, int, DIST::UniformReal, DIST::UniformIntegral> monteCarloSimulation(
            10'000'000, ///> number of trials
            condition_met,      ///> condition met?
            0.0, 1.0, 10, 1,  ///> lower bound, upper bound, nr_events for primary distribution, seed primary
            0, 9, 1, 2); ///> lower bound, upper bound, nr_events for secondary distribution, seed secondary

    StopWatch stopWatch;

    monteCarloSimulation.run();

    stopWatch.stop();

    monteCarloSimulation.print_result();

}
