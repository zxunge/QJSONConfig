cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME demo)
project(${PROJECT_NAME})

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 11)

find_package(Qt6 COMPONENTS Core)
if (NOT Qt6_FOUND)
    find_package(Qt5 REQUIRED COMPONENTS Core)
    if(Qt5_FOUND)
        message("-- Found Qt " ${Qt_VERSION})
    else()
        message(FATAL_ERROR "-- Couldn't find Qt")
else()
    message("-- Found Qt " ${Qt_VERSION})
endif()

include_directories(
    ../QJSONConfig
)

add_executable(${PROJECT_NAME}
    ../QJSONConfig/qjsonconfig.cpp
    main.cpp
)

target_link_libraries(${PROJECT_NAME} Qt::Core)
