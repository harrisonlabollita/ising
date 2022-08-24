package main


import (
    "math/rand"
    "math"
)

type State struct {
    J float64
    size int
    state [128][128]int
}


func (state *State) init() {
    for i := 0; i < state.size; i++ {
        for j := 0; j < state.size; j++ {
            var r float64 = rand.Float64()
            if r > 0.5 {
                state.state[i][j] = 1.0;
            } else {
                state.state[i][j] = -1.0;
            }
        }
    }
}

func (state *State) neighbors(i int, j int) float64 {
    var left,right,up,down int
    left = (i-1) % state.size
    if left < 0 {
        left = state.size - 1;
    }
    right = (i+1) % state.size
    if right > state.size -1 {
        right = 0;
    }
    up = (j-1) % state.size
    if up < 0 {
        up = state.size - 1;
    }
    
    down= (j+1) % state.size
    if down > state.size -1 {
        down = 0;
    }
    return float64(left+right+up+down);
}


func simulate(state State, kT float64){
    state.init();
    for n := 0; n < 100000000; n++ {
        for s := 0; s < state.size*state.size; s++{
            row := int(math.Round(rand.Float64()*float64(state.size-1)));
            col := int(math.Round(rand.Float64()*float64(state.size-1)));
            var spin float64 = float64(state.state[row][col]);
            var dE float64 = 2.0*state.J*spin*state.neighbors(row,col);
            var prob float64 = math.Exp(-dE/kT)
            if (dE <= 0) || (rand.Float64() <= prob) {
                state.state[row][col] = -1*state.state[row][col];
            }
        }
    }
}


func main(){
    var ising State = State{};
    ising.size = 128; // dumb for now
    ising.J = 1.0;
    simulate(ising, 1.0);
}
