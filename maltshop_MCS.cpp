/**
 * \file maltshop.cpp
 * \date 24-Jun-2017
 *
 */

#include <val/montecarlo/Chronology.h>
#include <val/montecarlo/MonteCarloSim_alpha.h>

using DIST = DistributionType;

const double Lil_will_wait = 5.0;
const double Bill_will_wait = 7.0;

int main()
{
    Distribution<double, DIST::UniformReal> Lil_and_Bill_30_minute_window(0.0, 30.0, 2);

    auto condition_met = [](Distribution<double, DIST::UniformReal>& pd,
            double& iv,
            DRE& dre) -> bool {
        if (pd.events[0] > pd.events[1]) return pd.events[0] - pd.events[1] <= Lil_will_wait;
        return pd.events[1] - pd.events[0] <= Bill_will_wait;
    };

    MonteCarloSimulation<double, double, DIST::UniformReal> monteCarloSimulation(
            10'000'000, ///> number of trials
            1,          ///> seed
            condition_met,      ///> condition met?
            Lil_and_Bill_30_minute_window); ///> distribution within 30 minutes

    StopWatch stopWatch;

    monteCarloSimulation.run();

    stopWatch.stop();

    monteCarloSimulation.print_result();

}
