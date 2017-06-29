/**
 * \file matches.cpp
 * \date 25-Jun-2017
 *
 */

#include <val/montecarlo/MonteCarloSim.h>
#include <val/util.h>
#include <algorithm>

using DIST = DistributionType;

int main() {

    const int match_book_full = 40;
    const std::vector<int> matchbook_init{match_book_full, match_book_full};

    auto condition_met = [&matchbook_init](Distribution<int, DIST::BernoulliIntegral>& matchbook_selection,
            Distribution<int, DIST::UniformIntegral>& matchbook_state,
            double& iv) -> bool {

        matchbook_state.reload_values(matchbook_init);
        iv = 0.0;
        while (std::none_of(matchbook_state.events.begin(), matchbook_state.events.end(),
            [](int i) { return i == 0;} )) {
            --matchbook_state.events[matchbook_selection.events[0]];
            iv += 1.0;
            matchbook_selection.reload_random_values();
        }
        ///> this next section is matches_banach problem
        ///*
        matchbook_selection.reload_random_values();
        while (matchbook_state.events[matchbook_selection.events[0]] != 0) {
            --matchbook_state.events[matchbook_selection.events[0]];
            ++iv;
            matchbook_selection.reload_random_values();
        }
        //*/
        ///> end matches_banach (remove above paragraph for original matches.cpp)

        return true;
    };


    MonteCarloSimulation<int, int, DIST::BernoulliIntegral, DIST::UniformIntegral> monteCarloSimulation(
            1'000'000,
            condition_met,
            1, 2, 1, 1, ///> first two parameters give ratio of probability for Bernoulli (1/2 in this case)
            0, 40, 2, 2 ///> second distribution is used as a state vector each time condition_met is called
    );

    monteCarloSimulation.change_message("average number of matches removed = ");

    StopWatch stopWatch;

    monteCarloSimulation.run();

    monteCarloSimulation.print_result();

    stopWatch.stop();
}
