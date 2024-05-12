# CMakeList.txt : CMake project for wait_for_event, include source and define
# project specific logic here.
#

project(WaitForEventExample)

set(CMAKE_CXX_STANDARD			20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS		OFF)

add_executable (
    ${PROJECT_NAME}  
    "main.cxx"
)

target_link_libraries(
    ${PROJECT_NAME}
    WaitForEventLib
)



# TODO: Add tests and install targets if needed.
