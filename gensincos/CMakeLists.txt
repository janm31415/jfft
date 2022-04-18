set(HDRS
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


add_executable(gensincos ${HDRS} ${SRCS})
source_group("Header Files" FILES ${hdrs})
source_group("Source Files" FILES ${srcs})

target_include_directories(gensincos
    PRIVATE
    ../qdouble
    )
	
target_link_libraries(gensincos
    PRIVATE	
    )	