
set(HDRS
  ../jfft/jfft.h
  fftw3.h
  )

set(SRCS
  main.cpp
)

if (WIN32)
set(CMAKE_C_FLAGS_DEBUG "/W4 /MP /GF /RTCu /Od /MDd /Zi")
set(CMAKE_CXX_FLAGS_DEBUG "/W4 /MP /GF /RTCu /Od /MDd /Zi")
set(CMAKE_C_FLAGS_RELEASE "/W4 /MP /GF /O2 /Ob2 /Oi /Ot /MD /Zi /DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "/W4 /MP /GF /O2 /Ob2 /Oi /Ot /MD /Zi /DNDEBUG")
endif (WIN32)


add_executable(bench2fftw ${HDRS} ${SRCS})
source_group("Header Files" FILES ${HDRS})
source_group("Source Files" FILES ${SRCS})	

target_include_directories(bench2fftw
    PRIVATE
    )
	
target_link_libraries(bench2fftw
    PRIVATE	
    )	
    
    
add_custom_command(TARGET bench2fftw PRE_BUILD 
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/libfftw3-3.dll" "$<TARGET_FILE_DIR:bench2fftw>/libfftw3-3.dll")
add_custom_command(TARGET bench2fftw PRE_BUILD 
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/libfftw3f-3.dll" "$<TARGET_FILE_DIR:bench2fftw>/libfftw3f-3.dll")
   
add_custom_command(TARGET bench2fftw PRE_BUILD 
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/libfftw3-3.lib" "${CMAKE_CURRENT_BINARY_DIR}/libfftw3-3.lib")
add_custom_command(TARGET bench2fftw PRE_BUILD 
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/libfftw3f-3.lib" "${CMAKE_CURRENT_BINARY_DIR}/libfftw3f-3.lib")
  