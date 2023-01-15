cmake_minimum_required(VERSION 3.13)
project(SpicyGoat)
set(CMAKE_CXX_STANDARD 20)


include(FetchContent)

set(ZLIB_COMPAT ON)
FetchContent_Declare(zlib
        GIT_REPOSITORY https://github.com/zlib-ng/zlib-ng
        GIT_TAG 2.0.6
        OVERRIDE_FIND_PACKAGE)
FetchContent_MakeAvailable(zlib)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG v3.11.2)
FetchContent_MakeAvailable(json)

FetchContent_Declare(toml11
        GIT_REPOSITORY https://github.com/ToruNiina/toml11
        GIT_TAG v3.7.1)
FetchContent_MakeAvailable(toml11)

FetchContent_Declare(uuid
        GIT_REPOSITORY https://github.com/mariusbancila/stduuid
        GIT_TAG 3afe7193facd5d674de709fccc44d5055e144d7a)
FetchContent_MakeAvailable(uuid)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(NBT_BUILD_TESTS OFF)
FetchContent_Declare(nbt++
        GIT_REPOSITORY https://github.com/ljfa-ag/libnbtplusplus
        GIT_TAG v2.5)
FetchContent_MakeAvailable(nbt++)

set(ABSL_PROPAGATE_CXX_STD ON)
FetchContent_Declare(abseil
        GIT_REPOSITORY https://github.com/abseil/abseil-cpp
        GIT_TAG 20220623.1)
FetchContent_MakeAvailable(abseil)

FetchContent_Declare(embed
        GIT_REPOSITORY https://github.com/MiSo1289/cmake-embed
        GIT_TAG 20273c330d8e727cfc587002c451ec368c4cfef3)
FetchContent_MakeAvailable(embed)


add_executable(SpicyGoat)
add_subdirectory(data)
add_subdirectory(src)
add_embedded_binary_resources(
        SpicyGoat_resources
        OUT_DIR resources_out
        HEADER resources.h
        NAMESPACE Resources
        RESOURCE_NAMES codec
        RESOURCES
        "${PROJECT_SOURCE_DIR}/resources/codec.dat"
)
target_link_libraries(SpicyGoat PUBLIC nlohmann_json::nlohmann_json pthread nbt++ toml11 zlibstatic stduuid absl::strings)
target_link_libraries(SpicyGoat PRIVATE SpicyGoat_resources -static)
if(WIN32)
    target_link_libraries(SpicyGoat PRIVATE wsock32 ws2_32)
endif()
