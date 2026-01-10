cmake_minimum_required(VERSION 3.20)

# Metadados do Projeto
project(nomai
    VERSION 0.1.0
    DESCRIPTION "Project & Environment Orchestrator TUI"
    LANGUAGES CXX
)

# Configurações Globais
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output de binários em pasta centralizada
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Flags de Compilação
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Gerenciamento de Dependências (Modularizado)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Dependencies)

# Inclusão dos Sources
add_subdirectory(src)

# Testes
# enable_testing()
# add_subdirectory(tests)