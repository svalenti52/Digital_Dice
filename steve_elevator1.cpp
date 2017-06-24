/**
 * \file steve_elevator1.cpp
 * \date 22-Jun-2017
 * \author svalenti
 * \brief Calculates the average number of elevator stops as a function of
 * the number of riders.
 *
 * \details
 */

#include <val/montecarlo/MCS_Integer.h>
#include <algorithm>

const int steve_floor = 9;

int main() {

    MCS_Integer mcs_integer(10'000'000, 1, 11, 2,
        [&mcs_integer](std::vector<int>& random_floors, std::vector<int>& transient) -> bool {
            std::sort(random_floors.begin(), random_floors.end());
            auto unique_floor_end = std::unique(random_floors.begin(), random_floors.end());
            mcs_integer.assign_interim_value( 1.0 + // count Steve's stop every time
                std::count_if(random_floors.begin(), unique_floor_end,
                        [](int random_floor) {
                            return random_floor < steve_floor;
                        }
                ) );
            mcs_integer.random_events.reload_random_values();
            return true;
        } );

    mcs_integer.change_message("number of elevator stops = ");

    mcs_integer.run();

    mcs_integer.print_result();
}
