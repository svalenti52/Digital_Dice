/** \file bus.cpp
 *
 */

#include <random>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <val/util.h>

/*--------------------------------------------------------------------------*/

class rider;

/*--------------------------------------------------------------------------*/

class bus
{
    int ix_bus;
    double arrival_tp;
public:
    bus(int i_ix_bus, double i_arrival_tp) : ix_bus(i_ix_bus), arrival_tp(i_arrival_tp) {}
    void set_arrival_time(double t) { arrival_tp = t; }
    friend std::ostream& operator << (std::ostream& o, bus& b);
    friend double closest_bus_time(std::vector<bus>& vb, rider& r);
};

std::ostream& operator << (std::ostream& o, bus& b)
    {
        o << "id=" << b.ix_bus << "  arrival=" << b.arrival_tp << '\n';
        return o;
    }

/*--------------------------------------------------------------------------*/

class rider
{
    double bus_stop_tp;
public:
    rider(double i_bus_stop_tp) : bus_stop_tp(i_bus_stop_tp) {}
    void set_arrival_time(double t) { bus_stop_tp = t; }
    friend std::ostream& operator << (std::ostream& o, rider& r);
    friend double closest_bus_time(std::vector<bus>& vb, rider& r);
};

std::ostream& operator << (std::ostream& o, rider& r)
{
    o << "rider time point = " << r.bus_stop_tp << '\n';
    return o;
}

/*--------------------------------------------------------------------------*/

double closest_bus_time(std::vector<bus>& vb, rider& r)
{
    double min_time = 100.0;
    for ( bus& b : vb )
        {
            double delta_time = b.arrival_tp - r.bus_stop_tp;
            if ( (delta_time >= 0.0) && (delta_time < min_time) )
                min_time = delta_time;
        }
    return min_time;
}


/*--------------------------------------------------------------------------*/

int main()
{
    using namespace std;

    default_random_engine dre;
    uniform_real_distribution<double> uniform_dist_over_1(0.0,1.0);

    const int nr_trials = 10'000'000;
    const int nr_busses = 5;

    double avg_closest_bus_time = 0.0;

    StopWatch stopWatch;

    vector<bus> busses { bus(0, 1.0) };
    for ( int jx = 1; jx < nr_busses; ++jx )
    	busses.push_back(bus(jx, uniform_dist_over_1(dre)));
    rider our_rider(uniform_dist_over_1(dre));

    for ( int ix = 0; ix < nr_trials; ++ix )
    {
        our_rider.set_arrival_time(uniform_dist_over_1(dre));

        for ( int jx = 1; jx < nr_busses; ++jx )
        	busses[jx].set_arrival_time(uniform_dist_over_1(dre));

        avg_closest_bus_time += closest_bus_time(busses, our_rider);
    }

    cout << "average closest bus time (min) = "
         << (avg_closest_bus_time / static_cast<double>(nr_trials)) * 60.0 << '\n';

    stopWatch.stop();
}
