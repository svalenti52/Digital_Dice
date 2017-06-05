/** \file tp.cpp
 *
 */

#include <vector>
#include <iostream>
#include <random>
#include <string>

template <typename T>
inline void print_elements( const T& coll, const std::string& optstr = "")
    {
        std::cout << optstr;
        for ( const auto& elem : coll ) std::cout << elem << ' ';
    }

int main()
{
    std::default_random_engine dre;
    std::uniform_real_distribution<double> tp_choice_big_roll(0.0, 100.0);
    const int nr_trials = 10000;
    std::vector<double> avg_tp_left;

	for ( int choose_big = 0; choose_big < 101; ++choose_big )
	{
	    int tp_left = 0;

		for (int j = 0; j < nr_trials; j++)
		{
			int m = 200;
			int n = 200;
			while (n != 0)
			{
			    if (m == n) --n;
			    if (n == 0) break;
			    if ( tp_choice_big_roll(dre) < static_cast<double>(choose_big)) --m;
			    else --n;
			}
			tp_left += m;
		}
        avg_tp_left.push_back(static_cast<double>(tp_left)/static_cast<double>(nr_trials));
        std::cout << choose_big << '\n';
	}

    print_elements(avg_tp_left,"\n\nNUMBER OF PORTIONS LEFT ON UNUSED ROLL\n");
}
