# Digital_Dice
Digital Dice Problems by Paul Nahin

Compiled with
g++ -std=c++14

Chapter 14. Parrondo's Paradox <br>

	Problem: Two coin-flipping gambling games are proposed. The first one is
	with a slightly unfavorable coin (let us say it lands as heads slightly
	less than half of the time). The second one is more complicated, involving
	two coins, one very unfavorable, the other a favorable coin but no match
	for the unfavorable one. The second game is complicated by the fact that
	1/3 of the time you play with the very unfavorable coin and 2/3 of the
	time you play with the favorable one. Given the right parameterization, it
	turns out that both games are losers for you. But astoundingly, if you
	introduce another coin, this one finally a fair coin, and use it to choose
	which game you play (both losing propositions), you will find that this
	additional randomization is sufficient to win!

	The file parrondo.cpp contains the parameterization necessary to prove the

Chapter 17. Waiting for Buses <br>

	Problem: A set of N buses are distributed to arrive within a one hour
	window. One arrival is set to the end of the hour, the other N-1 arrive at
	random, uniformly distributed arrival times within the hour.  If a rider
	also arrives at a random, uniformly distributed time within the hour, what
	is the average wait time for a bus to arrive?

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
	times. The run time (on my computer) is given for the files:

	g++ -std=c++14 -O2 bus.cpp		=> ~6600 ms <br>
	g++ -std=c++14 -O2 bus3.cpp		=> ~690  ms
