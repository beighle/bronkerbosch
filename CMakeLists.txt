cmake_minimum_required( VERSION 2.8 )

project( BronKerbosch )

set( bk_hdr
	src/bronkerbosch.h
	src/utils.h
)

set( bk_src
	src/bronkerbosch.cpp
	src/utils.cpp
	src/main.cpp
)

set( LIBLEMON_ROOT "$ENV{HOME}/lemon" CACHE PATH "Additional search directory for lemon library" )

set( Boost_USE_STATIC_LIBS ON )
find_package( Boost REQUIRED )

SET(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libstdc++")

if( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++ " )
endif()

include_directories( "${LIBLEMON_ROOT}/include" "src" ${Boost_INCLUDE_DIRS} )
link_directories( "${LIBLEMON_ROOT}/lib" )

set( CommonLibs
	m
	emon
)

add_executable( bk ${bk_src} ${bk_hdr} )
target_link_libraries( bk ${CommonLibs} )

