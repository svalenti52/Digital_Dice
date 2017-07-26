/**
 * \file maltshop_MCS.cpp
 * \date 24-Jun-2017
 *
 * \brief Probability that Bill and Lil meet within a 30 minute window
 * given uniformly random arrival times and a limited waiting time for each.
 *
 */

#include <val/montecarlo/Chronology.h>
#include <val/montecarlo/MonteCarloSim_alpha.h>

using DIST = DistributionType;

const double Lil_will_wait = 5.0;
const double Bill_will_wait = 7.0;

const int Lil_arrives = 1;
const int Bill_arrives = 0;

int main()
{
    Distribution<double, DIST::UniformReal> Lil_and_Bill_30_minute_window(0.0, 30.0, 2);

    auto condition_met = [](Distribution<double, DIST::UniformReal>& Thirty_minute_window,
            double& iv,
            DRE& dre) -> bool {

        if (Thirty_minute_window.events[Bill_arrives] > Thirty_minute_window.events[Lil_arrives])
            return Thirty_minute_window.events[Bill_arrives]
                    - Thirty_minute_window.events[Lil_arrives] <= Lil_will_wait;

        return Thirty_minute_window.events[Lil_arrives]
                - Thirty_minute_window.events[Bill_arrives] <= Bill_will_wait;
    };

    MonteCarloSimulation<double, double, DIST::UniformReal> monteCarloSimulation(
            10'000'000, ///> number of trials
            1,          ///> seed
            condition_met,      ///> condition met?
            Lil_and_Bill_30_minute_window); ///> distribution within 30 minutes

    StopWatch stopWatch;

    monteCarloSimulation.run();

    stopWatch.stop();

    monteCarloSimulation.change_message("Probability that Bill and Lil meet at the malt shop = ");

    monteCarloSimulation.print_result();
}
