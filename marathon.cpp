// marathon.cpp

#include <random>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include "utilities.hpp"

int main(int argn, char* argv[])
{
    if ( argn != 2 )
        {
            std::cout << "have % of numbered runners seen\n";
            return 1;
        }

    const int percentage_for_sample = atoi(argv[1]);
    const int lower_limit = 100;
    const int upper_limit = 1'000;

    std::default_random_engine dre;
    std::uniform_int_distribution<int> marathon_size(lower_limit,upper_limit);

    const int nr_trials = 10'000;

    std::vector<int> histogram_of_errors;
    for ( int ix = 0; ix < 201; ++ix )
        histogram_of_errors.push_back(0);

    for ( int ix = 0; ix < nr_trials; ++ix )
    {
        int nr_runners = marathon_size(dre);
        std::uniform_int_distribution<int> select_runners(1,nr_runners);

        int nr_runners_sampled = nr_runners/(100/percentage_for_sample);

        std::set<int> sampled_runners;
        select_random_without_repetition(sampled_runners, dre, select_runners, nr_runners_sampled);

        int max_seen = *sampled_runners.crbegin();

        double sample_size = static_cast<double>(nr_runners_sampled);
        double estimated_nr_runners = (sample_size+1)/sample_size * max_seen - 1;

        double error_in_estimate = (estimated_nr_runners - static_cast<double>(nr_runners)) /
            static_cast<double>(nr_runners) * 100.0;

        int i_error_in_estimate = static_cast<int>(error_in_estimate);
        if ( i_error_in_estimate > 100 || i_error_in_estimate < -100 ) std::cout << "Way off!!\n";
        else ++histogram_of_errors[i_error_in_estimate+100];
    }

    marathon_print_elements(histogram_of_errors, "\nHistogram of error percentage, from -100 to 100\n");
}
