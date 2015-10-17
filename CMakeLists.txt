project(pianobeep)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(./src SRC_LIST)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_compile_features(pianobeep PRIVATE cxx_range_for)

target_link_libraries(pianobeep ${SFML_LIBRARIES})


