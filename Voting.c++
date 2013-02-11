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
#include <sstream>

#include "Voting.h"

using namespace std;


void recount_votes(Voting_Scenario &vs, int loser) {
	for (vector<Ballot>::iterator it = vs.beginb(); it != vs.endb(); ++it) {
			(*it).bump_vote(loser);
	}
	
}

// ------------
// voting_eval
// ------------

string voting_eval (Voting_Scenario &vs) {
	int i, tie, loser, num_c;
	
	vector<vector<Ballot> > tally;
	vector<int> min_count;
countvotes:
	num_c = vs.num_candidates();
	tally.resize(num_c);
	min_count.resize(num_c);
	
	for (vector<Ballot>::iterator it = vs.beginb(); it != vs.endb(); ++it) {
			i = (*it).get_vote() - 1;
			tally.at(i).push_back(*it);
			min_count.at(i)++;
			if (tally.at(i).size() > vs.num_ballots()/2) 
				return vs.get_candidate(i) + "\n";
	}
	
	tie = 1;
	loser = min_count.at(0);
	
	for (i = 1; i < num_c; i++) {
		if (min_count.at(i) != loser) {
			tie = 0;
			if (min_count.at(i) < loser ) loser = min_count.at(i);
		}
	}
	if (tie) {
		string winners = "";
		for (i = 0; i < num_c; i++) {
			winners += vs.get_candidate(i) + "\n";
		}
		return winners;
	}
	
	for (i = 0; i < num_c;) {
		if (min_count.at(i) == loser) {
			recount_votes(vs, i+1);
			vs.remove_candidate(i);
			min_count.erase(min_count.begin()+i);
			num_c--;
		}
		else i++;
	}
	
	tally.clear();
	min_count.clear();
	goto countvotes;
}


// -------------
// voting_print
// -------------

void voting_print (std::ostream& w, string v) {
    w << v;
}


// ------------------
// valid_vote_check
// ------------------
bool valid_vote_check (Ballot &b, int j) {
	for (int i = 0; i < b.num_votes(); i++) {
			if (b.get_vote(i) == j) return false;
	}
	return true;
}

// -------------
// retrieve
// -------------

void retrieve (std::istream &r, Voting_Scenario &vs) {
	int numCandidates, i, j;
	char name[100];
	r >> numCandidates;
	if (numCandidates < 1)
		exit(-1);
	r.ignore(1, '\n');
	for (i = 0; i < numCandidates; i++) {
		try {
			r.getline(name, 100, '\n');
		} catch (...) {
			cout << "Number of candidates incorrect, skipping scenario" << endl;
			exit(-1);
		}
		vs.add_candidate(name);
	}
	
	while (1) {
		Ballot b;
		char line[41];
		bool add = 1;
		stringstream ss(stringstream::in | stringstream::out);

		if (r.peek() < '0' || r.peek() > '9') {
			break;
		}
		r.getline(line, 500, '\n');
		ss << line;
		
		for (i = 0; i < numCandidates; i++) {
			ss >> j;
			b.add_vote(j);
		}
		if (add) vs.add_ballot(b);
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
		Voting_Scenario vs;
		retrieve(r, vs);
    v = voting_eval(vs);
    voting_print(w,  v);
		if (numCases) w << endl;
	}
}
