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

    auto condition_met = [](Distribution<double, DIST::UniformReal>& bus_arrivals,
            Distribution<double, DIST::UniformReal>& rider,
            double& closest_next_bus) -> bool {

        bus_arrivals.events[0] = 1.0; // always set one of the buses to the hour

        rider.reload_random_values();

        /*
         // This is faster than using Differences
        closest_next_bus = 5.0;
        for ( double bus_arrival : bus_arrivals.events ) {
            if ( rider.events[0] > bus_arrival ) continue;
            double pot_closest_next_bus = bus_arrival - rider.events[0];
            if ( pot_closest_next_bus < closest_next_bus ) closest_next_bus = pot_closest_next_bus;
        }
        */

        ///*
        Differences<double> differences(bus_arrivals.events, rider.events[0], 5.0);

        closest_next_bus = differences.smallest_positive_difference();
        //*/

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
