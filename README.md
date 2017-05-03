# Digital_Dice
Digital Dice Problems by Paul Nahin

Compiled with
g++ -std=c++14

Chapter 0. Introduction (Convex Hulls) <br>

    Problem: What is the probability that four randomly chosen points within a
    unit square form a quadrilateral that is concave?  We are here taking the
    property of "concavity" to mean non-convex. The quadrilateral is concave if
    it is possible to contain one of points in the interior of a triangle formed
    by connecting the other three points.

Chapter 1. The Clumsy Dishwasher Problem <br>

    Problem: There are five dishwashers working in a restaurant, and after working
    for a week, they have broken five dishes, with four of them attributable to
    one dishwasher. How likely is it due to bad fortune rather than being clumsy?
    In other words, assuming an equal load for all, what are the odds that this
    would have happened?

Chapter 2. Will Lil and Bill Meet at the Malt Shop? <br>

    Problem: What is the probability the Lil and Bill will meet at the malt shop
    if they agree to meet within a 1/2 hour window (say 3:30 to 4:00) but with the
    conditions that whenever Lil comes she will only wait five minutes if Bill does
    not arrive, and whenever Bill comes he will only wait seven minutes if Lil does
    not arrive?  Neither will wait past 4:00.

Chapter 3. A Parallel Parking Question <br>

    Problem: Cars are parallel parked in single narrow lot (there is only one row).
    Given n cars parked in this fashion, what is the liklihood of randomly choosing
    a car that is member of a mutually nearest neighbor pair? That is, the car chosen
    is the nearest neighbor to another car and that car happens be the nearest
    neighbor of the chosen car also.

Chapter 4. A Curious Coin-Flipping Game <br>

    Problem: Three men have L, M, and N coins which they match by flipping so that
    the odd man wins - he gets the other two's coins. If all three match, they all
    keep their coins. What is the average number of flips that occur till one runs
    out of coins? It is suggested to not only do ths assuming that coins are fair
    (probability is 0.5 that it's heads) but unfair also.

Chapter 5. The Gamow-Stern Elevator Puzzle <br>

    Problem: Gamow and Stern both have offices in a seven storey building - Gamow
    on the second floor and Stern on the sixth floor. Assuming that a single
    elevator is continously travelling to the top floor and then to the bottom
    floor, this accounts for Gamow seeing the elevator going down 5/6 of the
    time and Stern seeing the elevator going up 5/6 of the time. But what is the
    situation when there are two or three independent elevators?

Chapter 6. Steve's Elevator Problem <br>

    Problem: In effect, Steve gets off on the 9th floor of an 11 storey building.
    (It is a different floor in the book but the elevator doesn't stop at every
    floor either.) How many stops on average does Steve experience when travelling
    to his floor? Determine this as a function of the number of additional riders.

Chapter 7. The Pipe Smoker's Discovery <br>

    Problem: A pipe smoker has two 40-match match books in his pocket. If he selects
    a match book at random to light his pipe, how many matches does he use in total
    when one of the match books becomes empty?

Chapter 8. A Toilet Paper Dilemma <br>

    Problem: If a stall is supplied with two rolls of toilet paper, each of length
    n, we have the situation where big roll choosers enter with probability p, and
    little roll choosers enter with the probability 1-p. As suggested by the name,
    the big roll choosers always choose the roll with the most left and little roll
    choosers always choose the roll with the least left. TBD

Chapter 9. The Forgetful Burglar Problem <br>

Chapter 10. The Umbrella Quandary <br>

Chapter 11. The Case of the Missing Senators <br>

Chapter 12. How Many Runners in a Marathon? <br>

Chapter 13. A Police Patrol Problem <br>

    Problem: A high-speed two-lane road (bidirectional) is the subject of patrol
    for accidents. The problem is seeing which method allows the quickest response:
    Having one patrol car sit in the middle, or having the car travel continuously
    from one end of the road to the other until the accident is reported. We also
    consider an additional case where there are two cars independently implementing
    the latter. The possibilities are further "forked" by another consideration:
    the median is either grass or a concrete barrier - grass means travelling
    immediately to the site of the accident whereas the barrier means possibly
    travelling to the end of the road to turn around to get to the accident.
    The problem is one of determining the minimum distance to the site of the
    accident under these different schemes.

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
	result. Also, the file parrando1.cpp contains just the second game to
	demonstrate that it is a losing game.

Chapter 15. How Long is the Wait to Get the Potato Salad? <br>

Chapter 16. The Appeals Court Paradox <br>

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

Chapter 18. Waiting for Stoplights <br>

Chapter 19. Electing Emperors and Popes <br>

Chapter 20. An Optimal Stopping Problem <br>

Chapter 21. Chain Reactions, Branching Processes, and Baby Boys
