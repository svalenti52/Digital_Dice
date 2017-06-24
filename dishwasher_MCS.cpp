/**
 * \file dishwasher_MCS.cpp
 * \date 23-Jun-2017
 */

#include <val/montecarlo/MonteCarloSim.h>
#include <algorithm>
#include "val/util.h"

int main() {
    StopWatch stopWatch;

    MonteCarloSimx<double, double> monteCarloSimx(10'000'000, ///> number of trials
            [](std::vector<double>& vd, std::vector<double>& vd2) -> bool { ///> condition met?
                return std::count_if(vd.begin(), vd.end(), [](double d) { return d < 0.2;} ) > 3;
            },
            0.0, 1.0, 5,  ///> lower bound, upper bound, nr_events for primary distribution
            0.0, 1.0, 0); ///> lower bound, upper bound, nr_events for secondary distribution

    monteCarloSimx.run();

    stopWatch.stop();

    monteCarloSimx.print_result();

}
