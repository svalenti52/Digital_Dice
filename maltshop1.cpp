/** \file maltshop1.cpp
 * \date 15-Jun-2017.
 * \brief Test out the new Monte Carlo Simulation class.
 */

#include <val/montecarlo/MCS_Real.h>

int main()
{

    MCS_Real mcs_real(10'000'000, 0.0, 30.0, 2, [](std::vector<double>& vd) -> bool {
        if (vd[0] > vd[1]) return vd[0] - vd[1] <= 5.0;
        else return vd[1] - vd[0] <= 7.0;
    } );

    mcs_real.run();

    mcs_real.print_result();

}
