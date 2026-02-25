# CMakeList.txt: projeto de CMake para SFML_2D-Animation, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)

# Habilite a Recarga Dinâmica para compiladores MSVC, se houver suporte.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SFML_2D-Animation")

# Adicione a origem ao executável deste projeto.
add_executable (SFML_2D-Animation "src/SFML_2D-Animation.cpp" "src/SFML_2D-Animation.h"   "src/Character.h" "src/Character.cpp"   "src/Animation.h" "src/Animation.cpp"   "src/Enemy.h" "src/Player.h" "src/Player.cpp" "src/Enemy.cpp")
target_link_libraries(SFML_2D-Animation ${CMAKE_SOURCE_DIR}/lib/sfml-graphics.lib)
target_link_libraries(SFML_2D-Animation ${CMAKE_SOURCE_DIR}/lib/sfml-window.lib)
target_link_libraries(SFML_2D-Animation ${CMAKE_SOURCE_DIR}/lib/sfml-system.lib)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Defina o padrão C++20 se o CMake for versão 3.12 ou superior.
set_property(TARGET SFML_2D-Animation PROPERTY CXX_STANDARD 20)
set_property(TARGET SFML_2D-Animation PROPERTY CXX_STANDARD_REQUIRED ON)

file(COPY ${CMAKE_SOURCE_DIR}/CharactersSprites
     DESTINATION ${CMAKE_BINARY_DIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SFML_2D-Animation PROPERTY CXX_STANDARD 20)
endif()

# TODO: Adicione testes e instale destinos, se necessário.
