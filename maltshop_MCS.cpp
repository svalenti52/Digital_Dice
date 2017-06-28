/**
 * \file maltshop.cpp
 * \date 24-Jun-2017
 *
 */

#include <val/util.h>
#include <val/montecarlo_alt/MonteCarloSim.h>

using DIST = DistributionType;

int main()
{

    auto condition_met = [](Distribution<double, DIST::UniformReal>& pd,
            Distribution<double, DIST::UniformReal>& sd,
            double& iv) -> bool {
        if (pd.events[0] > pd.events[1]) return pd.events[0] - pd.events[1] <= 5.0;
        else return pd.events[1] - pd.events[0] <= 7.0;
    };

    MonteCarloSimulation<double, double, DIST::UniformReal, DIST::UniformReal> monteCarloSimulation(
            10'000'000, ///> number of trials
            condition_met,      ///> condition met?
            0.0, 30.0, 2, 1,  ///> lower bound, upper bound, nr_events for primary distribution, seed primary
            0.0, 1.0, 0, 2); ///> lower bound, upper bound, nr_events for secondary distribution, seed secondary

    StopWatch stopWatch;

    monteCarloSimulation.run();

    stopWatch.stop();

    monteCarloSimulation.print_result();

}
