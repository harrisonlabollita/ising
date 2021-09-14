#include <stdlib.h> 



// initialize the state matrix of classical spins
void init(int L) {
	int state[L][L] = {};
	for(int i=0; i<L; i++) {
		for(int j=0; i<L; j++) {
			state[i][j] = (rand() > 0.5) ? 1 : -1;
		}
	}
} // end function init


// run the main program
int main() {
	int L = 10;
	init(L);
}

