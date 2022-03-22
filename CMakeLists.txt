cmake_minimum_required(VERSION 3.17)
project(Card)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Card
        card.cpp
        card.h
        deck.cpp
        deck.h
        hand.cpp
        hand.h
        main.cpp
        menu.cpp
        menu.h
        per.cpp
        per.h PrintHelper.cpp PrintHelper.h)
