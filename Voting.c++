// ----------------------------
// projects/voting/voting.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream

#include "voting.h"


/*
 * Ballot class 
 * votes - the list of votes the person has cast
 * get_vote() returns their first pick
 * bump_vote() removes their first pick
 */
class Ballot {
  vector<int> votes;
public:
	int get_vote();
	void bump_vote();
}

int Ballot::get_vote() {
	return votes.front();
}
void Ballot::bump_vote() {
	votes.erase(0);
	return;
}

/*
 * Voting Scenario class
 * candidates contains an array of all the candidates
 * ballots contains a list of the ballots cast
 * char *getCandidate() returns the candidate that corresponds to the vote cast
 * Ballot getBallot() returns the ballot at the position specified
 */

class Voting_Scenario {
	vector<string> candidates;
	vector<Ballot> ballots();
	
public: 
	Voting_Scenario(int n) {
		candidates.resize(n);
	}
}

// ------------
// voting_read
// ------------

bool voting_read (std::istream& r, int& i, int& j) {
    r >> i;
    if (!r)
        return false;
	
    r >> j;
    assert(i > 0);
    assert(j > 0);
    return true;
}

// ------------
// voting_eval
// ------------

char *voting_eval (Voting_Scenario &vs) {
	char *winner;
	//COUNT THEM VOTES
    return winner;
}

// -------------
// voting_print
// -------------

void voting_print (std::ostream& w, String v) {
    w << v << std::endl;}

// -------------
// retrieve
// -------------

void retrieve (std::isream &r, Voting_Scenario &vs) {
	int numCandidates, i, j;
	char name[81];
	r >> numCandidates;
	if (numCandidates < 1)
		return NULL;
	vs = new Voting_Scenario(numCandidates);
	r.ignore(1, '\n');
	for (; i < numCandidates; i++) {
		try {
			r.getline(name, 81, '\n');
		} catch (...) {
			cout << "Number of candidates incorrect, skipping scenario" << endl;
			return NULL;
		}
		vs.candidates.push_back(name);
	}
	
	while (1) {
		Ballot b;
		for (i = 0; i < numCandidates; i++) {
			r >> j;
			b.votes.push_back(j);
		}
		vs.ballots.push_back(b);
		r.ignore(1, '\n');
		if (r.peek() == '\n') break;
	}
	
	r.ignore(1, '\n');
	return vs;
}
	
	
// -------------
// voting_solve
// -------------

void voting_solve (std::istream& r, std::ostream& w) {
	int numCases;
	r >> numCases;
	Voting_Scenario vs;
	if (!r) {
		numCases = -1;
	}
	r.ignore(1, '\n');
    while (numCases-- < 0) {
		retrieve(r, vs);
        String v = voting_eval(vs);
        voting_print(w,  v);
	}
}
