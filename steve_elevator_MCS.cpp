/**
 * \file steve_elevator.cpp
 * \date 25-Jun-2017
 * \author svalenti
 * \brief Calculates the average number of elevator stops as a function of
 * the number of riders.
 *
 * \details
 */

#include <val/montecarlo/MonteCarloSim.h>
#include <val/montecarlo/Differences.h>
#include <val/util.h>

using DIST = DistributionType;

const int steve_floor = 9;

int main(int argc, char*argv[]) {

    auto condition_met = [](Distribution<int, DIST::UniformIntegral>& random_floors,
            Distribution<int, DIST::UniformIntegral>& sd,
            double& iv) -> bool { ///> condition met?
        std::sort(random_floors.events.begin(), random_floors.events.end());
        auto unique_floor_end = std::unique(random_floors.events.begin(), random_floors.events.end());
        iv = 1.0 +
                std::count_if(random_floors.events.begin(), unique_floor_end,
                    [](int random_floor) {
                        return random_floor < steve_floor;
                    } );
        return true;
    };

    MonteCarloSimulation<int, int, DIST::UniformIntegral, DIST::UniformIntegral> monteCarloSimulation(
            10'000'000,
            condition_met,
            1, 11, 5, 1,
            1, 11, 0, 2
    );

    monteCarloSimulation.change_message("average number of elevator stops is ");

    StopWatch stopWatch;

    monteCarloSimulation.run();

    stopWatch.stop();

    monteCarloSimulation.print_result();
}
