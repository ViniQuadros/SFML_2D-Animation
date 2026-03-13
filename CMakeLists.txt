cmake_minimum_required (VERSION 3.12)
project ("SFML_2D-Animation")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

add_subdirectory(external/box2d)

add_executable(SFML_2D-Animation ${SOURCES})

target_include_directories(SFML_2D-Animation PRIVATE 
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(SFML_2D-Animation
    PRIVATE
    box2d
    "${CMAKE_SOURCE_DIR}/lib/sfml-graphics.lib"
    "${CMAKE_SOURCE_DIR}/lib/sfml-window.lib"
    "${CMAKE_SOURCE_DIR}/lib/sfml-system.lib"
)

file(COPY "${CMAKE_SOURCE_DIR}/CharactersSprites" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "${CMAKE_SOURCE_DIR}/map" DESTINATION "${CMAKE_BINARY_DIR}")