cmake_minimum_required(VERSION 3.10)
project (jfft)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(qdouble)
add_subdirectory(gensincos)
add_subdirectory(jfft.tests)
add_subdirectory(bench2gfft)
add_subdirectory(bench2nr)

if(WIN32)
add_subdirectory(bench2fftw)
endif(WIN32)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)
