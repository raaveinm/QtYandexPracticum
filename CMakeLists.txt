cmake_minimum_required(VERSION 4.0)
project(QtYandexPracticum)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
#        Multimedia
        REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(QtYandexPracticum
#        Sprint-4-2-Gomoku
#        problems/sprint4/gomoku/submission/controller.h
#        problems/sprint4/gomoku/submission/main.cpp
#        problems/sprint4/gomoku/submission/model.h
#        problems/sprint4/gomoku/submission/submission.pro
#        problems/sprint4/gomoku/submission/view.cpp
#        problems/sprint4/gomoku/submission/view.h
#        problems/sprint4/gomoku/submission/view.ui

#        Sprint-4-1-3-Vector_Emulator-1
#        problems/sprint4/vector-emulator-01/submission/main.cpp
#        problems/sprint4/vector-emulator-01/submission/mainwindow.h
#        problems/sprint4/vector-emulator-01/submission/mainwindow.cpp
#        problems/sprint4/vector-emulator-01/submission/mainwindow.ui
#        problems/sprint4/vector-emulator-01/submission/model.h

#        Sprint-4-1-5-Vector_Emulator-2
#        problems/sprint4/vector-emulator-02/submission/main.cpp
#        problems/sprint4/vector-emulator-02/submission/mainwindow.h
#        problems/sprint4/vector-emulator-02/submission/mainwindow.cpp
#        problems/sprint4/vector-emulator-02/submission/mainwindow.ui
#        problems/sprint4/vector-emulator-02/submission/model.h

#        Sprint-4-1-6-Vector_Emulator-3
#        problems/sprint4/vector-emulator-03/submission/main.cpp
#        problems/sprint4/vector-emulator-03/submission/mainwindow.h
#        problems/sprint4/vector-emulator-03/submission/mainwindow.cpp
#        problems/sprint4/vector-emulator-03/submission/mainwindow.ui
#        problems/sprint4/vector-emulator-03/submission/model.h

#       Sprint-4-1-7-Vector_Emulator-4
#        problems/sprint4/vector-emulator-04/submission/main.cpp
#        problems/sprint4/vector-emulator-04/submission/mainwindow.h
#        problems/sprint4/vector-emulator-04/submission/mainwindow.cpp
#        problems/sprint4/vector-emulator-04/submission/mainwindow.ui
#        problems/sprint4/vector-emulator-04/submission/model.h

#        Sprint-4-1-8-Vector_Emulator-5
        problems/sprint4/vector-emulator-05/submission/main.cpp
        problems/sprint4/vector-emulator-05/submission/mainwindow.h
        problems/sprint4/vector-emulator-05/submission/mainwindow.cpp
        problems/sprint4/vector-emulator-05/submission/mainwindow.ui
        problems/sprint4/vector-emulator-05/submission/model.h

#        Sprint-4-1-9-Meander
#        problems/sprint4/meander/submission/main.cpp
#        problems/sprint4/meander/submission/mainwindow.cpp
#        problems/sprint4/meander/submission/mainwindow.h
#        problems/sprint4/meander/submission/mainwindow.ui
#        problems/sprint4/meander/submission/player.cpp
#        problems/sprint4/meander/submission/player.h
#        problems/sprint4/meander/submission/signal-processing.h
#        problems/sprint4/meander/submission/submission.pro

#        Sprint-4-2-4-Map_Emulator
#        problems/sprint4/map-emulator-01/submission/main.cpp
#        problems/sprint4/map-emulator-01/submission/mainwindow.cpp
#        problems/sprint4/map-emulator-01/submission/mainwindow.h
#        problems/sprint4/map-emulator-01/submission/mainwindow.ui
#        problems/sprint4/map-emulator-01/submission/model.h
#        problems/sprint4/map-emulator-01/submission/submission.pro

#        Sprint-4-2-6-Filmoteka
#        problems/sprint4/filmoteka/submission/main.cpp
#        problems/sprint4/filmoteka/submission/mainwindow.cpp
#        problems/sprint4/filmoteka/submission/mainwindow.h
#        problems/sprint4/filmoteka/submission/mainwindow.ui
#        problems/sprint4/filmoteka/submission/submission.pro

#        Sprint-4-3-4-Oraculum
#        problems/sprint4/oraculum/submission/main.cpp
#        problems/sprint4/oraculum/submission/mainwindow.cpp
#        problems/sprint4/oraculum/submission/mainwindow.h
#        problems/sprint4/oraculum/submission/mainwindow.ui

#        Sprint-4-4-Final_Task-Dequeue_Emulator
#        problems/sprint4/deque-emulator/submission/algo.h
#        problems/sprint4/deque-emulator/submission/main.cpp
#        problems/sprint4/deque-emulator/submission/mainwindow.cpp
#        problems/sprint4/deque-emulator/submission/mainwindow.h
#        problems/sprint4/deque-emulator/submission/mainwindow.ui
#        problems/sprint4/deque-emulator/submission/model.h
#        problems/sprint4/deque-emulator/submission/submission.pro
)

target_include_directories(QtYandexPracticum PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(QtYandexPracticum PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
#        Qt6::Multimedia
)
