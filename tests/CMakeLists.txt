# Descobre os testes do GTest
include(GoogleTest)

# Cria o executável de testes
add_executable(nomai_tests
    matcher_test.cpp
    frecency_test.cpp
)

# Linka com a biblioteca core e o GTest
target_link_libraries(nomai_tests PRIVATE
    nomai_core
    GTest::gtest_main
)

# Registra os testes no CTest
gtest_discover_tests(nomai_tests)