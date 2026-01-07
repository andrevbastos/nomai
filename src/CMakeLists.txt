# Coleta de arquivos

set(NOMAI_SOURCES
    main.cpp
)

add_executable(nomai ${NOMAI_SOURCES})

# Diretórios de Include
target_include_directories(nomai PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

# Linkagem de Dependências
target_link_libraries(nomai PRIVATE
    ftxui::screen
    ftxui::dom
    ftxui::component
    nlohmann_json::nlohmann_json
    fmt::fmt
)