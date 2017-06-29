/**
 * \file bus_MCS.cpp
 * \date 29-Jun-2017
 *
 */

#include <val/montecarlo/MonteCarloSim.h>
#include <val/montecarlo/Differences.h>
#include <val/util.h>

using DIST = DistributionType;

int main() {

    auto condition_met = [](Distribution<double, DIST::UniformReal>& pd,
            Distribution<double, DIST::UniformReal>& rider,
            double& iv) -> bool {

        pd.events[0] = 1.0; // always set one of the buses to the hour

        rider.reload_random_values();
        /*
         // This is faster than using Differences
        iv = 5.0;
        for ( double event : pd.events ) {
            if ( rider.events[0] > event ) continue;
            double pot_smallest_diff = event - rider.events[0];
            if ( pot_smallest_diff < iv ) iv = pot_smallest_diff;
        }
        */
        Differences<double> differences(pd.events, rider.events[0], 5.0);

        iv = differences.smallest_positive_difference();

        return true;
    };

    MonteCarloSimulation<double, double, DIST::UniformReal, DIST::UniformReal> monteCarloSimulation(
        10'000'000,
        condition_met,
        0.0, 1.0, 5, 1,
        0.0, 1.0, 1, 2
    );

    StopWatch stopWatch;

    monteCarloSimulation.run();

    monteCarloSimulation.print_result();

    stopWatch.stop();
}
