/**
 * \file monotonic.cpp
 *
 */

#include <iostream>
#include <vector>
#include <random>

int main()
{
    std::default_random_engine dre;
    std::uniform_real_distribution<double> sequence(0.0,1.0);

    const int nr_trials = 10'000'000;

    int sum_len_of_seq = 0;
    int max_len_of_seq = 0;

    for ( int ix = 0; ix < nr_trials; ++ix )
    {

        double greatest_in_sequence = sequence(dre);
        int len_of_seq = 1;

        bool monotonic_increment = true;

        while ( monotonic_increment )
        {
            double next_in_sequence = sequence(dre);
            if ( next_in_sequence <= greatest_in_sequence )
                monotonic_increment = false;
            else
                greatest_in_sequence = next_in_sequence;
            ++len_of_seq;
            if ( max_len_of_seq < len_of_seq ) max_len_of_seq = len_of_seq;
        }
        sum_len_of_seq += len_of_seq;
    }

    std::cout << "expected value of sequence lengths is = "
        << static_cast<double>(sum_len_of_seq) / static_cast<double>(nr_trials) << '\n';

    std::cout << "maximum sequence length = " << max_len_of_seq << '\n';

    return 0;
}
