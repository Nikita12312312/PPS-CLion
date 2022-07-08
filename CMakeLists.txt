cmake_minimum_required(VERSION 3.15)
project(my_first_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wno-strict-aliasing")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -DGNSS_SIM")


add_executable(${PROJECT_NAME})

#set(PROJECT_LIBS    System)
#set(LIB_TARGET ${PROJECT_NAME}${PLATFORM_EXEC_SUFFIX})
#add_library(${LIB_TARGET})
#target_link_libraries(${LIB_TARGET} ${PROJECT_LIBS})
#install(TARGETS ${LIB_TARGET} DESTINATION Lib)
#add_executable(my_first_project main.cpp)
#add_subdirectory(System System)

set(HEADERS ./PPS_from_fpga/Include/receiver.h)

set(SOURCES ./main.cpp
            ./PPS_from_fpga/Source/receiver.cpp)

target_sources(${PROJECT_NAME} PUBLIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_INSTALL_PREFIX}/Include ${CMAKE_BINARY_DIR} ${PROJECT_LEVEL}
        )
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/System/Interfaces)
target_link_libraries(${PROJECT_NAME} System Interfaces -static-libgcc -static-libstdc++)
add_subdirectory(System)
#install(TARGETS ${PROJECT_NAME} DESTINATION Bin)
#add_executable(${PROJECT_NAME})