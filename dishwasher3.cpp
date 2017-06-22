/**
 * \file dishwasher3.cpp
 * \date 15-Jun-2017.
 * \brief File to test out new Monte Carlo Simulation Class.
 *
 * \author svalenti
 */

#include <val/montecarlo/MCS_Real.h>
#include <algorithm>
#include "val/util.h"

int main()
{
    StopWatch stopWatch;


    MCS_Real mcs_real(10'000'000, 0.0, 1.0, 5, [](std::vector<double>& vd) -> bool {
        return std::count_if(vd.begin(), vd.end(), [](double d) { return d < 0.2;} ) > 3;
    });

    mcs_real.run();

    stopWatch.stop();

    mcs_real.print_result();
}
