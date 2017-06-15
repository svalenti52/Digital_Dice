/**
 * \file dishwasher3.cpp
 * \date 15-Jun-2017.
 * \brief File to test out new Monte Carlo Simulation Class.
 *
 * \author svalenti
 */

#include <iostream>
#include <val/montecarlo/MCS_Real.h>

int main()
{
    MCS_Real mcs_real(0.0, 1.0, 5);

    mcs_real.load_condition_met([](double d) { return d < 0.2; });

    mcs_real.run();

    mcs_real.print_result();

}
