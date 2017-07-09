/**
 * \file judges.cpp
 *
 */

#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
//#include <functional>

/*--------------------------------------------------------------------------*/

class Judge
{
    int id;
    double prob_decision_correct;
    double decision_this_case;
public:
    Judge(int i_id, double i_prob_decision_correct) : id(i_id), prob_decision_correct(i_prob_decision_correct) {}
    bool decision_judgement(double i_decision_this_case) { return i_decision_this_case < prob_decision_correct; }
    void set_decision_same(Judge& judge_to_copy)
        {
            prob_decision_correct = judge_to_copy.prob_decision_correct;
            decision_this_case = judge_to_copy.decision_this_case;
        }
};

/*--------------------------------------------------------------------------*/

class Decision
{
    bool verdict_correct;
public:
    Decision(bool i_verdict_correct) : verdict_correct(i_verdict_correct) {}
    auto get_verdict_correct() -> bool { return verdict_correct; }
    void set_verdict_correct(Decision& d) { verdict_correct = d.verdict_correct; }
};

/*--------------------------------------------------------------------------*/

int main(int argn, char* argv[])
{
    std::vector<Judge> judges { Judge(1, 0.95), Judge(2, 0.95), Judge(3, 0.9), Judge(4, 0.9), Judge(5, 0.8) };

    std::default_random_engine dre;
    std::uniform_real_distribution<double> case_decision(0,1);
    dre.seed(1);

    const int nr_trials = 10'000'000;

    double nr_incorrect_decisions = 0;
    double nr_all_correct = 0;
    double nr_incorrect_decisions_dup_judge = 0;

    for ( int ix=0; ix<nr_trials; ++ix )
    {
        long nr_correct_decisions = 0;

        std::vector<Decision> verdict_correct_by_judge;
        for ( Judge judge : judges )
            {
                verdict_correct_by_judge.push_back(judge.decision_judgement(case_decision(dre)));
            }
//        auto ruling = std::mem_fun(&Decision::get_verdict_correct);
        nr_correct_decisions = std::count_if(verdict_correct_by_judge.begin(), verdict_correct_by_judge.end(),
                                [](Decision& d) -> bool { return d.get_verdict_correct(); });

        verdict_correct_by_judge[4].set_verdict_correct(verdict_correct_by_judge[0]);
        long nr_correct_decisions_dup_judge = std::count_if(verdict_correct_by_judge.begin(),
                                                verdict_correct_by_judge.end(),
                                                [](Decision& d) -> bool { return d.get_verdict_correct(); });

        if ( nr_correct_decisions < 3 ) { nr_incorrect_decisions += 1.0; }

        if ( nr_correct_decisions == 5 ) { nr_all_correct += 1.0; }

        if ( nr_correct_decisions_dup_judge < 3 ) { nr_incorrect_decisions_dup_judge += 1.0; }

//        std::cout << "nr_correct_verdicts = " << nr_correct_decisions << '\n';
    }
 //       std::bind(ruling, std::placeholders::_1));
    std::cout << "probability of incorrect decision = "
        << nr_incorrect_decisions/static_cast<double>(nr_trials) << '\n';

    std::cout << "probability of all correct ="
        << nr_all_correct/static_cast<double>(nr_trials) << '\n';

    std::cout << "probability of incorrect decision when last judge follows first = "
        << nr_incorrect_decisions_dup_judge/static_cast<double>(nr_trials) << '\n';

}
