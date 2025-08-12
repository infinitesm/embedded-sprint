cmake_minimum_required(VERSION 3.16)
project(EmbeddedSprint C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)
enable_testing()

option(ENABLE_SANITIZERS "Enable Address/UB sanitizers (gcc/clang)" ON)
option(WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

set(COMMON_WARN -Wall -Wextra -O0 -g)
if (WARNINGS_AS_ERRORS)
    list(APPEND COMMON_WARN -Werror)
endif()

set(SAN_FLAGS "")
if (ENABLE_SANITIZERS AND (CMAKE_C_COMPILER_ID MATCHES "Clang|GNU") AND (NOT WIN32))
    list(APPEND SAN_FLAGS -fsanitize=address,undefined)
endif()

# Build every day*/<file>.c as its own executable: run_<day>_<file>
function(add_day_exes DAYDIR)
    set(ABS_DAY "${CMAKE_SOURCE_DIR}/${DAYDIR}")
    if (NOT EXISTS "${ABS_DAY}")
        return()
    endif()

    file(GLOB DAY_CS CONFIGURE_DEPENDS "${ABS_DAY}/*.c")
    if (NOT DAY_CS)
        message(STATUS "Skipping ${DAYDIR}: no .c files")
        return()
    endif()

    foreach(SRC ${DAY_CS})
        get_filename_component(BASE "${SRC}" NAME_WE)   # e.g., memlab or ptrutils
        # skip hidden/backup files if any
        if (BASE MATCHES "^\\.|~$")
            continue()
        endif()

        # Executable name: run_day01_memlab
        string(REPLACE "/" "_" EXE "run_${DAYDIR}_${BASE}")

        add_executable(${EXE} "${SRC}")
        target_compile_options(${EXE} PRIVATE ${COMMON_WARN} ${SAN_FLAGS})
        target_link_options(${EXE}    PRIVATE ${SAN_FLAGS})

        # Register as a ctest (it should return 0 on success)
        add_test(NAME "${DAYDIR}:${BASE}" COMMAND ${EXE})

        message(STATUS "Added executable: ${EXE} (${SRC})")
    endforeach()
endfunction()

# Discover day folders like day01, day02, ...
file(GLOB DAY_DIRS RELATIVE "${CMAKE_SOURCE_DIR}" "day*")
list(SORT DAY_DIRS)
message(STATUS "Discovered day folders: ${DAY_DIRS}")

foreach(D ${DAY_DIRS})
    if (IS_DIRECTORY "${CMAKE_SOURCE_DIR}/${D}")
        add_day_exes(${D})
    endif()
endforeach()

# Convenience target: cmake --build build --target run_all
add_custom_target(run_all
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running all deliverable executables via ctest")
