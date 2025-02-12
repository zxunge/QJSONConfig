cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME demo)
project(${PROJECT_NAME})

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 11)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)
if (Qt6_FOUND)
    message("-- Found Qt " ${Qt6_VERSION})
else()
    find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)
endif()
if (Qt5_FOUND)
    message("-- Found Qt " ${Qt5_VERSION})
else()
    message(FATAL_ERROR "-- Could not find Qt!")
endif()

include_directories(
    ../QJSONConfig
)

add_executable(${PROJECT_NAME}
    ../QJSONConfig/qjsonconfig.cpp
    main.cpp
)

target_link_libraries(${PROJECT_NAME} 
    Qt::Core
    Qt::Widgets
    Qt::Gui
)
