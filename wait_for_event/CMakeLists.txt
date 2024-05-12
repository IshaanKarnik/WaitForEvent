# CMakeList.txt : CMake project for wait_for_event, include source and define
# project specific logic here.
#

project(WaitForEventLib)

set(CMAKE_CXX_STANDARD			20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS		OFF)

add_library(
    ${PROJECT_NAME}
    INTERFACE
    ${SRC_SETONCE}
)

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE
    ${PROJECT_SOURCE_DIR}
)



# TODO: Add tests and install targets if needed.
