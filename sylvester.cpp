/** \file sylvester.cpp
 *
 */

#include <random>
#include <iostream>
//#include <vector>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
#include <boost/geometry/geometries/register/multi_point.hpp>

typedef boost::tuple<float, float> point_type;
typedef point_type pt;

BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)
BOOST_GEOMETRY_REGISTER_MULTI_POINT(std::vector< ::point_type >)
typedef std::vector<pt> vec_pt;

int main()
{
    std::default_random_engine dre;
//    std::mt19937 dre;
    std::uniform_real_distribution<float> radial(0,1);
    std::uniform_real_distribution<float> angular(0, static_cast<float>(2.0*3.14159));

    int nr_concave = 0;
    const int nr_trials = 10'000'000;
    const int quad_lim = 4;
    const int nr_to_disp_dot = nr_trials / 10;

    for ( int ix = 0; ix < nr_trials; ++ix )
    {
        vec_pt vpt;

        for ( int jx = 0; jx < quad_lim; ++jx )
        {
            float rad = std::sqrt(radial(dre));
            float ang = angular(dre);
            vpt.push_back( pt(rad*static_cast<float>(cos(ang)), rad*static_cast<float>(sin(ang))) );
        }

        vec_pt convex_hull;
        boost::geometry::convex_hull(vpt, convex_hull);

        if ( convex_hull.size() < quad_lim + 1 )   // convex hull goes back to and includes starting point
            ++nr_concave;               // (the same point is included twice to "close" the shape
                                        // that's why a four-sided hull contains five points
        if ( ix % nr_to_disp_dot == 0 ) std::cout << ". " << std::flush;
    }

    std::cout << "\nFor the case of 4-sided hulls\n";
    std::cout << "Nr Concave Hulls: " << nr_concave << '\n';
    std::cout << "Prob Concave: " << static_cast<double>(nr_concave)/static_cast<double>(nr_trials) << '\n';

}
