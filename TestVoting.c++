// --------------------------------
// projects/voting/TestVoting.c++
// Copyright (C) 2013
// cmbes
// --------------------------------

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Voting.h"

// -----------
// TestCollatz
// -----------

struct TestVoting : CppUnit::TestFixture {

    // ----
    // eval
    // ----

		
		/**Baseline test**/
    void test_eval_1 () {
				Voting_Scenario vs;
				vs.add_candidate("John Doe");
				vs.add_candidate("Jane Smith");
				vs.add_candidate("Sirhan Sirhan");
				{
					Ballot b;
					b.add_vote(1);
					b.add_vote(2);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(2);
					b.add_vote(1);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(2);
					b.add_vote(3);
					b.add_vote(1);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(1);
					b.add_vote(2);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(3);
					b.add_vote(1);
					b.add_vote(2);
					vs.add_ballot(b);
				}
        const string v = voting_eval(vs);
        CPPUNIT_ASSERT(v == "John Doe\n");
		}

		/**All votes for 1**/
    void test_eval_2 () {
        Voting_Scenario vs;
				vs.add_candidate("John Doe");
				vs.add_candidate("Jane Smith");
				vs.add_candidate("Sirhan Sirhan");
				{
					Ballot b;
					b.add_vote(1);
					b.add_vote(2);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(1);
					b.add_vote(2);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(1);
					b.add_vote(3);
					b.add_vote(2);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(1);
					b.add_vote(2);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(1);
					b.add_vote(3);
					b.add_vote(2);
					vs.add_ballot(b);
				}
        const string v = voting_eval(vs);
        CPPUNIT_ASSERT(v == "John Doe\n");
		}

		/**All votes for 2**/
    void test_eval_3 () {
				Voting_Scenario vs;
				vs.add_candidate("John Doe");
				vs.add_candidate("Jane Smith");
				vs.add_candidate("Sirhan Sirhan");
				{
					Ballot b;
					b.add_vote(2);
					b.add_vote(1);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(2);
					b.add_vote(1);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(2);
					b.add_vote(3);
					b.add_vote(1);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(2);
					b.add_vote(1);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(2);
					b.add_vote(3);
					b.add_vote(1);
					vs.add_ballot(b);
				}
        const string v = voting_eval(vs);
        CPPUNIT_ASSERT(v == "Jane Smith\n");
		}

		/**All votes for 3**/
    void test_eval_4 () {
        Voting_Scenario vs;
				vs.add_candidate("John Doe");
				vs.add_candidate("Jane Smith");
				vs.add_candidate("Sirhan Sirhan");
				{
					Ballot b;
					b.add_vote(3);
					b.add_vote(2);
					b.add_vote(1);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(3);
					b.add_vote(2);
					b.add_vote(1);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(3);
					b.add_vote(1);
					b.add_vote(2);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(3);
					b.add_vote(2);
					b.add_vote(1);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(3);
					b.add_vote(1);
					b.add_vote(2);
					vs.add_ballot(b);
				}
        const string v = voting_eval(vs);
        CPPUNIT_ASSERT(v == "Sirhan Sirhan\n");
		}
		
		/**3 Way Tie**/
    void test_eval_5 () {
        Voting_Scenario vs;
				vs.add_candidate("John Doe");
				vs.add_candidate("Jane Smith");
				vs.add_candidate("Sirhan Sirhan");
				{
					Ballot b;
					b.add_vote(1);
					b.add_vote(2);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(2);
					b.add_vote(1);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(2);
					b.add_vote(3);
					b.add_vote(1);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(1);
					b.add_vote(2);
					b.add_vote(3);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(3);
					b.add_vote(1);
					b.add_vote(2);
					vs.add_ballot(b);
				}
				{
					Ballot b;
					b.add_vote(3);
					b.add_vote(1);
					b.add_vote(2);
					vs.add_ballot(b);
				}
        const string v = voting_eval(vs);
        CPPUNIT_ASSERT(v == "John Doe\nJane Smith\nSirhan Sirhan\n");
		}
		
		
		/**Tie to be eliminated**/
    void test_eval_6 () {
        Voting_Scenario vs;
				stringstream ss(stringstream::in | stringstream::out);
				ss << "14\nA\nB\nC\nD\nE\nF\nG\nH\nI\nJ\nK\nL\nM\nN\n12 5 11 8 6 13 3 2 10 1 7 9 14 4\n8 14 1 13 11 12 5 4 3 10 2 6 7 9\n13 12 14 5 7 11 3 10 2 1 9 8 4 6\n12 3 7 11 2 10 13 5 9 1 6 14 8 4\n11 14 13 1 7 4 2 12 5 3 8 10 9 6\n4 3 12 8 5 1 2 7 13 11 10 14 6 9\n6 14 3 11 1 5 10 7 13 2 12 4 8 9\n";
				retrieve(ss, vs);
        //cout << vs;
				const string v = voting_eval(vs);
        CPPUNIT_ASSERT(v == "L\n");
		}
		

    // -----
    // print
    // -----

    void test_print () {
        std::ostringstream w;
        voting_print(w, "winner");
        CPPUNIT_ASSERT(w.str() == "winner\n");
		}

    // -----
    // solve
    // -----

    void test_solve () {
        std::istringstream r("1\n\n14\nA\nB\nC\nD\nE\nF\nG\nH\nI\nJ\nK\nL\nM\nN\n12 5 11 8 6 13 3 2 10 1 7 9 14 4\n8 14 1 13 11 12 5 4 3 10 2 6 7 9\n13 12 14 5 7 11 3 10 2 1 9 8 4 6\n12 3 7 11 2 10 13 5 9 1 6 14 8 4\n11 14 13 1 7 4 2 12 5 3 8 10 9 6\n4 3 12 8 5 1 2 7 13 11 10 14 6 9\n6 14 3 11 1 5 10 7 13 2 12 4 8 9\n");
        std::ostringstream w;
        voting_solve(r, w);
        CPPUNIT_ASSERT(w.str() == "L\n\n");
		}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestVoting);
    CPPUNIT_TEST(test_eval_1);
    CPPUNIT_TEST(test_eval_2);
    CPPUNIT_TEST(test_eval_3);
    CPPUNIT_TEST(test_eval_4);
    CPPUNIT_TEST(test_eval_5);
    CPPUNIT_TEST(test_eval_6);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_solve);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestVoting.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestVoting::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}