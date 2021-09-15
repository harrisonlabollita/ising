program main
        implicit none
        integer, parameter:: L = 10
        integer :: i, j
        integer, dimension(L, L) :: state

        state = init(L)
        do i=1,L
                do j=1,L
                        write(*,*) state(i,j)
                end do
        end do
contains
function init(L) result (state)
        ! initialize a state
        implicit none
        integer :: i, j, L
        integer, dimension(L, L) :: state

        do i=1,L
                do j=1,L
                        if (rand() > 0.5) then
                                state(i, j) = 1
                        else
                                state(i, j) = -1
                        end if
                end do
        end do
end function init


function neighbors(state, i, j) result (neigh)
        ! calculate interaction with neighbors
        implicit none
        integer :: L, i, j, neigh
        integer, dimension(L, L) :: state
        L = size(state, 1)
        ! TODO: calculate left, right, up, down
        neigh = left+right+up+down
end function neighbors



function energy(state, J) result (E)
        ! calculate the energy of a given state
        implicit none
        integer :: L, i, j
        real :: J
        real :: E = 0.0
        integer, dimension(L, L) :: state
        L = size(state, 1)
        do i=1,L
                do j=1,L
                E -= J*state*neighbors(state, i, j)
                end do
        end do
end function energy


end program main
