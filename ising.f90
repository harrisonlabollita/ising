program main
        implicit none
        integer, parameter:: L = 10
        real, parameter :: Jint = 1.0
        integer, dimension(L, L) :: state

        state = init(L)
        print *, energy(state, Jint)

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
end program main
