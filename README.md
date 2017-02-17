# Digital_Dice
Digital Dice Problems by Paul Nahin

Compiled with
g++ -std=c++14

17. Waiting for Buses
	Problem: A set of N buses are distributed to arrive within a one hour
	window. One arrival is set to the end of the hour, the other N-1 arrive at
	random, uniformly distributed arrival times with the hour.  If a rider
	also arrives at a random, uniformly distributed time within the hour, what
	is average wait time for a bus to arrive?

	The answer is 1/(N+1) hours (or 60/(N+1) minutes). The author also
	provides an analytical approach which turns out to be more involved than
	one would expect!

	The file bus.cpp is based on a simple approach that initializes the buses
	vector each time through the loop. I ran it through gprof and discovered
	that a relatively "massive" amount of time was spent destroying the vector
	and its contained objects, not to mention the amount of time constructing
	them again. The file bus3.cpp adds a couple of new member functions to the
	bus and rider classes (for updating the arrival times) and then moves
	construction outside of the loop. Note that we are looping 10,000,000

	g++ -std=c++14 -O2 bus.cpp		=> ~6600 ms
	g++ -std=c++14 -O2 bus3.cpp		=> ~690  ms
