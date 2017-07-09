/**
 * \file patrol.cpp
 *
 */

#include <random>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include "utilities.hpp"

enum class median_type { GRASS, CONCRETE };

class Pos_Dir
{
public:
    enum direction { RIGHT, LEFT };
private:
    double pos;
    direction dir;
public:
    Pos_Dir(double i_pos, double i_dir) : pos(i_pos) { i_dir < 0.5 ? dir = RIGHT : dir = LEFT; }
    double get_pos() { return pos; }
    direction get_dir() { return dir; }
//    template <median_type M>friend double operator -(Pos_Dir static_obj, Pos_Dir moving_obj);
    template <median_type M>friend double distance(Pos_Dir static_obj, Pos_Dir moving_obj);
};

template <median_type M> double distance(Pos_Dir static_obj, Pos_Dir moving_obj)
{
    double d = std::fabs(static_obj.get_pos() - moving_obj.get_pos());;
    switch (M)
    {
        case median_type::GRASS:
            break;
        case median_type::CONCRETE:
            if ( moving_obj.get_dir() == Pos_Dir::RIGHT && static_obj.get_dir() == Pos_Dir::RIGHT )
                {
                    if ( moving_obj.get_pos() > static_obj.get_pos() )
                        d = 2.0 - d;
                }
            else if ( moving_obj.get_dir() == Pos_Dir::RIGHT )
                {
                        d = 2.0 - moving_obj.get_pos() - static_obj.get_pos();
                }
            else if ( static_obj.get_dir() == Pos_Dir::RIGHT )
                {
                        d = moving_obj.get_pos() + static_obj.get_pos();
                }
            else
                {
                    if ( moving_obj.get_pos() < static_obj.get_pos() )
                        d = 2.0 - d;
                }
            break;
    }
    return d;
}

int main(int argn, char* argv[])
{

    std::default_random_engine dre;
    std::uniform_real_distribution<double> on_road(0,1);

    const int nr_trials = 1'000'000;
    std::vector<double> tot_distance_grass { 0.0, 0.0, 0.0, 0.0, 0.0,
                                             0.0, 0.0, 0.0, 0.0, 0.0 };
    std::vector<double> tot_distance_concrete { 0.0, 0.0, 0.0, 0.0, 0.0,
                                                0.0, 0.0, 0.0, 0.0, 0.0 };

    for ( int ix = 0; ix < nr_trials; ++ix )
    {
        std::vector<double> distance_on_grass;
        std::vector<double> distance_on_concrete;

        Pos_Dir accident(on_road(dre), on_road(dre));

        std::vector<Pos_Dir> patrol_car;
        for ( int jx = 0; jx < 10; ++jx )
            {
                if ( jx == 0 ) patrol_car.push_back(Pos_Dir(0.5, on_road(dre)));
                else patrol_car.push_back(Pos_Dir(on_road(dre), on_road(dre)));
                distance_on_grass.push_back(distance<median_type::GRASS>(accident, patrol_car[jx]));
                distance_on_concrete.push_back(distance<median_type::CONCRETE>(accident, patrol_car[jx]));
            }
        for ( int jx = 0; jx < 10; ++jx )
            {
                if ( jx == 0 )
                    {
                        tot_distance_grass[jx] += *std::min_element(distance_on_grass.begin(), distance_on_grass.begin() + 1);
                        tot_distance_concrete[jx] += *std::min_element(distance_on_concrete.begin(), distance_on_concrete.begin() + 1);
                    }
                else
                    {
                        tot_distance_grass[jx] += *std::min_element(distance_on_grass.begin()+1, distance_on_grass.begin() + jx + 1);
                        tot_distance_concrete[jx] += *std::min_element(distance_on_concrete.begin()+1, distance_on_concrete.begin() + jx + 1);
                    }
            }
    }
    int nr_rand_patrol_cars = 0;
    for ( double dist : tot_distance_grass )
        {
            std::cout << "For Nr Random Patrol Cars = " << nr_rand_patrol_cars
                << " avg min dist to accident on grass median = "
                << dist / static_cast<double>(nr_trials) << '\n';
            ++nr_rand_patrol_cars;
        }
    std::cout << '\n' << '\n';

    nr_rand_patrol_cars = 0;
    for ( double dist : tot_distance_concrete )
        {
            std::cout << "For Nr Random Patrol Cars = " << nr_rand_patrol_cars
                << " avg min dist to accident on concrete median = "
                << dist / static_cast<double>(nr_trials) << '\n';
            ++nr_rand_patrol_cars;
        }
}
