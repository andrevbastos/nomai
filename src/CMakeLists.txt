# Coleta todos os sources, EXCETO o main.cpp
file(GLOB_RECURSE NOMAI_LIB_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/core/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tui/*.cpp" 
)

# Cria uma biblioteca estática com a lógica do Nomai
add_library(nomai_core STATIC ${NOMAI_LIB_SOURCES})

target_include_directories(nomai_core PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(nomai_core PUBLIC
    ftxui::screen
    ftxui::dom
    ftxui::component
    nlohmann_json::nlohmann_json
    fmt::fmt
)

# O Executável final apenas linka com o core e adiciona o main.cpp
add_executable(nomai main.cpp)
target_link_libraries(nomai PRIVATE nomai_core)