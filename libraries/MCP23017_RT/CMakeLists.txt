#   Allows for use with ESP-IDF and Arduino as component
#   Tested with ESP-IDF v4.4.4

cmake_minimum_required(VERSION 3.5)

idf_component_register(SRCS "MCP23017.cpp" 
                       INCLUDE_DIRS "."
                       REQUIRES arduino)

project(MCP23017)
