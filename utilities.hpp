/**
 * \file utilities.hpp
 *
 * @tparam T
 * @param coll
 * @param optstr
 */


template <typename T>
inline void print_elements( const T& coll, const std::string& optstr = "")
    {
        std::cout << optstr;
        for ( const auto& elem : coll ) std::cout << elem << ' ';
    }

template <typename T>
inline void marathon_print_elements( const T& coll, const std::string& optstr = "")
    {
        std::cout << optstr;
        int ix = -100;
        for ( const auto& elem : coll ) std::cout << ix++ << ':' << elem << ' ';
    }

template <typename Cont, typename Engine, typename Distrib>
inline void select_random_without_repetition(Cont& assoc, Engine& e, Distrib& d, int sample_size)
    {
        // assumes a unique element associative container with the standard insert operation
        // (not very satisfactory, a random number of some sort to be the element)
        // probably better if remove the engine and distribution as parameters and
        // define them locally?!
        for ( int ix=0; ix<sample_size; ++ix )
            while ( !assoc.insert(d(e)).second );
    }
