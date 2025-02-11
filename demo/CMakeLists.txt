cmake_minimum_required(VERSION 3.20)

project(demo)
set(PROJECT_NAME demo)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 11)

find_package(Qt5 COMPONENTS Widgets Core Gui)
if (${Qt5_FOUND})
    message("Found Qt " ${Qt5_VERSION})
else()
    message("Couldn't find Qt")
endif()

include_directories(
    ../QJSONConfig
)

add_executable(${PROJECT_NAME}
    ../QJSONConfig/qjsonconfig.cpp
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)
