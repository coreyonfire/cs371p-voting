#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<math.h>
#include<ctime>


//number of elections to generate
#define num_tests 1000

//if you want to use a set number of candidates with a set number of ballots,
//use the below values. 
#define num_candidates 10
#define num_ballots 500
// 0 to random values, 1 to use above values
#define set_num 0

//voila, now just compile and run that shit.
//make sure to pipe it to RunVoting.in!

using namespace std;


string  first_name[] = { 
	"Sophisticated", "Final", "Honest", "Systematic", "Loyal",
	"Mature", "Bold", "Coherent", "Protective", "Typical", 
	"Helpful", "Daunting", "Estoteric", "Problematic", 
	"Fizzy", "Outrageous", "Burgeois", "Flat", "Small",
	"Weird", "Organic", "Brave", "Giddy", "Vicious", 
	"Friendly", "Hopeful", "Advanced", "Curvy", "Zippy",
	"Private", "Bright", "Wiggly", "Daring", "Fabulous",
	"Long", "Raging", "Clever", "Dim", "Silly", "Obstinate",
	"Empathetic", "Lustful", "Greedy", "Sinful", "Wrathful",
	"Furry", "Quick", "Evolved", "Needy", "Nonsensical", "Awesome",
	"Colorful", "Stinky", "Boisterous", "Envious", "Glutonous",
	"Massive", "Sizable", "Underwhelming", "Staunch", "Prowling",
	"Pushy", "Needy", "Quizzical", "Quixotic", "Speedy", "Fake",
	"Sticky", "Immature", "Young", "Old",
};

string last_name[] = {
	"Pelican", "Hawk", "Oryx", "Goat", "Lion", "Dog",
	"Zebra", "Horse", "Cow", "Orangutan", "Llama", "Termite",
	"Hedgehog", "Mite", "Jellyfish", "Boobs", "Frog", "Snail",
	"Lark", "Pangolin", "Cat", "Squirrel", "Shrew", "Chimpanzee",
	"Chipmunk", "Downing", "Reza", "Seagull", "Shark", "Terrier",
	"Pikachu", "Wolf", "Unicorn", "Dragon", "Wyvern", "Dinosaur", 
	"Alien", "Whale", "Fish", "Monkey", "Bear", "Pegasus", 
	"Elephant", "Tiger", "Hyena", "Toaster", "Spaghetti", "Poe",
	"ReDead", "Armadillo", "Mockingbird", "Nightengale", "Dove",
	"Finch", "Kitten", "Child", "Pigeon", "Tumbleweed", "Sardine",
	"Mouse", "Rat", "Worm", "Robot", "Chicken", "Cottontail", 
	"Snake", "Deer", "Scottsman", "Ginger", "Dubstepper", 
	"Turkey", "Eagle", "Loon"
};


int main() {
	int i, j, c, b, t, x, a;

	//seed the randomizer for funniest test cases
	srand((unsigned)time(0)); 

	cout << num_tests << endl << endl;
	for (i = 0; i < num_tests; i++) {
		//generate number of candidates
		c = (set_num ? num_candidates : rand()%19+1);
		cout << c << endl;

		//generate their names
		vector<string> names;
		vector<int> votes;
		vector<int> votest;
		for (j = 0; j < c; j++) {
			names.push_back(first_name[rand()%71] + " " + last_name[rand()%73]);
			cout << names.back() << endl;
			votes.push_back(j+1);
		}
		//generate a random number of ballots
		b = (set_num ? num_ballots : rand()%999+1);
		//b = num_ballots;
		votest = votes;
		for (j = 0; j < b; j++) {
			for (a = 0; a < c; a++) {
				x = rand()%(c-a);
				t = votes.at(x);
				cout << t << " ";
				votes.erase(votes.begin()+x);
			}
			votes = votest;
			cout << endl;
		}

		cout << endl;
	}

}