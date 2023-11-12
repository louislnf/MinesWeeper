cmake_minimum_required(VERSION 3.16)

project(minesweeper)

include(FindCurses)

include_directories( ./ ${CURSES_INCLUDE_DIRS} )

add_executable(
  minesweeper
  main.c
  menu.c
  menu.h
  game.c
  game.h
  graphic.c
  graphic.h
  basic.c
  basic.h)

target_link_libraries( minesweeper ${CURSES_LIBRARIES} )
