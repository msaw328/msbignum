add_executable(simple
        simple.c
        )

target_link_libraries(simple PUBLIC msbignum)

add_test(NAME cmp_simple COMMAND simple)
