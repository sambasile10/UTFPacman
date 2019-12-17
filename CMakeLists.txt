cmake_minimum_required(VERSION 3.15)
project(Pacman)

set(CMAKE_CXX_STANDARD 11)
list(APPEND CMAKE_LIBRARY_PATH /usr/include/ncursesw)
list(APPEND CMAKE_LIBRARY_PATH /opt/boost/lib)

set(NCURSES_LIBRARY_NAME "ncursesw")
set(CURSES_FORM_LIBRARY_NAME "formw")
set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

include(FindCurses)

find_package(Curses REQUIRED)
find_package(Boost 1.71)

include_directories(/usr/include/ncursesw)
include_directories(${CURSES_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIRS})

message(STATUS "CURSES_LIBRARIES: ${CURSES_LIBRARIES}")

set(CMAKE_CXX_FLAGS "-D_GNU_SOURCE -D_DEFAULT_SOURCE -I/usr/include/ncursesw")
add_executable(Pacman Level.h Viewport.h Position.h Viewport.cpp Position.cpp Entity.h Entity.cpp Ghost.h Ghost.cpp Level.cpp Pacman.h Game.h Pacman.cpp Game.cpp)
#add_executable(Pacman main.cpp)
target_link_libraries(Pacman ${CURSES_LIBRARIES} ${Boost_LIBRARIES})