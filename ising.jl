using Printf
using LinearAlgebra


abstract type Parameters end

struct params <: Parameters
    L::Integer          # system size
    J::Float            # coupling
    kT::Float           # temperature
    thermal::Integer    # thermalize
    Nmc::Integer        # no. of sweeps
end

function init!(params::Parameters)
    state = zeros(params.L, params.L)
    for i=1:params.L, j=1:params.L
            state[i][j] = (rand() > 0.5 ? 1 : -1)
    end
    state
end

function neighbors(state, i, j)
    L = size(state)[1]
    left = (i+1)%L == 0 ? state[L][j] : state[i+1][j]
    right = (i-1)%L == 0 ? state[1][j] : state[i-1][j]
    up = (j+1)%L == 0 ? state[i][1] : state[i][j+1]
    down = (j-1)%L == 0 ? state[i][L] : state[i][j-1]
    return left+right+up+down
end

function energy(params::Parameters, state::Matrix)
	E::Float64 = 0
    L = size(state)[1]
    for i=1:L, j=1:L
        E -= params.J*state[i][j]*neighbors(state, i, j)
    end
    E
end


function Magnetization(model)
    m::Float64 = 0
    N = length(model.state)
    for i in 1:N
        m += model.state[i]
    end
    return m
end


function thermalize!(model, kT)
	N = length(model.state)
	for i=1:model.parameters.thermalize
		for j=1:N
			site = convert(Int64, 1+round(rand()*(N-1), digits=0))
			ΔE = 2*model.parameters.J1*model.state[site]*sumNeighbors(model, site)
			if ΔE < 0 || rand() < exp(-ΔE/kT)
				model.state[site] *= -1
			end
		end
	end
	return model
end




function run!(model)
	N = length(model.state)
	observables = Observables(model.parameters.temps)
	Temps = LinRange(model.parameters.tmax, model.parameters.tmin, model.parameters.temps)
	totalTime = time_ns()
	for (t, T) in enumerate(Temps)
		@printf "\n %d of %d Temps | Starting MC at T = %0.5f eV\n" t length(Temps) T
		@printf "Starting thermalization...\n"
		warmTime = time_ns()
		model = thermalize!(model, T)
		@printf "Finished warm up in %.4f s\n" (time_ns() - warmTime)/1.0e9
		@printf " T        E        |Mz|        Cv        χ\n"
		etot = e2tot = mtot = m2tot = mabstot = 0.0
		for n=1:model.parameters.mccycles
			model.energy = Energy(model)
			model.magnet = Magnetization(model)
			for s=1:N
				site = convert(Int64, 1+round(rand()*(N-1), digits = 0))
				ΔE   = 2*model.parameters.J1*model.state[site]*sumNeighbors(model, site)
				if ΔE < 0 || rand() < exp(-ΔE/T)
					model.state[site] *= -1
					model.energy += ΔE
					model.magnet += 2*model.state[site]
				end
			end
			etot += model.energy/2.0
			e2tot += (model.energy/2.0)^2
			mtot += model.magnet
			m2tot += model.magnet * model.magnet
			mabstot += sqrt(model.magnet * model.magnet)
		end
        	E_avg    = etot/convert(Float64, model.parameters.mccycles*N)
        	E2_avg   = e2tot/convert(Float64, model.parameters.mccycles*N)
        	M_avg    = mtot/convert(Float64, model.parameters.mccycles*N)
        	M2_avg   = m2tot/convert(Float64, model.parameters.mccycles*N)
        	Mabs_avg = mabstot/convert(Float64, model.parameters.mccycles*N)

		observables.temperature[t] = T
		observables.energy[t] = E_avg		
		observables.magnetization[t] = Mabs_avg 		
        	observables.heatcapacity[t] = (E2_avg - E_avg*E_avg*N)/convert(Float64, T*T*model.parameters.mccycles*N)
        	observables.susceptibility[t] = (M2_avg - M_avg*M_avg*N)/convert(Float64, T*model.parameters.mccycles*N)
		@printf "\n %0.4f        %0.4f        %0.4f        %0.4f        %0.4f" T E_avg Mabs_avg observables.heatcapacity[t] observables.susceptibility[t] 	
	end
	@printf "\n Finished MC for all temperatures requested in %0.4f seconds" (time_ns() - totalTime)/1.0e9
	return model, observables
end




