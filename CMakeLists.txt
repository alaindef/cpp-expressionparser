cmake_minimum_required(VERSION 3.0.0)
project(expressionparser VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(SOURCES
    main.cpp
    calculator.cpp
    tokengenerator.cpp
    rpngenerator.cpp
    vartable.cpp)

set(HEADERS
     calculator.h
     tokengenerator.h
     rpngenerator.h
     vartable.h
     utils.h)

add_executable(expressionparser ${SOURCES} ${HEADERS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
