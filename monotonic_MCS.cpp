/**
 * \file monotonic_MCS.cpp
 * \date 24-Jul-2017
 *
 * \brief Determine the average length of the sequence at which numbers
 * randomly chosen from the unit interval cease increasing.
 *
 */

#include <val/montecarlo/MonteCarloSim.h>
#include <val/montecarlo/Chronology.h>

using DIST = DistributionType;

int main() {

    Distribution<double, DIST::UniformReal> distribution(0.0, 1.0, 1);

    //-------------------------------------------------------------------------

    auto condition_met = [](Distribution<double, DIST::UniformReal>& number_sequence,
            double& len_sequence) -> bool {

        len_sequence = 2.0;
        number_sequence.add_random_value_to_end(); /// sequence is now 2 in length

        while ( number_sequence.events[0] < number_sequence.events[1] ) {
            len_sequence += 1.0;
            number_sequence.add_random_value_to_end(); /// temporarily 3 in length
            number_sequence.events.pop_front(); /// preserve length of 2 by keeping latest
        }

        number_sequence.events.pop_front(); /// sequence is now 1 in length
        return true;
    };

    //-------------------------------------------------------------------------

    MonteCarloSimulation_alpha<double, double, DIST::UniformReal> monteCarloSimulation(10'000'000,
        condition_met,
        distribution);

    StopWatch stopWatch;

    monteCarloSimulation.run();

    stopWatch.stop();

    monteCarloSimulation.print_result();
}
