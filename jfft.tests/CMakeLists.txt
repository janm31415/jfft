
set(HDRS
  ../jfft/jfft.h
  jfft_tests.h
  test_assert.h
)

set(SRCS
  jfft_tests.cpp
  test.cpp
  test_assert.cpp
)

if (WIN32)
set(CMAKE_C_FLAGS_DEBUG "/W4 /MP /GF /RTCu /Od /MDd /Zi")
set(CMAKE_CXX_FLAGS_DEBUG "/W4 /MP /GF /RTCu /Od /MDd /Zi")
set(CMAKE_C_FLAGS_RELEASE "/W4 /MP /GF /O2 /Ob2 /Oi /Ot /MD /Zi /DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "/W4 /MP /GF /O2 /Ob2 /Oi /Ot /MD /Zi /DNDEBUG")
endif (WIN32)


add_executable(jfft.tests ${HDRS} ${SRCS})
source_group("Header Files" FILES ${HDRS})
source_group("Source Files" FILES ${SRCS})	

target_include_directories(jfft.tests
    PRIVATE
    )
	
target_link_libraries(jfft.tests
    PRIVATE	
    )	