/**
 * \file parkinglot2.cpp
 * \date 16-Jun-2017
 */

#include <random>
#include <iostream>
#include <algorithm>
#include <val/montecarlo/MCS_Real_and_Integer.h>
#include <deque>

int main()
{
    MCS_Real_and_Integer mcs_real_and_integer(1'000'000, 0.0, 1.0, 0, 9, 10,
            [&mcs_real_and_integer](std::vector<double>& vd) -> bool {
                std::sort(vd.begin(), vd.end());
                std::deque<double> difference;
                for (int ix = 0; ix<vd.size()-1; ++ix)
                    difference.push_back(vd[ix+1]-vd[ix]);
                difference.push_back(1.1);
                difference.push_front(1.1);
                int x = mcs_real_and_integer.uid(mcs_real_and_integer.dre);
                // difference[x] is before the xth element
                if (difference[x]>1.0) {
                    return difference[x+1] < difference[x+2];
                }
                else if (difference[x+1]>1.0) {
                    return difference[x] < difference[x-1];
                }
                else return difference[x] < difference[x+1] ?
                            difference[x] < difference[x-1] : difference[x+1] < difference[x+2];
            }, nullptr);

    mcs_real_and_integer.run();

    mcs_real_and_integer.print_result();
}

