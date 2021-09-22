#include <cmath>
#include <vector>
#include <stdlib.h> 
#include <iostream>
using namespace std;

//declare functions
vector<vector<int>> init(int L);
int neighbors(vector<vector <int>> state, int i, int j);
double energy(vector<vector<int>> state, double J);
double magnet(vector<vector<int>> state);
vector<vector<int>> thermalize(vector<vector<int>> state, double J, int thermal);
int mc(int L, double J, double kT, int Nmc, int thermal);

// run the main program
int main() {
	static const int L = 8;
	static const double J=1.0;
	static const double kT=5.0;
	static const int Nmc=1000000;
	static const int thermal=100000;
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
	const int L = state.size();
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
	const int L = state.size();
	for(int i=0; i<L; i++) {
		for(int j=0; j<L; j++) {
			E -= J*state[i][j]*neighbors(state, i, j);
		}
	}
	return E;
}

double magnet(vector<vector<int>> state) {
	double M = 0.0;
	int L = state.size();
	for(int i=0; i<L; i++){
		for(int j=0; j<L; j++){
			M += state[i][j];
		}
	}
	M /= L;
	return M;
}


vector<vector<int>> thermalize(vector<vector<int>> state, double J, double kT, int thermal){
	cout << "thermalizing..." << endl;
	const int L = state.size();
	const int size2 = int (L*L);
	for(int n=0; n<thermal; n++) {
		for(int s=0; s<size2; s++) {
			int row= (int) ((rand()/RAND_MAX)*(double) L);
			int col= (int) ((rand()/RAND_MAX)*(double) L);
			int spin = state[row][col];
			double dE = 2.0 * J * (double) (spin) * (double) (neighbors(state, row, col));
			double prob = exp (-dE/kT);
			if(dE <=0 || (rand()/RAND_MAX) <= prob) {
				state[row][col] *= -1;
			}//did we accept this move?
		}//end loop over lattice
	}//end thermalization
	cout << "finished thermalization..." << endl;
	return state;
}


// the main monte carlo function 
int mc(const int L, const double J, const double kT, const int Nmc, const int thermal) {
	cout << "Starting simulation..." << endl;
	vector<vector<int>> state;
	state = init(L);
	state = thermalize(state, J, kT, thermal);
	const int size2 = int (L*L);
	double Eavg = 0.0;
	double Mavg = 0.0;
	for(int n=0; n<Nmc; n++) {
		double E = energy(state, J);
		double M = magnet(state);
		for(int s=0; s<size2; s++) {
			int row= (int) ((rand()/RAND_MAX)*(double) L);
			int col= (int) ((rand()/RAND_MAX)*(double) L);
			int spin = state[row][col];
			double dE = 2.0 * J * (double) (spin) * (double) (neighbors(state, row, col));
			double prob = exp (-dE/kT);
			if(dE <=0 || (rand()/RAND_MAX) <= prob) {
				state[row][col] *= -1;
				E += dE;
				M += 2*state[row][col];
			}//did we accept this move?
		}//end loop over lattice
		Eavg += E;
		Mavg += M;
	}//end Mc steps
	Eavg /= (double (Nmc) * double (L) * double(L));
	Mavg /= (double (Nmc) * double (L) * double(L));

	cout << "E = " << Eavg << endl;
	cout << "M = " << Mavg << endl;
	return 0;
}//end mc




	

