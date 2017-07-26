/**
 * \file bus_MCS.cpp
 * \date 29-Jun-2017
 *
 */

#include <val/montecarlo/MonteCarloSim_alpha.h>
#include <val/montecarlo/Differences.h>
#include <val/montecarlo/Chronology.h>

using DIST = DistributionType;

int main() {

    Distribution<double, DIST::UniformReal> bus_arrivals(0.0, 1.0, 5);

    Distribution<double, DIST::UniformReal> rider_arrival(0.0, 1.0, 1);

    auto condition_met = [&rider_arrival](Distribution<double, DIST::UniformReal>& _bus_arrivals,
            double& closest_next_bus,
            DRE& dre) -> bool {

        _bus_arrivals.events[0] = 1.0; // always set one of the buses to the hour

        rider_arrival.reload_random_values(dre);

        ///*
         // This is faster than using Differences
        closest_next_bus = 5.0;
        for ( double bus_arrival : _bus_arrivals.events ) {
            if ( rider_arrival.events[0] > bus_arrival ) continue;
            double pot_closest_next_bus = bus_arrival - rider_arrival.events[0];
            if ( pot_closest_next_bus < closest_next_bus ) closest_next_bus = pot_closest_next_bus;
        }
        //*/

        /*
        Differences<double> differences(_bus_arrivals.events, rider_arrival.events[0], 5.0);

        closest_next_bus = differences.smallest_positive_difference();
        //*/

        return true;
    };

    MonteCarloSimulation<double, double, DIST::UniformReal> monteCarloSimulation(
        10'000'000,
            1,
        condition_met,
        bus_arrivals
    );

    StopWatch stopWatch;

    monteCarloSimulation.run();

    monteCarloSimulation.print_result();

    stopWatch.stop();
}
