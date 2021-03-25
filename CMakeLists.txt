# CMake file for making PDKs for libmask. Created by Yuan Liu on 12/16/2018
# Normally you only need to use .cpp files for your source file and change the varibles below accordingly.


cmake_minimum_required(VERSION 3.6)


# Change the PDK information below accordingly.

set(PDK_NAME "pdk_Xtech")
set(PDK_VERSION "0.2")
set(PDK_AUTHOR "Bowen Song")
set(PDK_DESCRIPTION "GenII-SiOI_500nmDemo")
set(MASK_LIB_VERSION 7.0)
################


# Change the test file information below accordingly.

set(GDS_FILENAME "mask_example.gds")
set(MASK_NAME "JK_Extension")

################

project(${PDK_NAME})
message(STATUS "Downloading pdk.cmake from https://bintray.com/cmalips/libmask/")
file(DOWNLOAD "https://bintray.com/cmalips/libmask/download_file?file_path=pdk.cmake"
        "${CMAKE_BINARY_DIR}/pdk.cmake")
include(${CMAKE_BINARY_DIR}/pdk.cmake)
