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
		if (votes.size() == 1) return;
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



void recount_votes(Voting_Scenario &vs, int loser) {
	//cout << "looking to bump all " << loser << "s..." <<endl;
	for (vector<Ballot>::iterator it = vs.beginb(); it != vs.endb(); ++it) {
			if ((*it).get_vote() == loser) {
				//cout << "bumping vote" << endl;
				(*it).bump_vote();
			}
		}
	
}

void display_tally(vector<int> m, int num_c) {
	int i;
	cout << "---------" << endl;
	for (i = 0; i < num_c; i++) {
		cout << "Candidate " << i << " got " << m.at(i) << " votes." <<endl;
	}
	cout << "---------" << endl;
}

// ------------
// voting_eval
// ------------

string voting_eval (Voting_Scenario &vs) {
	int i, tie, loser, num_c;
	//cout << vs << endl;
	num_c = vs.num_candidates();
	vector<vector<Ballot> > tally;
	vector<int> min_count;
countvotes:
	tally.resize(num_c);
	min_count.resize(num_c);
	//cout << "counting votes..." << endl;
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
	//display_tally(min_count, num_c);
	for (i = 1; i < num_c; i++) {
		if (min_count.at(i) != min_count.at(loser)) {
			tie = 0;
			if (min_count.at(loser) == 0) {
			
				//cout << "removing zero, changing " << loser << " to " << i << endl ;
				loser = i;
			}
			else if (min_count.at(i) < min_count.at(loser) && min_count.at(i) != 0) loser = i;
		}
	}
	//cout << "eliminating " << loser << " now..." << endl;
	if (tie) {
		string winners = "";
		for (i = 0; i < num_c; i++) {
			if (min_count.at(i)) winners += vs.get_candidate(i) + "\n";
		}
		return winners;
	}
	//if all candidates have same number of votes, return all names
	recount_votes(vs, loser+1);
	
	tally.clear();
	min_count.clear();
	goto countvotes;
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
	//int safety = 0;
	while (1) {
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
		if (r.peek() < '0' || r.peek() > '9') {
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

int main () {
    using namespace std;
    voting_solve(cin, cout);
    return 0;
} //fuck your braces
