cmake_minimum_required(VERSION 3.15)
project(htx22027)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(app/src/src)
link_libraries(comm_parser)

add_definitions(-DD_OS_ALONE)
include_directories(
        app/drv/include
        app/drv/include/drvcommon
        app/drv/include/drvcommon

        standalone_bsp_0/ps7_cortexa9_0/include
        )
file(GLOB SRCS
        app/src/*
        app/drv/drv_src/*
        standalone_bsp_0/ps7_cortexa9_0/libsrc/standalone_v6_8/src/*
        standalone_bsp_0/ps7_cortexa9_0/libsrc/standalone_v6_8/src/profile/*
        )

# 用于代码提示
add_executable(${PROJECT_NAME} ${SRCS})

# 测试逻辑
add_executable(test
        test/main.cpp
        test/mock_data.cpp
        )
