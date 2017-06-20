/**
 * \file parkinglot2.cpp
 * \date 16-Jun-2017
 */

#include <random>
#include <iostream>
#include <algorithm>
#include <val/montecarlo/MCS_Real_and_Integer.h>
#include "val/util.h"

int main()
{
    MCS_Real_and_Integer mcs_real_and_integer(1'000'000, 0.0, 1.0, 0, 9, 10,
            [&mcs_real_and_integer](std::vector<double>& vd) -> bool {
                Deque_of_Difference<double> deque_of_difference(vd, 1.1, 1.1, 1.0);

                mcs_real_and_integer.random_discrete_event.reload_random_values();

                return deque_of_difference.member_of_mutually_closest
                        (mcs_real_and_integer.random_discrete_event.events[0]);
            }, nullptr);


    StopWatch stopWatch;

    mcs_real_and_integer.run();

    mcs_real_and_integer.print_result();

    stopWatch.stop();
}

