program main
        implicit none
        integer, parameter:: L = 10
        real, parameter :: Jint = 1.0
        real, parameter :: kT = 5.0
        integer, parameter :: Nmc = 10000
        integer, parameter :: thermal = 1000
        real :: Esim
        Esim  = mc(L, Jint, kT, Nmc, thermal)
        ! maybe should be rewritten as a subroutine?
        ! call mc(.....)

contains
        function init(L) result (state)
                implicit none
                integer :: i, j, L
                integer, dimension(L, L) :: state
                do i=1,L
                        do j=1,L
                                if (rand() > 0.5) then
                                        state(i,j) = 1
                                else
                                        state(i,j) = -1
                                end if
                        end do
                end do
        end function init

        function energy(state, Jint) result (ene)
                implicit none
                integer :: i, j, L
                integer, dimension(:, :) :: state
                real :: Jint, ene
                L = size(state, 1)
                ene = 0.0
                do i=1,L
                        do j=1,L
                                ene = ene + Jint*real(state(i,j))*real(neighbors(state, i,j))*real(neighbors(state, i,j))
                        end do
                end do
         end function energy

         function neighbors(state, i, j) result (neigh)
                 implicit none
                 integer :: L, neigh, i, j
                 integer :: ileft, iright, jup, jdn
                 integer, dimension(:, :) :: state
                 L = size(state, 1)
                 ileft = mod(i-1, L)
                 iright = mod(i+1, L)
                 if (ileft == 0) then
                         ileft = L
                 end if
                 iright = mod(i+1, L)
                 if (iright == L+1) then
                         iright = 1
                 end if
                 jup = mod(j-1, L)
                 if (jup == 0) then 
                         jup = L
                 end if
                 jdn = mod(j+1, L)
                 if (jdn == L+1) then
                         jdn = 1
                 end if
                 neigh = state(ileft, j)+state(iright, j)+state(i,jup)+state(i,jdn)
         end function neighbors

         function mc(L, Jint, kT, Nmc, thermal) result (Eavg)
                 implicit none
                 integer :: L, Nmc, thermal, size2
                 integer :: n, s, spin, row, col
                 integer, dimension(L, L) :: state
                 real :: Eavg, Jint, kT, E, dE, prob
                 print*, "Starting simulation..."
                 size2 = int(L*L)
                 state = init(L)
                 Eavg = 0.0
                 do n=1,(Nmc+thermal)
                        E = energy(state, Jint)
                        do s=1,size2
                                row = int(rand()*real(L-1)) + 1
                                col = int(rand()*real(L-1)) + 1
                                spin = state(row, col)
                                dE = 2.0*Jint*real(spin)*real(neighbors(state, row, col))
                                prob = exp(-1.0*dE/kT)
                                if(dE <= 0 .or. rand() <= prob) then
                                        state(row,col) = -1*state(row,col)
                                        if(n>=thermal) then
                                                E = E + dE
                                        end if
                                end if
                        end do
                        if (n>=thermal) then
                                Eavg = Eavg + E
                        end if
                end do
                Eavg = Eavg/real(Nmc)
                print*, "E = ", Eavg
         end function mc
end program main
