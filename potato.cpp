/** \file potato.cpp
 *
 */

#include <random>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <functional>
#include "utilities.hpp"

class customer
{
    int tag;
    double prev_cust_arrival_time_point;
    double prior_to_arrival_time_duration;
    double arrival_time_point;
    double queue_time_duration;
    double service_begin_time_point;
    double service_end_time_point;
    double service_time_duration;
public:
    customer(int i_tag, double i_base_time, double i_prior_to_arrival_time_duration,
        double i_service_time_delta, double prev_service_time_end) :
        tag(i_tag),
        prev_cust_arrival_time_point(i_base_time),
        prior_to_arrival_time_duration(i_prior_to_arrival_time_duration),
        service_time_duration(i_service_time_delta)
        {
            arrival_time_point = prev_cust_arrival_time_point + prior_to_arrival_time_duration;
            service_begin_time_point = std::max(arrival_time_point, prev_service_time_end);
            service_end_time_point = service_begin_time_point + service_time_duration;
            queue_time_duration = prev_service_time_end - arrival_time_point > 0.0 ?
                            prev_service_time_end - arrival_time_point : 0.0;
        }
    double get_service_begin() { return service_begin_time_point; }
    double get_service_end() { return service_end_time_point; }
    double get_arrival_time() { return arrival_time_point; }
    double get_queue_time() { return queue_time_duration; }
    double get_service_time() { return service_time_duration; }
    friend std::ostream& operator << (std::ostream& o, const customer& c);
    bool operator < (const customer& rhs) const { return tag < rhs.tag; }
//    bool operator == (const customer& rhs) const { return tag == rhs.tag; }
};

std::ostream& operator << (std::ostream& o, const customer& c)
{
    o << c.tag << "  " << c.arrival_time_point << "  " << c.service_end_time_point
        << "  " << c.queue_time_duration << '\n';
    return o;
}


int main(int argn, char* argv[])
{

    std::default_random_engine dre;
    std::exponential_distribution<double> arrival_time(30.0/3600.0);
    std::exponential_distribution<double> service_time(40.0/3600.0);

//    int len_queue = 0;
//    int max_len_queue = 0;

    const double nr_seconds = 36000.0;

    std::vector<customer> customers;

    double arrival_delta_first = arrival_time(dre);
    customers.push_back(customer(0, 0.0, arrival_delta_first, service_time(dre), 0.0));
    double prev_arrival = arrival_delta_first;
    int ix = 0;

    while ( prev_arrival < nr_seconds )
    {
        double service_end_prev = customers[ix].get_service_end();
        ++ix;
        customers.push_back(customer(ix, prev_arrival, arrival_time(dre), service_time(dre), service_end_prev));
        prev_arrival = customers[ix].get_arrival_time();
    }
    std::cout << "Number of customers = " << customers.size() << '\n';

    print_elements(customers, "By Customer Nr - Arrival Times - Ser Time End - Queue Time\n");

    int q_len = 0;
    int max_q_len = 0;
    double avg_q_len = 0.0;
    double max_time = 0.0;
    double avg_time_in_sys = 0.0;

    std::queue<customer> wait_in_line;

    for ( customer cust : customers )
        {
            if ( max_time < cust.get_queue_time() + cust.get_service_time() )
                max_time = cust.get_queue_time() + cust.get_service_time();
            avg_time_in_sys += cust.get_queue_time() + cust.get_service_time();
            double this_arrival_time_point = cust.get_arrival_time();

            if ( cust.get_queue_time() > 0.0 )
                wait_in_line.push(cust);
            for ( int ix = 0; ix < wait_in_line.size(); ++ix )
                {
                    auto waiting_cust = wait_in_line.front();
                    if ( waiting_cust.get_service_begin() < this_arrival_time_point )
                        wait_in_line.pop();
                    else
                        break;
                }
            avg_q_len += wait_in_line.size();
            if ( max_q_len < wait_in_line.size() )
                max_q_len = wait_in_line.size();
         }

    while ( !wait_in_line.empty() ) wait_in_line.pop();

    std::set<customer> in_system;
    std::cout << "\nqueue size at end = " << wait_in_line.size() << '\n';
    avg_time_in_sys /= customers.size();

    std::cout << "\nAverage Time in Deli (minutes) = " << avg_time_in_sys/60.0 << '\n';
    std::cout << "Max Time in Deli (minutes) = " << max_time/60.0 << '\n';
    std::cout << "Average Queue Length = " << avg_q_len/static_cast<double>(customers.size()) << '\n';
    std::cout << "Max Queue Length = " << max_q_len << '\n';

    double avg_nr_in_system = 0;
    const int time_tick_max = 36000;
    int idle_time = 0;
    double avg_queue_length = 0.0;
    int max_queue_length = 0;

    for ( int time_tick = 1; time_tick <= time_tick_max; ++time_tick )
    {
        for ( customer cust : customers )
            {
                double time_tk = static_cast<double>(time_tick);
                if ( time_tk > cust.get_arrival_time() &&
                     time_tk < cust.get_service_end() )
                    {
                        in_system.insert(cust);
                    }
                if ( time_tk > cust.get_service_end() )
                    in_system.erase(cust);
            }

        int nr_in_system = in_system.size();
        avg_nr_in_system += static_cast<double>(nr_in_system);
//        std::cout << "nr_in_system = " << nr_in_system << '\n';
        if ( in_system.size() == 0 )
            ++idle_time;
        avg_queue_length += in_system.size() == 0 ? 0.0 : static_cast<double>(in_system.size() - 1);
        int current_queue_length = in_system.size() - 1;
        max_queue_length = std::max(max_queue_length, current_queue_length);
    }
//    print_elements(in_system, "Customers in System\n");
    avg_nr_in_system /= static_cast<double>(time_tick_max);
    std::cout << "\n\naverage number in system = " << avg_nr_in_system << '\n';
    std::cout << "percentage idle time = "
        << static_cast<double>(idle_time)/static_cast<double>(time_tick_max)*100.0 << '\n';
    std::cout << "average queue length = " << avg_queue_length/static_cast<double>(time_tick_max) << '\n';
    std::cout << "maximum queue length = " << max_queue_length << '\n';
}
