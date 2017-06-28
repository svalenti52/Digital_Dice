/**
 * /file gamow_elevator.cpp
 * /date 25-Jun-2017
 * /author
 */

#include <val/montecarlo/MonteCarloSim.h>
#include <val/montecarlo/Differences.h>
#include <val/util.h>

using DIST = DistributionType;

int main(int argc, char*argv[]) {

    auto condition_met = [](Distribution<double, DIST::UniformReal>& pd,
            Distribution<double, DIST::UniformReal>& sd,
            double& iv) -> bool { ///> condition met?
        Differences<double> deque_of_difference(pd.events, 0.166666667, 5.0);
        return deque_of_difference.closest_is_positive();
    };

    MonteCarloSimulation<double, double, DIST::UniformReal, DIST::UniformReal> monteCarloSimulation(
            10'000'000,
            condition_met,
            0.0, 1.0, 4, 1,
            0.0, 1.0, 0, 2
            );

    monteCarloSimulation.change_message("probability of elevator arriving first on 2nd floor and going down is ");

    StopWatch stopWatch;

    monteCarloSimulation.run();

    stopWatch.stop();

    monteCarloSimulation.print_result();
}
