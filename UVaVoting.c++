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
		//int j;
		
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

	string candidate_string() {
		string s = "";
		for (int i = 0; (unsigned)i < candidates.size(); i++) s += candidates.at(i) + "\n";
		return s;
	}
	
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
	
	void remove_candidate(int n) {
		candidates.erase(candidates.begin()+n);
	}
	
	void add_ballot(Ballot b) {
		ballots.push_back(b);
	}
	//camron was here
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



bool is_eliminated(vector<int> not_eliminated, int i) {
	for (vector<int>::iterator it = not_eliminated.begin();
			it != not_eliminated.end(); ++it) {
			//cout << i << " : " << *it << endl;
			if (i == *it) return false;
	}
	return true;
}

// ------------
// voting_eval
// ------------

string voting_eval (Voting_Scenario &vs) {
	//cout << "starting vote count now..." << endl;
	int i, tie, loser, num_c, glenndowning = 1;
	string winners = "";
	vector<vector<Ballot> > tally;
	vector<int> min_count;
	vector<int> not_eliminated;
	vector<int> tied_for_last;
	
	//check for special case of 0 ballots
	if (vs.num_ballots() == 0) {
		//cout << "No ballots!" << endl;
		return vs.candidate_string();
	}
	
	num_c = vs.num_candidates();
	tally.resize(num_c);
	//cout << "counting votes initially" << endl;
	for (vector<Ballot>::iterator it = vs.beginb(); it != vs.endb(); ++it) {
		i = (*it).get_vote() - 1;
		//cout << "voting for " << vs.get_candidate(i);
		tally.at(i).push_back(*it);
		//cout << ", " << tally.at(i).size() << " votes" << endl;
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
		//cout << "finding the minimum..." << endl;
		for (vector<int>::iterator it = not_eliminated.begin();
			it != not_eliminated.end(); ++it) {
			i = tally.at(*it).size();
			
			//cout << i << " for " << vs.get_candidate(*it) << endl;
			//if someone's got the majority, just give it to them
			if ( (unsigned) i > vs.num_ballots()/2) 
				return vs.get_candidate(*it) + "\n";
			
			//else, if there's a TIE
			else if (i <= loser) {
				
				if (i < loser ) {
					//cout << "new minimum found" << endl;
					tie = 0;
					loser = i;
					tied_for_last.clear();
					tied_for_last.push_back(*it);
				}
				else if (i == loser) {
					//cout << "found more losers" << endl;
					tied_for_last.push_back(*it);
				}
			}
			else tie = 0;
		}
	
		//ensure that if there's a tie, it's accounted for
		//cout << "checking for tie..." << endl;
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
		
		//cout << "redistributing votes..." << endl;
		for (vector<int>::iterator it2 = tied_for_last.begin();
			it2 != tied_for_last.end(); ++it2) {
			//remove his votes
			//cout << "removing " << vs.get_candidate(*it2) << endl;
			for (vector<Ballot>::iterator it = tally.at(*it2).begin();
			it != tally.at(*it2).end(); ++it) {
			
				//cout << "hi: " << (*it).get_vote() << endl;
				do {
					//cout << "bumping vote: " << (*it) << endl;
					(*it).bump_vote();
				} while (is_eliminated(not_eliminated, (*it).get_vote()-1));
				//cout << "omg" << endl;
				//cout << "adding vote for " << vs.get_candidate((*it).get_vote()-1) << ", ";
				tally.at((*it).get_vote()-1).push_back((*it));
				//cout << tally.at((*it).get_vote()-1).size() << endl;
				if (tally.at((*it).get_vote()-1).size() == 1){
					//cout << "bumped someone up: " << vs.get_candidate((*it).get_vote()-1) << endl;
					not_eliminated.push_back((*it).get_vote()-1);
				}
			}
			tally.at(*it2).clear();
			//remove him
			//cout << "eliminating him now" << endl;
			for (vector<int>::iterator it = not_eliminated.begin();
			it != not_eliminated.end(); ++it) {
				//cout << "bye" << endl;
				if (*it == *it2) {
					//cout << "eliminating " << vs.get_candidate(*it) << endl;
					not_eliminated.erase(it);
					break;
				}
			}
		}
		tied_for_last.clear();
	} while (glenndowning);
	//cout << "tie found, returning winners." << endl;
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



int main () {
    using namespace std;
    voting_solve(cin, cout);
    return 0;
} //fuck your braces
