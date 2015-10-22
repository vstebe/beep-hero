set(PROJECT_NAME beep-hero)

project(${PROJECT_NAME})
cmake_minimum_required(VERSION 2.8)
set(SRC_LIST
    ./src/main.cpp
    ./src/beeper.cpp
    ./src/sheet.cpp
    ./src/sheetparser.cpp
    ./src/note.cpp
    ./src/rawnote.cpp
    ./src/soundsystem.cpp
    ./src/utils.cpp
    ./src/config.h
    )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})

INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/bin)

