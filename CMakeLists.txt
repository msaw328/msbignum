cmake_minimum_required(VERSION 2.8.0)
project("ms-bignum" LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -Wextra")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DBIGNUM_DEBUG")

add_library(msbignum SHARED
        src/base.c
        src/mem.c
        src/arithmetic.c
        src/chunkops.c
        )

target_include_directories(msbignum PUBLIC include)

enable_testing()
add_subdirectory(tests)

# TODO:once examples are added, uncomment the line
# add_subdirectory(examples EXCLUDE_FROM_ALL)
