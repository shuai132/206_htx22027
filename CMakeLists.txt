# ONLY FOR WRITE CODE
cmake_minimum_required(VERSION 2.8)
project(test)
set(CMAKE_CXX_STANDARD 14)

add_definitions(-DD_OS_ALONE)

include_directories(
        app/src
        app/src/src

        app/drv/include
        app/drv/include/drvcommon
        app/drv/include/drvcommon

        standalone_bsp_0/ps7_cortexa9_0/include
        )

file(GLOB SRCS
        app/src/*
        app/src/crc/*
        app/src/src/*
        app/drv/drv_src/*
        standalone_bsp_0/ps7_cortexa9_0/libsrc/standalone_v6_8/src/*
        standalone_bsp_0/ps7_cortexa9_0/libsrc/standalone_v6_8/src/profile/*
        )
add_executable(${PROJECT_NAME} ${SRCS})
