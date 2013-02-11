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



//return true if the specified number is not in the election any more
bool is_eliminated(vector<int> not_eliminated, int i) {
	assert(i >= 0);
	for (vector<int>::iterator it = not_eliminated.begin();
			it != not_eliminated.end(); ++it) {
			if (i == *it) return false;
	}
	return true;
}

// ------------
// voting_eval
// ------------

string voting_eval (Voting_Scenario &vs) {
	assert(vs.num_candidates() != 0);
	int i, tie, loser, num_c, glenndowning = 1;
	string winners = "";
	vector<vector<Ballot> > tally;
	vector<int> min_count;
	vector<int> not_eliminated;
	vector<int> tied_for_last;
	
	//check for special case of 0 ballots
	if (vs.num_ballots() == 0) {
		return vs.candidate_string();
	}
	
	num_c = vs.num_candidates();
	tally.resize(num_c);
	
	//do initial tally of votes
	for (vector<Ballot>::iterator it = vs.beginb(); it != vs.endb(); ++it) {
		i = (*it).get_vote() - 1;
		tally.at(i).push_back(*it);
		if (tally.at(i).size() == 1) {
			not_eliminated.push_back(i);
		}
		if (tally.at(i).size() > vs.num_ballots()/2) 
			return vs.get_candidate(i) + "\n";
	}
	
	do {
		tie = 1;
		
		loser = tally.at(not_eliminated.front()).size();
		
		//FIND THE MINIMUM AND WHO ALL IS AT IT
		for (vector<int>::iterator it = not_eliminated.begin();
			it != not_eliminated.end(); ++it) {
			i = tally.at(*it).size();
			
			//if someone's got the majority, just give it to them
			if ( (unsigned) i > vs.num_ballots()/2) 
				return vs.get_candidate(*it) + "\n";
			
			//else, if there's a TIE
			else if (i <= loser) {
				
				if (i < loser ) {
					tie = 0;
					loser = i;
					tied_for_last.clear();
					tied_for_last.push_back(*it);
				}
				else if (i == loser) {
					tied_for_last.push_back(*it);
				}
			}
			else tie = 0;
		}
	
		//ensure that if there's a tie, it's accounted for
		if (tie) {
			for (int i = 0; i < num_c; i++) {
				if (!is_eliminated(not_eliminated, i)) winners += vs.get_candidate(i) + "\n";
			}
			break;
		}
		
		//now i've got a vector full of ballots that need to be recast
		//so bump them and push them where they go
		//GO THROUGH THE LOSERS, REDISTRIBUTING THEIR VOTES
		//AND ADD THEM TO ELIMINATED
		for (vector<int>::iterator it2 = tied_for_last.begin();
			it2 != tied_for_last.end(); ++it2) {
			//remove his votes
			for (vector<Ballot>::iterator it = tally.at(*it2).begin();
			it != tally.at(*it2).end(); ++it) {
			
				do {
					(*it).bump_vote();
				} while (is_eliminated(not_eliminated, (*it).get_vote()-1));
				tally.at((*it).get_vote()-1).push_back((*it));
				if (tally.at((*it).get_vote()-1).size() == 1){
					not_eliminated.push_back((*it).get_vote()-1);
				}
			}
			tally.at(*it2).clear();
			//remove him
			for (vector<int>::iterator it = not_eliminated.begin();
			it != not_eliminated.end(); ++it) {
				if (*it == *it2) {
					not_eliminated.erase(it);
					break;
				}
			}
		}
		tied_for_last.clear();
	} while (glenndowning);
	return winners;
}


// -------------
// voting_print
// -------------

void voting_print (std::ostream& w, string v) {
    w << v;
}

// -------------
// retrieve
// -------------

void retrieve (std::istream &r, Voting_Scenario &vs) {
	int numCandidates, i, j;
	char name[100];
	r >> numCandidates;
	assert(numCandidates > 0);
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
	assert(numCases > 0);
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
	assert (numCases < 0);
}
