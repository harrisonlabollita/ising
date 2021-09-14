#include <cmath>
#include <stdlib.h> 
#include <iostream>
using namespace std;

//declare functions
void init(void *state, int L);

// run the main program
int main() {
	int L = 10;
	int state[L][L] = {0};
	init(state, L);

	for(int i=0; i<L; i++) {
		for(int j=0; j<L; j++) {
			cout << state[i][j] << ' ';
	        }
      }
      return 0;
}



// init: initialize the state as matrix of 1's and -1's
void init(int **state, int L) {
	for(int i=0; i<L; i++) {
		for(int j=0; j<L; j++) {
			state[i][j] = ((double) rand()/RAND_MAX>=0.5) ? 1 : -1;
		}
	}
}


