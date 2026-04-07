cmake_minimum_required(VERSION 3.10)
project(Doctors_and_Patients)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

set(comp
    main.c
    Doctor.c
    Patient.c
    Base.c
    str.c
    to_bin.c
)

add_executable(main ${comp})