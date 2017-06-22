# Digital_Dice
Digital Dice Problems by Paul Nahin

Compiled with
g++ -std=c++14

Chapter 0. Introduction (Convex Hulls)

    Problem: What is the probability that four randomly chosen points within a
    unit square form a quadrilateral that is concave?  We are here taking the
    property of "concavity" to mean non-convex. The quadrilateral is concave if
    it is possible to contain one of points in the interior of a triangle formed
    by connecting the other three points. The programs use the convex_hull function
    of the Boost Geometry library.
    
    Associated files: sylvester.cpp and sylvester1.cpp.

Chapter 1. The Clumsy Dishwasher Problem

    Problem: There are five dishwashers working in a restaurant, and after working
    for a week, they have broken five dishes, with four of them attributable to
    one dishwasher. How likely is it due to bad fortune rather than being clumsy?
    In other words, assuming an equal load for all, what are the odds that this
    would have happened?
    
    Associated files: dishwasher.cpp and dishwasher2.cpp.

Chapter 2. Will Lil and Bill Meet at the Malt Shop?

    Problem: What is the probability the Lil and Bill will meet at the malt shop
    if they agree to meet within a 1/2 hour window (say 3:30 to 4:00) but with the
    conditions that whenever Lil comes she will only wait five minutes if Bill does
    not arrive, and whenever Bill comes he will only wait seven minutes if Lil does
    not arrive?  Neither will wait past 4:00.
    
     Associated file: maltshop.cpp.

Chapter 3. A Parallel Parking Question

    Problem: Cars are parallel parked in single narrow lot (there is only one row).
    Given n cars parked in this fashion, what is the liklihood of randomly choosing
    a car that is member of a mutually nearest neighbor pair? That is, the car chosen
    is the nearest neighbor to another car and that car happens be the nearest
    neighbor of the chosen car also.
    
     Associated files: parkinglot.cpp and parkinglot4.cpp.

Chapter 4. A Curious Coin-Flipping Game

    Problem: Three men have L, M, and N coins which they match by flipping so that
    the odd man wins - he gets the other two's coins. If all three match, they all
    keep their coins. What is the average number of flips that occur till one runs
    out of coins? It is suggested to not only do ths assuming that coins are fair
    (probability is 0.5 that it's heads) but unfair also.
    
     Associated file: cointoss.cpp.

Chapter 5. The Gamow-Stern Elevator Puzzle

    Problem: Gamow and Stern both have offices in a seven storey building - Gamow
    on the second floor and Stern on the sixth floor. Assuming that a single
    elevator is continously travelling to the top floor and then to the bottom
    floor, this accounts for Gamow seeing the elevator going down 5/6 of the
    time and Stern seeing the elevator going up 5/6 of the time. But what is the
    situation when there are two or three independent elevators?
    
     Associated file: gamow_elevator.cpp.

Chapter 6. Steve's Elevator Problem <br>

    Problem: In effect, Steve gets off on the 9th floor of an 11 storey building.
    (It is a different floor in the book but the elevator doesn't stop at every
    floor either.) How many stops on average does Steve experience when travelling
    to his floor? Determine this as a function of the number of additional riders.
    
     Associated file: steve_elevator.cpp.

Chapter 7. The Pipe Smoker's Discovery <br>

    Problem: A pipe smoker has two 40-match match books in his pocket. If he selects
    a match book at random to light his pipe, how many matches does he use in total
    when one of the match books becomes empty?
    
     Associated file: matches.cpp and matches_banach.cpp.

Chapter 8. A Toilet Paper Dilemma <br>

    Problem: If a stall is supplied with two rolls of toilet paper, each of length
    n, we have the situation where big roll choosers enter with probability p, and
    little roll choosers enter with the probability 1-p. As suggested by the name,
    the big roll choosers always choose the roll with the most left and little roll
    choosers always choose the roll with the least left. TBD
    
     Associated file: tp.cpp.

Chapter 9. The Forgetful Burglar Problem <br>

    Problem: This is a one-dimensional random walk problem - for an infinite number
    of houses lined up in a row, how likely is a burglar to revisit a home that he
    already visited? He is equally likely at each step to do one of four things:
    1) go two houses to the left; 2) go one house to the left; 3) go one house to
    the right; 4) go two houses to the right. The goal is to determine the probability
    that he will revisit in n visits (steps).
    
     Associated file: forget_burglar.cpp.

Chapter 10. The Umbrella Quandary <br>

    Problem: A man travels between office and home each day and carries an umbrella
    with him if it is raining. He starts with having m umbrellas at home and n unbrellas
    at the office. How many days is he able to go on average until he is soaked? Calculate
    the number of days based on the probabilities of it raining being 0.01 to 0.99.
    Remember that he does not carry an umbrella with him if it is not raining. And obviously
    he is soaked when he has to travel without an umbrella.
    
     Associated file: umbrella.cpp.

Chapter 11. The Case of the Missing Senators <br>

    Problem: Given the number of senators voting against a bill and a number of senators
    missing (randomly chosen among for/against), what is the probability of a bill being
    voted down?  In particular figure it out for Against=49, and Missing=3, Missing=4, and
    Missing=5. A bill is voted down if the number of senators against is greater than the
    number of senators for a bill (the missing are not present to vote).
    
     Associated file: senators.cpp.

Chapter 12. How Many Runners in a Marathon? <br>

    Problem: Based on seeing a sample of the number of runners in a marathon, and also
    seeing the numbers for identification assigned to each runner in the sample, extrapolate
    to approximate the total number of runners in the marathon. Use the formula
    N = (n+1)/n * max_sample - 1, and develop histograms for a 2%, 5%, 10%, and 20%.
    
     Associated file: marathon.cpp.

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
    
     Associated file: patrol.cpp.

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
	
	 Associated files: parrondo.cpp and parrondo1.cpp.

Chapter 15. How Long is the Wait to Get the Potato Salad? <br>

    Problem: This is a problem of queuing theory - it is measuring the times
    spent waiting and being served in a delicatessen, along with the length of
    lines and overall number of people in the deli. One or two clerks are serving
    the customers. The arrival time and service time are both exponentially
    distributed. The problem is to calculate (for one, and then two clerks) for
    an arrival rate of 30 customers per hour and a service rate of first 40
    customers per hour, then 25 customers per hour.
    
     Associated files: potato.cpp and potato1.cpp.

Chapter 16. The Appeals Court Paradox <br>

    Problem: An appeals court consists of five judges that require a majority
    vote for a decision. The five judges have the following probabilities of
    making the right decision: 0.95, 0.95, 0.9, 0.9, and 0.8. What is the probability
    that they will make an incorrect decision? Then the problem is adjusted
    by letting the worst judge let his decision be the same as the best judge.
    What is the probability of an incorrect decision now?
    
     Associated file: judges.cpp.

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
	
	 Associated files: bus.cpp and bus3.cpp.

Chapter 18. Waiting for Stoplights <br>

    Problem: Starting at a point (m+1, n+1) on two-dimensional grid (well, it is
    rectangular grid of streets in a big city), a shopper works her way back to
    point (1, 1) following certain rules: a green light always determines her
    immediate destination, either south or west towards the unltimate destination.
    However, once she reaches (1, y) or (x, 1) she always goes immediately south or
    west (so that neither coordinate goes below one) so that she is finally subject
    to the stoplights. How many stoplights does she have to wait for as function of
    where she starts? (Assume that the lights are as likely to be green as red.)
    
     Associated file: shopping_grid.cpp.

Chapter 19. Electing Emperors and Popes <br>

    Problem: This is an election problem with 3 parameters: N, n, and M.  N is the
    voting population, n is the candidate population (n <= N), and M is the threshold
    for deciding the election. Determine the probabilities of selecting a group
    leader using N=7 and N=25, for the cases n=2, 3, and 4. Use the majority for M.
    As a further twist, calculate the probabilities where one can vote for himself,
    and one is prohibited from voting for himself.
    
     Associated file: pope.cpp.

Chapter 20. An Optimal Stopping Problem <br>

    Problem: Select a partner from a pool of n candidates, dating them and then
    deciding if they are the "right" one. The rules are, that once you haved dated
    one and decided against them, then that one is not eligible again. What should
    your dating and selection stratgy be given a pool of size n? In addition, note
    that you pick randomly from the pool and that they are ranked all the way from
    the best to the worst - you find out how they rank relatively by dating them.
    In other words, you do not know if you have dated the best without dating them
    all, but you do know the relative rank of those that you have dated.
    
    Associated file: dating.cpp.

Chapter 21. Chain Reactions, Branching Processes, and Baby Boys

    Problem: This problem is relevant to the fission process whereby neutrons
    crash into the nucleus of atoms, and in splitting the atom produce a chain
    reaction of other neutrons to smash other atoms. The theoretical question was
    calculating the probability distribution of the number of neutrons produced in
    the nth generation of a chain reaction, generated from a single neutron. It turns
    out that this same question had been asked earlier with reference to male offspring -
    what is the probability that you have k males in the nth generation of descendants?
    Use the results discovered by Lotka, p(0) = 0.4825, p(i) = (0.2126)(0.5893)^(i-1) for
    i >= 1 to simulate the number of males in ith generation. Specifically, what is the
    probability for two male descendants in the second generation? Of there being six
    males in the third generation?
    
    Associated file: chain.cpp.