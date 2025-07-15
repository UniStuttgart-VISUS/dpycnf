# <copyright file="CMakeLists.txt" company="Visualisierungsinstitut der Universität Stuttgart">
# Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
# Licensed under the MIT licence. See LICENCE file for details.
# </copyright>
# <author>Christoph Müller</author>

cmake_minimum_required(VERSION 3.17)
project (dpycnf)


# Expat is required to parse the configuration files.
FetchContent_Declare(expat
    GIT_REPOSITORY https://github.com/libexpat/libexpat/
    GIT_TAG R_2_7_1
    GIT_PROGRESS ON
    SOURCE_SUBDIR expat/
)
FetchContent_MakeAvailable(expat)


# Define the library itself.
add_library(dpycnf INTERFACE)

target_include_directories(dpycnf INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
