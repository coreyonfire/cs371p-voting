// ----------------------------
// projects/voting/Voting.c++
// Copyright (C) 2013
// cmbes
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <vector>
#include <string>

#include "Voting.h"

using namespace std;


// ------------
// voting_eval
// ------------

string voting_eval (Voting_Scenario &vs) {
	string winner = "No Winner";
	int i;
	//cout << vs << endl;
	vector<vector<Ballot>> tally(vs.num_candidates());
//countvotes:
	for (vector<Ballot>::iterator it = vs.beginb(); it != vs.endb(); ++it) {
			i = (*it).get_vote() - 1;
			tally.at(i).push_back(*it);
			if (tally.at(i).size() > vs.num_ballots()/2) 
				return vs.get_candidate(i);
	}
	//if i get out here, I gotta discard the lowest amount of votes.
//tiecheck:
	
	
    return winner;
}

// -------------
// voting_print
// -------------

void voting_print (std::ostream& w, string v) {
	//Change this to allow ties
    w << v << std::endl;
}

// -------------
// retrieve
// -------------

void retrieve (std::istream &r, Voting_Scenario &vs) {
	int numCandidates, i, j;
	char name[81];
	r >> numCandidates;
	if (numCandidates < 1)
		exit(-1);
	r.ignore(1, '\n');
	//cout << numCandidates << endl;
	for (i = 0; i < numCandidates; i++) {
		try {
			r.getline(name, 81, '\n');
			//cout << "Candidate: " << name << endl;
		} catch (...) {
			cout << "Number of candidates incorrect, skipping scenario" << endl;
			exit(-1);
		}
		vs.add_candidate(name);
	}
	int safety = 0;
	while (safety++ < 10) {
		Ballot b;
		for (i = 0; i < numCandidates; i++) {
			r >> j;
			//cout << j << " ";
			b.add_vote(j);
		}
		//cout << endl;
		vs.add_ballot(b);
		r.ignore(1, '\n');
		//cout << r.peek() << endl;
		if (r.peek() == '\n' || !r) {
			//cout << "done reading ballots" << endl;
			break;
		}
	}
	
	r.ignore(1, '\n');
	return;
}
	
	
// -------------
// voting_solve
// -------------

void voting_solve (std::istream& r, std::ostream& w) {
	int numCases;
	string v;
	r >> numCases;
	if (!r) {
		numCases = -1;
	}
	r.ignore(1, '\n');
	
    while (numCases-- > 0) {
	
		//cout << numCases << endl;
		Voting_Scenario vs;
		retrieve(r, vs);
        v = voting_eval(vs);
        voting_print(w,  v);
	}
}
