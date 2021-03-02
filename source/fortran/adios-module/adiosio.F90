module adiosio
    use adios2
    implicit none

    type(adios2_adios) :: adios2obj
    type(adios2_io) :: io_diag
    type(adios2_engine) :: engine_diag

contains

subroutine init_adiosio()
    use mpivars
    use adios2
    implicit none
    integer*4 :: err
    call adios2_init(adios2obj, app_comm, err)
    if (.not.adios2obj%valid) then
        write(*,*) "Error when creating ADIOS2 object"
    endif
end subroutine init_adiosio

subroutine finalize_adiosio()
    use adios2
    implicit none
    integer*4 :: err
    ! close the engine now if it was not closed yet
    if (engine_diag%valid) then
        call adios2_close(engine_diag, err)
    endif
    if (adios2obj%valid) then
        call adios2_finalize(adios2obj, err)
    endif
end subroutine finalize_adiosio

end module adiosio
