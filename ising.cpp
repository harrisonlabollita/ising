#include <cmath>
#include <vector>
#include <stdlib.h> 
#include <iostream>
using namespace std;

//declare functions
vector<vector<int>> init(int L);

// run the main program
int main() {
	int L = 10;
	vector<vector<int>> state;
	state = init(L);

	for(int i=0; i<L; i++) {
		for(int j=0; j<L; j++) {
			cout << state[i][j] << ' ';
	        }
      }
      return 0;
}



// init: initialize the state as matrix of 1's and -1's
vector<vector<int>> init(int L) {
	vector<vector<int>> state;
	state.resize(L, vector<int>(L, 0));
	for(int i=0; i<L; i++) {
		for(int j=0; j<L; j++) {
			state[i][j] = ((double) rand()/RAND_MAX>=0.5) ? 1 :-1;
		}
	}
	return state;
}
