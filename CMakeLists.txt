cmake_minimum_required(VERSION 3.24)
project(AgendaSSD2 C)

set(CMAKE_C_STANDARD 11)

add_executable(AgendaSSD2 main.c cell.c cell.h list.c list.h meeting.c meeting.h save.c save.h menu.c menu.h partie1-2/list_value.c partie1-2/list_value.h partie1-2/cell_value.c partie1-2/cell_value.h timer.c timer.h graph/pbPlots.h graph/pbPlots.c graph/supportLib.c)
