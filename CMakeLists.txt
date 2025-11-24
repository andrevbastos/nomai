cmake_minimum_required(VERSION 3.14)
project(Nomai VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- DEPENDENCIES (FTXUI) ---
include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v5.0.0
)
FetchContent_MakeAvailable(ftxui)

# --- LIBRARY (CORE) ---
file(GLOB_RECURSE CORE_SOURCES 
    CONFIGURE_DEPENDS 
    "src/*.cpp"
)

add_library(nomai_core ${CORE_SOURCES})

target_include_directories(nomai_core PUBLIC include)

# --- APP EXECUTABLE ---
add_executable(nomai tests/main.cpp)

target_link_libraries(nomai PRIVATE 
    nomai_core
    ftxui::screen
    ftxui::dom
    ftxui::component
)