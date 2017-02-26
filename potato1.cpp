// potato1.cpp

#include <random>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <functional>
#include "utilities.hpp"

/*--------------------------------------------------------------------------*/

const double service_end_time_too_high = 1000000.0;

class customer
{
    int tag;
    double await_next_arrival_timepoint;	// arrival_time of (n-1)th customer
    double interarrival_duration;
    double arrival_time;		// actual arrival time of nth customer
    double wait_queue_duration;
    double service_begin_time;
    double service_duration;
    double service_end_time;
    bool being_served;
    bool been_served;
public:
    customer(int i_tag, double i_base_time, double i_prior_to_arrival_time_duration,
        double i_service_time_delta) :
        tag(i_tag),
        await_next_arrival_timepoint(i_base_time),
        interarrival_duration(i_prior_to_arrival_time_duration),
        service_duration(i_service_time_delta)
        {
            arrival_time = await_next_arrival_timepoint + interarrival_duration;
            wait_queue_duration  = 0; // do not know what these are yet
            service_begin_time = 0; // depends on number of servers
            service_end_time = service_end_time_too_high; // we do know what service_duration (service time duration) is ...
            // need to find service_begin_time (or equivalently wait_queue_duration), then we have full knowledge
            // i.e., service_end_time = service_begin_time + service_duration
            // and   wait_queue_duration  = service_begin_time - arrival_time
            being_served = false;
            been_served = false;
        }
    int get_tag() const { return tag; }
    void set_service_begin(double service_begin_tp)
        {
            service_begin_time = service_begin_tp;
            service_end_time = service_begin_time + service_duration;
            wait_queue_duration  = service_begin_time - arrival_time < 1.0 ? 0.0 : service_begin_time - arrival_time;
            being_served = true;
        }
    bool not_been_serviced() { return !been_served; }
    bool not_being_serviced() { return !being_served; }
    bool being_serviced() { return being_served; }
    bool been_serviced() { return been_served; }
    void set_being_serviced() { being_served = true; been_served = false; }
    void set_been_serviced() { been_served = true; being_served = false; }
    double get_service_begin() { return service_begin_time; }
    double get_service_end() { return service_end_time; }
    double get_arrival_time() { return arrival_time; }
    double get_queue_time() { return wait_queue_duration; }
    double get_service_time() { return service_duration; }
    friend std::ostream& operator << (std::ostream& o, const customer& c);
    bool operator < (const customer& rhs) const { return tag < rhs.tag; }
//    bool operator == (const customer& rhs) const { return tag == rhs.tag; }
};

std::ostream& operator << (std::ostream& o, const customer& c)
{
    o << "tag=" << c.tag << "  arrival_time=" << c.arrival_time << "  service_begin_time="
        << c.service_begin_time << "  service_duration=" << c.service_duration << "  service_end_time=" << c.service_end_time
        << "  wait_queue_duration=" << c.wait_queue_duration << "  been_served=" << c.been_served << '\n';
    return o;
}

/*--------------------------------------------------------------------------*/

const int clerk_free = -1;

class clerk
{
    int customer_nr;
    double seconds_idle;
public:
    clerk(int i_customer_nr) : customer_nr(i_customer_nr) {}
    clerk() : customer_nr(clerk_free) {}
    void set_customer_nr(int nr) { customer_nr = nr; }
    int get_customer_nr() { return customer_nr; }
    bool is_clerk_free() { return customer_nr == clerk_free; }
    double get_seconds_idle() { return seconds_idle; }
    void operator += (double idle_secs) { seconds_idle += idle_secs; }
};

/*--------------------------------------------------------------------------*/

int main(int argn, char* argv[])
{

    std::default_random_engine dre;
    std::exponential_distribution<double> arrival_time(30.0/3600.0);
    std::exponential_distribution<double> service_time(40.0/3600.0);

    const double nr_seconds = 36000.0;
    const double nr_time_ticks = 36000.0;
    int nr_trials = 7;

    for ( int ix=0; ix<nr_trials; ++ix )
    {

        std::vector<customer> customers;

        double arrival_delta_first = arrival_time(dre);
        customers.push_back(customer(0, 0.0, arrival_delta_first, service_time(dre)));
        double prev_arrival = arrival_delta_first;
        int customer_number = 1;

        while ( prev_arrival < nr_seconds )
        {
            customers.push_back(customer(customer_number, prev_arrival, arrival_time(dre), service_time(dre)));
            prev_arrival = customers[customer_number].get_arrival_time();
            ++customer_number;
        }
        std::cout << "Number of customers = " << customers.size() << '\n';

        const int nr_clerks = 1;
        std::queue<clerk> free_clerks;
        std::vector<clerk> clerks;
        for ( int jx=0; jx<nr_clerks; ++jx )
        {
            free_clerks.push(clerk());
            clerks.push_back(clerk());
        }

        std::set<int> in_system;
        std::set<int> in_service;

        double avg_q_len = 0.0;
        int max_q_len = 0;
        int cur_q_size = 0;
        double avg_time_in_sys = 0.0;
        double max_time_in_sys = 0.0;

        for ( int time_tick = 1; time_tick <= nr_seconds; ++time_tick )
        {
            for ( customer& cust : customers )
                {
                    double time_tk = static_cast<double>(time_tick);

                    if ( cust.being_serviced() && time_tk > cust.get_service_end() )
                        {
                            free_clerks.push(clerk());
                            for ( clerk& ck : clerks )
                                {
                                    if ( !ck.is_clerk_free() )
                                        {
                                            ck.set_customer_nr(clerk_free);
                                            break;
                                        }
                                }
                            in_service.erase(cust.get_tag());
                            in_system.erase(cust.get_tag());
                            cust.set_been_serviced();
                        }

                    if ( cust.not_being_serviced() && cust.not_been_serviced() && time_tk > cust.get_arrival_time() )
                        {
                            in_system.insert(cust.get_tag());
                            if ( free_clerks.empty() == false )
                            {
                                in_service.insert(cust.get_tag());
                                auto cust_it = in_service.begin();
                                free_clerks.front().set_customer_nr(*cust_it);
                                free_clerks.pop();
                                for ( clerk& ck : clerks )
                                    {
                                        if ( ck.is_clerk_free() )
                                            {
                                                ck.set_customer_nr(*cust_it);
                                                break;
                                            }
                                    }
                                cust.set_service_begin(time_tk);
                                cust.set_being_serviced();
                            }
                        }
                } // end customers

                cur_q_size = static_cast<double>(in_system.size() - in_service.size());
                max_q_len = std::max(max_q_len,cur_q_size);
                avg_q_len += static_cast<double>(cur_q_size);
                for ( clerk& ck : clerks )
                    if ( ck.is_clerk_free() )
                        ck += 1.00;  // this is 1 second per tick, has to adjusted according
                                    // the granularity of time ticks
        }  // end time ticks

        for ( customer& cust : customers )
            {
                if ( cust.been_serviced() || cust.being_serviced() )
                    {
                        avg_time_in_sys += cust.get_service_end() - cust.get_arrival_time();
                        max_time_in_sys = std::max(max_time_in_sys, (cust.get_service_end() - cust.get_arrival_time()));
                    }
            }
        std::cout << "average time in deli (minutes) = " << avg_time_in_sys/(customers.size() - cur_q_size)/60.0 << '\n';
        std::cout << "max time in deli = " << max_time_in_sys/60.0 << '\n';
        std::cout << "last_q size = " << cur_q_size << '\n';
        std::cout << "avg queue size = " << avg_q_len/nr_seconds << '\n';
        std::cout << "max queue len = " << max_q_len << '\n';
        for ( clerk& ck : clerks )
            std::cout << "clerk % idle time = " << (ck.get_seconds_idle()/nr_seconds) * 100.0 << '\n';
        std::cout << '\n';

    }  // nr of trials
    return 0;
}
