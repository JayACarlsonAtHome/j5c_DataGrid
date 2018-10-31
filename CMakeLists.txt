cmake_minimum_required(VERSION 3.9)

project(j5c_DataGrid)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES

        source/Common_Functions.h
        source/Common_Functions.cpp
        source/DataColumnHeader.h
        source/DataColumnHeader.cpp
        source/DataDictionary.h
        source/DataDictionary.cpp
        source/DataGrid.h
        source/DataGrid.cpp
        main.cpp
        )

add_executable(j5c_data_grid ${SOURCE_FILES})
