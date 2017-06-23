/**
 * /file gamow_elevator1.cpp
 * /date 22-Jun-2017
 * /author
 */

#include <val/montecarlo/MCS_Real.h>
#include <val/montecarlo/Deque_of_Difference.h>
#include <val/util.h>

int main(int argc, char*argv[]) {

    MCS_Real mcs_real(10'000'000, 0.0, 1.0, 3,
        [](std::vector<double>& vd) -> bool {
            Deque_of_Difference<double> deque_of_difference(vd, 0.166666667, 5.0);
            return deque_of_difference.closest_is_positive();
        });

    mcs_real.change_message("probability of elevator arriving first on 2nd floor and going down is ");

    StopWatch stopWatch;

    mcs_real.run();

    stopWatch.stop();

    mcs_real.print_result();
}
