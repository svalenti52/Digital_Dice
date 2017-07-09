/**
 * \file shopping_grid.cpp
 *
 */

#include <random>
#include <iostream>
#include <vector>
#include <algorithm>

/*--------------------------------------------------------------------------*/

enum class Direction { SOUTH, WEST };

class shopping_grid
{
    int southern_loc;
    int western_loc;
    int southern_axis;
    int western_axis;
    int stop_lights_count;
    bool at_destination;
public:
    shopping_grid(int i_loc) : southern_loc(i_loc), western_loc(i_loc),
        southern_axis(1), western_axis(1), stop_lights_count(0), at_destination(false) {}
    bool arrive_at_destination() { return at_destination; }
    double get_stop_count() { return static_cast<double>(stop_lights_count); }
    void cross_street(Direction D)
        {
            if ( D == Direction::SOUTH )
                {
                    if ( southern_loc == southern_axis )
                        {
                            if ( western_loc == western_axis )
                                {
                                    at_destination = true;
                                    return; // at destination
                                }
                            else
                                {
                                    // must wait for stoplight
                                    // so increment stop_lights_count
                                    ++stop_lights_count;
                                    --western_loc;
                                }
                        }
                    else
                        {
                            --southern_loc;
                        }
                }
            else
                {
                    if ( western_loc == western_axis )
                        {
                            if ( southern_loc == southern_axis )
                                {
                                    at_destination = true;
                                    return; // at destination
                                }
                            else
                                {
                                    // must wait for stoplight
                                    // so increment stop_lights_count
                                    ++stop_lights_count;
                                    --southern_loc;
                                }
                        }
                    else
                        {
                            --western_loc;
                        }
                }
        }
    friend std::ostream& operator << (std::ostream& o, shopping_grid& s);
};

std::ostream& operator << (std::ostream& o, shopping_grid& s)
    {
        o << "southern=" << s.southern_loc << "  western=" << s.western_loc
            << "  stop_lights_count = " << s.stop_lights_count << '\n';
        return o;
    }

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

int main(int argn, char* argv[])
{
    using namespace std;
    using Dir = Direction;

    if ( argn != 2 )
        {
            cout << "usage: ./a <pos-num>\n";
            return 1;
        }


    default_random_engine dre;
    bernoulli_distribution direction_south;

    const int nr_trials = 1000000;
    double avg_nr_stop_lights = 0;
    int init_loc = atoi(argv[1]) + 1;

    for ( int ix = 0; ix < nr_trials; ++ix )
    {
        shopping_grid sg{ shopping_grid(init_loc) };

        // std::cout << sg;
        while ( !sg.arrive_at_destination() )
            {
                if ( direction_south(dre) )
                    sg.cross_street(Dir::SOUTH);
                else
                    sg.cross_street(Dir::WEST);
                // std::cout << sg;
            }
        avg_nr_stop_lights += sg.get_stop_count();
    }

    std::cout << "avg nr of stop lights encountered = "
        << avg_nr_stop_lights / static_cast<double>(nr_trials) << '\n';
}
