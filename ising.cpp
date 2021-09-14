#include <cmath>
#include <stdlib.h> 
#include <iostream>
using namespace std;




// initialize the state matrix of classical spins
void init(int L, int **state) {
	for(int i=0; i<L; i++) {
		for(int j=0; i<L; j++) {
			state[i][j] = (rand() > 0.5) ? 1 : -1;
		}
	}
} // end function init


void init(int L, int **);

// run the main program
int main() 
{
	int L = 10;
	int **state[L][L] = { {} };
	init(L, state);
	for(int i=0; i<L; i++){
		for(int j=0; j<L; j++){
			cout<<state[i][j];
		}
	cout<<endl;
	}
	return 0;
}

