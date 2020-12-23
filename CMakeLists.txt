cmake_minimum_required(VERSION 3.17)
project(autodock_vina_extractor C)

set(CMAKE_C_STANDARD 11)

add_executable(autodock_vina_extractor
        data_extractor.c)
