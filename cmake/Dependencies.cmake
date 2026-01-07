include(FetchContent)

# --- FTXUI ---
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG        v5.0.0 # Sempre pinne versões para estabilidade
)
FetchContent_MakeAvailable(ftxui)

# --- Nlohmann JSON ---
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json
  GIT_TAG        v3.11.3
)
FetchContent_MakeAvailable(json)

# --- FMT ---
FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        10.2.1
)
FetchContent_MakeAvailable(fmt)