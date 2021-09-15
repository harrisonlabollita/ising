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
end program main
