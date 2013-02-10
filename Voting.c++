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
	//cout << "looking to bump all " << loser << "s..." <<endl;
	for (vector<Ballot>::iterator it = vs.beginb(); it != vs.endb(); ++it) {
		//if ((*it).get_vote() == loser) {
			//cout << "bumping vote" << endl;
			(*it).bump_vote(loser);
		//}
	}
	
}

void display_tally(vector<int> m, int num_c) {
	int i;
	//cout << "---------" << endl;
	for (i = 0; i < num_c; i++) {
		//cout << "Candidate " << i << " got " << m.at(i) << " votes." <<endl;
	}
	//cout << "---------" << endl;
}

// ------------
// voting_eval
// ------------

string voting_eval (Voting_Scenario &vs) {
	int i, tie, loser, num_c;
	//cout << vs << endl;
	//cout << "-------------------" << endl;
	vector<vector<Ballot> > tally;
	vector<int> min_count;
countvotes:
	num_c = vs.num_candidates();
	tally.resize(num_c);
	min_count.resize(num_c);
	//cout << "counting votes..." << endl;
	for (vector<Ballot>::iterator it = vs.beginb(); it != vs.endb(); ++it) {
			i = (*it).get_vote() - 1;
			//cout << "voting for " << vs.get_candidate(i) << " now" << endl;
			tally.at(i).push_back(*it);
			min_count.at(i)++;
			if (tally.at(i).size() > vs.num_ballots()/2) 
				return vs.get_candidate(i) + "\n";
	}
	tie = 1;
	//**if i get out here, I gotta discard the lowest amount of votes.
	loser = min_count.at(0);
	// find the candidate with the lowest number of votes
	//display_tally(min_count, num_c);
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
		//cout << "TIE" << endl;
		return winners;
	}
	
	//cout << "eliminating candidates with " << loser << " votes now..." << endl;
	//if all candidates have same number of votes, return all names
	for (i = 0; i < num_c;) {
		//cout << min_count.at(i) << " / " << loser << endl;
		if (min_count.at(i) == loser) {
			//cout << "removing " << vs.get_candidate(i) << endl;
			recount_votes(vs, i+1);
			vs.remove_candidate(i);
			min_count.erase(min_count.begin()+i);
			num_c--;
		}
		else i++;
	}
	//cout << "removing candidate now" <<endl;
	
	//cout << "candidate removed" << endl;
	
	tally.clear();
	min_count.clear();
	goto countvotes;
}


// -------------
// voting_print
// -------------

void voting_print (std::ostream& w, string v) {
    w << v << std::endl;
}


// ------------------
// valid_vote_check
// ------------------
bool valid_vote_check (Ballot &b, int j) {
	for (int i = 0; i < b.num_votes(); i++) {
			//cout << b.get_vote(i) << " : " << j << endl;
			if (b.get_vote(i) == j) return false;
	}
	//cout << "valid vote\n";
	return true;
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
	//int safety = 0;
	while (1) {
		Ballot b;
		char line[41];
		bool add = 1;
		stringstream ss(stringstream::in | stringstream::out);
		
		
		if (r.peek() < '0' || r.peek() > '9') {
			//cout << r.peek()<< endl;
			break;
		}
		//char *s;
		r.getline(line, 500, '\n');
		//cout << "ballot is: " << line << endl;
		ss << line;
		
		
		for (i = 0; i < numCandidates; i++) {
			ss >> j;
			if (valid_vote_check(b, j)) {
				b.add_vote(j);
			}	
			else {
				//add = 0;
				//cout << "invalid ballot\n";
				//break;
			}
		}
		//cout << endl;
		if (add) vs.add_ballot(b);
		//r.ignore(1, '\n');
		//cout << r.peek() << endl;
		
		//cout << "next ballot... " << endl;
	}
	//cout << "done reading ballots" << endl;
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
