// --------------------------
// projects/voting/Voting.h
// Copyright (C) 2013
// cmbes
// --------------------------

#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <vector>
#include <string>

using namespace std;

// --------------
// custom classes
// --------------

/**
 * Ballot class 
 * votes - the list of votes the person has cast
 * get_vote() returns their first pick
 * bump_vote() removes their first pick
 */
class Ballot {
	vector<int> votes;
public:
	int add_vote(int n) {
		votes.push_back(n);
		return n;
	}
	int get_vote() {
		return votes.front();
	}
	void bump_vote() {
		votes.erase(votes.begin());
		return;
	}
	int num_votes() {
		return votes.size();
	}
	int get_vote(int n) {
		return votes.at(n);
	}
	friend ostream& operator<<(ostream& output, Ballot &b) {
		for (int i = 0; i < b.num_votes(); i++) {
			output << b.get_vote(i) << " ";
		}
		return output;
	}
};

/**
 * Voting Scenario class
 * candidates contains an array of all the candidates
 * ballots contains a list of the ballots cast
 * char *getCandidate() returns the candidate that corresponds to the vote cast
 * Ballot getBallot() returns the ballot at the position specified
 */
class Voting_Scenario {
	vector<string> candidates;
	vector<Ballot> ballots;
public: 
	
	void add_candidate(string name) {
		candidates.push_back(name);
	}
	
	unsigned num_candidates() {
		return candidates.size();
	}
	
	unsigned num_ballots() {
		return ballots.size();
	}
	
	string get_candidate(int n) {
		return candidates.at(n);
	}
	
	void add_ballot(Ballot b) {
		ballots.push_back(b);
	}
	
	Ballot get_ballot(int n) {
		return ballots.at(n);
	}
	
	vector<string>::iterator beginc() {
		return candidates.begin();
	}
	
	vector<Ballot>::iterator beginb() {
		return ballots.begin();
	}
	
	vector<string>::iterator endc() {
		return candidates.end();
	}
	
	vector<Ballot>::iterator endb() {
		return ballots.end();
	}
	
	friend ostream& operator<<(ostream& output, Voting_Scenario& vs) {
		output << "-Candidates (" << vs.num_candidates() << "):" << endl;
		for (vector<string>::iterator it = vs.beginc(); it != vs.endc(); ++it) {
			output << *it << endl;
		}
		output << "-Ballots (" << vs.num_ballots() << "):" << endl;
		for (vector<Ballot>::iterator it = vs.beginb(); it != vs.endb(); ++it) {
			output << *it << endl;
		}
		return output;
		
	}
};



// ------------
// voting_eval
// ------------

/**
 * @param vs The voting scenario being counted
 * @return the name(s) of the winner(s)
 */
string voting_eval (Voting_Scenario &vs);

// -------------
// voting_print
// -------------

/**
 * prints the values of i, j, and v
 * @param w a std::ostream
 * @param v the names of the winners
 */
void voting_print (std::ostream& w, string v);

// -------------
// retrieve
// -------------

/**
 * parses text into Voting_Scenarios
 * @param r a std::istream
 * @param vs a Voting_Scenario to parse into
 */
void retrieve (std::istream &r, Voting_Scenario &vs);

// -------------
// voting_solve
// -------------

/**
 * read, eval, print loop
 * @param r a std::istream
 * @param w a std::ostream
 */
void voting_solve (std::istream& r, std::ostream& w);

#endif // Voting_h