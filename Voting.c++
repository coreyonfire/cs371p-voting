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
#include <algorithm>

#include "Voting.h"

using namespace std;


void recount_votes(Voting_Scenario &vs, int loser) {
	for (vector<Ballot>::iterator it = vs.beginb(); it != vs.endb(); ++it) {
			if ((*it).get_vote() == loser)
				(*it).bump_vote();
		}
	
}

// ------------
// voting_eval
// ------------

string voting_eval (Voting_Scenario &vs) {
	string winner = "No Winner";
	int i, tie, loser, num_c;
	//cout << vs << endl;
	num_c = vs.num_candidates();
	vector<vector<Ballot>> tally(num_c);
	vector<int> min_count(num_c, 0);
	goto countvotes;
cleaned:
	tally.clear();
	tally.resize(num_c);
	min_count.clear();
	min_count.resize(num_c);
countvotes:
	for (vector<Ballot>::iterator it = vs.beginb(); it != vs.endb(); ++it) {
			i = (*it).get_vote() - 1;
			
			tally.at(i).push_back(*it);
			min_count.at(i)++;
			if (tally.at(i).size() > vs.num_ballots()/2) 
				return vs.get_candidate(i);
	}
	tie = 1;
	//**if i get out here, I gotta discard the lowest amount of votes.
	loser = 0;
	// find the candidate with the lowest number of votes
	for (i = 1; i < num_c; i++) {
		if (min_count.at(i) != min_count.at(loser)) {
			tie = 0;
			
			if (min_count.at(i) < min_count.at(loser)) loser = i;
		}
	}
	if (tie) {
		string winners = "";
		for (i = 0; i < num_c; i++) {
			if (min_count.at(i)) winners += vs.get_candidate(i) + "\n";
		}
		return winners;
	}
	//if all candidates have same number of votes, return all names
	recount_votes(vs, loser+1);
	goto cleaned;
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
