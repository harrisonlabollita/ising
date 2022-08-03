let L			= 16;
let kT			= 0.1;
let J			= 1.0;
let thermal 	= 100;
let Nmc  		= 100;

const SCALE     = 10;
const canvas = document.getElementById("app");
canvas.width =  L*SCALE;
canvas.height =  L*SCALE;
const ctx    = canvas.getContext('2d');

function Spin(x, y, width, height, color) {
	this.x = x
	this.y = y
	this.width=width
	this.height=height
	this.color = color
	this.draw = function() {
		ctx.fillStyle = this.color
		ctx.fillRect(this.x, this.y, this.width, this.height)
	}
}

function drawIsingState(state){
	for (let i = 0; i < canvas.width; i+=SCALE) {
		for (let j = 0; j < canvas.height; j+=SCALE) {
			if (state[i/SCALE][j/SCALE] > 0) {
				color = 'rgba(0,255,255)';
			} else {
				color = 'rgba(255,105,180)';
			}
			let spin = new Spin(i,j,SCALE,SCALE,color);
			spin.draw();
		}
	}
}

class Ising {
	constructor(L, kT, J, thermal, Nmc) {
		this.L = L;
		this.kT = kT;
		this.J = J;
		this.thermal = thermal;
		this.Nmc = Nmc;
		this.state = new Array(this.L).fill(0).map(x => Array(this.L).fill(0));
		this.InitializeState();
	}

	InitializeState() {
		for(let i=0; i<this.L; i++) {
			for(let j=0; j<this.L; j++) {
				this.state[i][j] = Math.random() > 0.5 ? 1 : -1;
			}
		}
	}

	SumNeighbors(i, j) {
		let left_idx  = i-1  > 0 ? i-1 : L-1;
		let right_idx = i+1  < L ? i+1 : 0;
		let up_idx    = j-1  > 0 ? j-1 : L-1;
		let down_idx  = j+1  < L ? j+1 : 0;
		let left = this.state[left_idx][j];
		let right = this.state[right_idx][j];
		let up = this.state[i][up_idx];
		let down = this.state[i][down_idx];
		return left + right + up + down;
	}
}

function SimulateIsing() {
	for (let n=0; n<model.Nmc; n++) {
		for (let s=0; s < model.L*model.L; s++) {
			var row = Math.round(Math.random() * (model.L-1));
			var col = Math.round(Math.random() * (model.L-1));
			var spin = model.state[row][col];
			var dE = 2*model.J*model.SumNeighbors(row,col);
			var prob = Math.exp(-dE/model.kT);
			if (dE <= 0 || Math.random() <= prob) {
				model.state[row][col] = -1*model.state[row][col];
				}
		drawIsingState(model.state);
		window.requestAnimationFrame(SimulateIsing);
		}
	}
}



let model = new Ising(L, kT, J, thermal, Nmc);

function init() {
	window.requestAnimationFrame(SimulateIsing);
}

init()
