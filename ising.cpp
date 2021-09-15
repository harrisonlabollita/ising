#include <cmath>
#include <vector>
#include <stdlib.h> 
#include <iostream>
using namespace std;

//declare functions
vector<vector<int>> init(int L);
int neighbors(vector<vector <int>> state, int i, int j);
double energy(vector<vector<int>> state, double J);
int mc(int L, double J, double kT, int Nmc, int thermal);

// run the main program
int main() {
	int L = 10;
	double J=1.0;
	vector<vector<int>> state;
	state = init(L);
	cout << energy(state, J) << ' ';
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

//calculate the total energy of a state
double energy(vector<vector<int>> state, double J) {
	double E = 0.0;
	int L = state.size();
	for(int i=0; i<L; i++) {
		for(int j=0; j<L; j++) {
			E -= J*state[i][j]*neighbors(state, i, j);
		}
	}
	return E;
}
// the main monte carlo function 
int mc(int L, double J, double kT, int Nmc, int thermal) {
	vector<vector<int>> state;
	state = init(state);
	int L = state.size();
	double Eavg = 0.0;
	for(n=0; n<(thermal+Nmc); n++) {
		double E = energy(state, J);
		for(s=0; s<(L*L); s++) {
			int row=int ((rand()/RAND_MAX)*L);
			int col=int ((rand()/RAND_MAX)*L);
			int spin = state[row, col];
			double dE =2*J*spin*neighbors(state, row, col);
			prob=exp (-dE/kT);
			if(dE <=0 || (rand()/RAND_MAX) <= prob) {
				state[row, col] = -state[row, col];
				if(n>=thermal) {
					E += dE;
				}
			}
		}
	}
	return 0;
}




	

