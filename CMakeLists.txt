cmake_minimum_required(VERSION 3.7)

if(NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
     set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
endif()

project(conway C)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -Wall -Werror -fdump-rtl-expand")

set(SRCS
  main.c
  logic.c
  render.c
)

set(HEADERS
  logic.h
  render.h
  game.h
)

set(CMAKE_SYSTEM_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(conway ${SRCS} ${HEADERS})
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} SDL2::Main)
