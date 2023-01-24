cmake_minimum_required(VERSION 3.25)
project(spicygoat)
set(CMAKE_CXX_STANDARD 20)


include(FetchContent)

set(ZLIB_COMPAT ON)
FetchContent_Declare(zlib
        GIT_REPOSITORY https://github.com/zlib-ng/zlib-ng
        GIT_TAG b56a2fd0b126cfe5f13e68ab9090cd4f6a773286 # 2.0.6
        OVERRIDE_FIND_PACKAGE)
FetchContent_MakeAvailable(zlib)

FetchContent_Declare(json
        URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(toml11
        GIT_REPOSITORY https://github.com/ToruNiina/toml11
        GIT_TAG dcfe39a783a94e8d52c885e5883a6fbb21529019) # v3.7.1
FetchContent_MakeAvailable(toml11)

FetchContent_Declare(uuid
        GIT_REPOSITORY https://github.com/mariusbancila/stduuid
        GIT_TAG 3afe7193facd5d674de709fccc44d5055e144d7a)
FetchContent_MakeAvailable(uuid)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(NBT_BUILD_TESTS OFF)
FetchContent_Declare(nbt++
        GIT_REPOSITORY https://github.com/ljfa-ag/libnbtplusplus
        GIT_TAG c7cb857c2fe0a066011cf7d2a8f82eb025d86fec) # v2.5
FetchContent_MakeAvailable(nbt++)

set(ABSL_PROPAGATE_CXX_STD ON)
FetchContent_Declare(abseil
        GIT_REPOSITORY https://github.com/abseil/abseil-cpp
        GIT_TAG 8c0b94e793a66495e0b1f34a5eb26bd7dc672db0) # 20220623.1
FetchContent_MakeAvailable(abseil)

FetchContent_Declare(embed
        GIT_REPOSITORY https://github.com/MiSo1289/cmake-embed
        GIT_TAG 20273c330d8e727cfc587002c451ec368c4cfef3)
FetchContent_MakeAvailable(embed)

FetchContent_Declare(spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG ad0e89cbfb4d0c1ce4d097e134eb7be67baebb36) # v1.11.0
FetchContent_MakeAvailable(spdlog)

set(CLI11_PRECOMPILED ON)
set(CLI11_SINGLE_FILE OFF)
FetchContent_Declare(cli11
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11
        GIT_TAG 291c58789c031208f08f4f261a858b5b7083e8e2) # v2.3.2
FetchContent_MakeAvailable(cli11)


add_executable(spicygoat)
add_subdirectory(data)
add_subdirectory(src)
add_embedded_binary_resources(
        spicygoat_resources
        OUT_DIR resources_out
        HEADER resources.h
        NAMESPACE Resources
        RESOURCE_NAMES codec
        RESOURCES
        "${PROJECT_SOURCE_DIR}/resources/codec.dat"
)
target_link_libraries(spicygoat PUBLIC nlohmann_json::nlohmann_json pthread nbt++ toml11 zlibstatic stduuid absl::strings spdlog::spdlog CLI11::CLI11)
target_link_libraries(spicygoat PRIVATE spicygoat_resources -static)
if(WIN32)
    target_link_libraries(spicygoat PRIVATE wsock32 ws2_32)
endif()
