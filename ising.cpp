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
	int L = 5;
	double J=1.0;
	double kT=5.0;
	int Nmc=10000;
	int thermal=10000;
	mc(L, J, kT, Nmc, thermal);
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
	// this is probably dumb but it maps to the python way
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
	cout << "Starting simulation..." << endl;
	vector<vector<int>> state;
	state = init(L);
	int size2 = int (L*L);
	double Eavg = 0.0;
	for(int n=0; n<(thermal+Nmc); n++) {
		double E = energy(state, J);
		for(int s=0; s<size2; s++) {
			int row= (int) ((rand()/RAND_MAX)*(double) L);
			int col= (int) ((rand()/RAND_MAX)*(double) L);
			int spin = state[row][col];
			double dE = 2.0 * J * (double) (spin) * (double) (neighbors(state, row, col));
			double prob = exp (-dE/kT);
			if(dE <=0 || (rand()/RAND_MAX) <= prob) {
				state[row][col] *= -1;
				if(n>=thermal) {
					E += dE;
				}//are we thermal?
			}//did we accept this move?
		}//end loop over lattice
		if(n>=thermal) {
			Eavg += E;
		}//not thermalized yet
	}//end Mc steps
	Eavg /= double (Nmc);
	cout << "E = " << Eavg << endl;
	return 0;
}//end mc




	

