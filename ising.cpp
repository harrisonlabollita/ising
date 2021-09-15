#include <cmath>
#include <vector>
#include <stdlib.h> 
#include <iostream>
using namespace std;

//declare functions
vector<vector<int>> init(int L);
int neighbors(vector<vector <int>> state, int i, int j);

// run the main program
int main() {
	int L = 10;
	vector<vector<int>> state;
	state = init(L);
	cout << neighbors(state, 0, 0) << ' ';
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

// neighbors: calculate interaction with neighboring spins
int neighbors(vector<vector<int>> state, int i, int j) {
	int L = state.size();
	// this is probably dumb
	int left = state[(L+(i-1))%L][j]; 	// left neighbor
	int right = state[(L+(i+1))%L][j];     // right neighbor
	int up = state[i][(L+(j-1))%L]; 	// up neighbor
	int down = state[j][(L+(j+1))%L];     // down neighbor
	return left+right+up+down;
}

