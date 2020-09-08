add_executable(mul_overflow
        mul_overflow.c
        )

target_link_libraries(mul_overflow PUBLIC msbignum)

add_test(NAME arithmetic_mul_overflow COMMAND mul_overflow)

add_executable(add_overflow
        add_overflow.c
        )

target_link_libraries(add_overflow PUBLIC msbignum)

add_test(NAME arithmetic_add_overflow COMMAND add_overflow)
