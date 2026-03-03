cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
project(espeon VERSION 0.0.1 LANGUAGES C CXX)

option(ESPEON_BUILD_TESTS "Build espeon Tests" OFF)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

add_library(espeon STATIC ${HEADERS} ${SOURCES})
add_library(espeon::espeon ALIAS espeon)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)
target_link_libraries(espeon PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf)
target_include_directories(espeon PUBLIC ${PROJECT_SOURCE_DIR}/include)

install(TARGETS espeon
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)

if (ESPEON_BUILD_TESTS)
    file(GLOB_RECURSE TEST_SOURCES test/*.cpp)
    add_executable(espeon_test ${TEST_SOURCES})
    target_link_libraries(espeon_test PRIVATE espeon::espeon SDL3::SDL3)
endif()