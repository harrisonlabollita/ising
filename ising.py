#!/usr/bin/env python
"""
Two-dimensional Ising model on a square lattice in python.
"""
import sys
import numpy as np
from datetime import datetime


class ising:
    def __init__(self, L, kT, J, thermal, Nmc):
        self.L = L
        self.kT = kT
        self.J = J
        self.thermal = thermal
        self.Nmc = Nmc

    def init(self):
        state = np.zeros((self.L, self.L))
        for i in range(self.L):
            for j in range(self.L):
                if np.random.rand() > 0.5:
                    state[i][j] = 1
                else:
                    state[i][j] = -1
        return state

    def neighbors(self, i, j):
        left = self.state[(i-1)%self.L][j]
        right = self.state[(i+1)%self.L][j]
        up = self.state[i][(j-1)%self.L]
        down = self.state[i][(j+1)%self.L]
        return left+right+up+down

    def magnetization(self):
        return np.mean(self.state)

    def energy(self):
        E = 0
        for i in range(len(self.state)):
            for j in range(len(self.state)):
                E -= J*self.state[i][j]*self.neighbors(i, j)
        return E

    def mc(self):
        self.state = self.init() 
        Eavg = E2avg = M = Mavg = 0
        for n in range(self.thermal + self.Nmc):
            E = self.energy()
            M = self.magnetization()
            for s in range(self.L**2):
                row = int(np.random.random()*self.L)
                col = int(np.random.random()*self.L)
                spin = self.state[row, col]
                dE = 2*J*spin*self.neighbors(row, col)
                prob = np.exp(-dE/self.kT)
                if dE <= 0 or np.random.random() <= prob:
                    self.state[row, col] = -1*self.state[row, col]
                    if n >= self.thermal:
                        E += dE
                        M += 2*self.state[row, col]

            if n >= self.thermal:
                Eavg += E
                E2avg += E**2
                Mavg += M

        Eavg /= float(self.Nmc)
        E2avg /= float(self.Nmc)

        Evar = (E2avg - Eavg*E_avg)/float(self.L*self.L*sefl.kT*self.kT)
        Mavg /= float(self.Nmc*self.L*self.L)
        Eavg /= float(self.L*self.L)
        return Eavg, Evar, Mavg


if __name__ == "__main__":
    # default params
    L = 10
    kT = 4.0
    J = 1.0
    thermal = 10000
    Nmc = 100000
    help = """2d ising model on a square lattice. Command line arguments are:
            -------------------------------------------
             Variable         |   Default  |     Tag 
             -------------------------------------------
             L (system size)  |   10       |     -L
             kT (temperature) |   4.0      |     -kT
             J  (coupling)    |   1.0      |     -J
             thermal (warmup) |   10000    |     -thermal
             Nmc (no. sweeps) |  100000    |     -Nmc
             -------------------------------------------"""
    for arg in range(1, len(sys.argv)):
        if sys.argv[arg] == "-L":
            L = sys.argv[arg+1]
        elif sys.argv[arg] == "-kT":
            kT = sys.argv[arg+1]
        elif sys.argv[arg] == "-J":
            J = sys.argv[arg+1]
        elif sys.argv[arg] == "-thermal":
            thermal = sys.argv[arg+1]
        elif sys.argv[arg] == "-Nmc":
            Nmc = sys.argv[arg+1]
        elif sys.argv[arg] == "-h":
            print(help)
            sys.exit(0)
    model = ising(L, kT, J, thermal, Nmc)
    print("running 2d ising model at {}...".format(str(datetime.now())))
    model.mc()
