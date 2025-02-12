cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME demo)
project(${PROJECT_NAME})

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 11)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Gui)
if (Qt6_FOUND)
    message("-- Found Qt " ${Qt6_VERSION})
elseif(Qt5_FOUND)
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

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Core
    Qt::Widgets
    Qt::Gui
)
