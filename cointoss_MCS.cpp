/**
 * \file cointoss_MCS.cpp
 * \date 24-Jun-2017
 *
 * \brief Three players tossing coins, "odd" man out wins round, all matching no effect.
 *
 * \detail Expected number of tosses till one of the players is out, i.e., has 0 coins left.
 */

#include <val/montecarlo/Chronology.h>
#include <val/montecarlo/MonteCarloSim.h>
#include <algorithm>

using DIST = DistributionType;

int main(int argc, char* argv[])
{

    if ( argc != 5 )
    {
        std::cout << "the first 3 positions are number of coins for three players and 2 digits (%) for fairness\n";
        return 1;
    }

    int coins1 = atoi(argv[1]);
    int coins2 = atoi(argv[2]);
    int coins3 = atoi(argv[3]);
    int i_fairness = atoi(argv[4]);

    const std::vector<int> stake_vector{coins1, coins2, coins3};

    auto condition_met = [stake_vector](Distribution<bool, DIST::BernoulliIntegral>& cointoss,
            Distribution<int, DIST::UniformIntegral>& stake,
            double& nr_flips_till_out) -> bool {

        nr_flips_till_out = 0;
        stake.reload_values(stake_vector);
        while ( std::none_of(stake.events.begin(), stake.events.end(), [](int cash) { return cash == 0;} )) {
            ++nr_flips_till_out;
            cointoss.reload_random_values();
            if ( cointoss.events[0] == cointoss.events[1] && cointoss.events[1] == cointoss.events[2] ) continue;
            else if ( cointoss.events[0] == cointoss.events[1] ) {
                --stake.events[0];
                --stake.events[1];
                ++stake.events[2], ++stake.events[2];
            }
            else if ( cointoss.events[0] == cointoss.events[2] ) {
                --stake.events[0];
                ++stake.events[1], ++stake.events[1];
                --stake.events[2];
            }
            else {
                ++stake.events[0], ++stake.events[0];
                --stake.events[1];
                --stake.events[2];
            }
        }
        return true;
    };

    Distribution<bool, DIST::BernoulliIntegral> cointoss_distribution(0.5, 3);
    Distribution<int, DIST::UniformIntegral> coins_at_stake(0, 1, 3);

    MonteCarloSimulation<bool, int, DIST::BernoulliIntegral, DIST::UniformIntegral> monteCarloSimulation(
            10'000'000, ///> number of trials
            condition_met,      ///> condition met?
            cointoss_distribution,  ///> primary distribution (new constructor)
            coins_at_stake); ///> secondary distribution

    monteCarloSimulation.change_message("average number of tosses till out = ");

    StopWatch stopWatch;

    monteCarloSimulation.run();

    stopWatch.stop();

    monteCarloSimulation.print_result();

}
