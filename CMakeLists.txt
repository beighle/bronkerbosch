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

set( GitCommand1 "symbolic-ref HEAD 2> /dev/null | cut -b 12-" )
execute_process( COMMAND git symbolic-ref HEAD  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
COMMAND tail -c -7 COMMAND tr -d "\\n" OUTPUT_VARIABLE GitBranch )
set( GitCommand2 "log --pretty=format:\\\"%h\\\" -1" )
execute_process( COMMAND git log --pretty=format:%h WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
COMMAND head -n 1  COMMAND tr -d "\\n" OUTPUT_VARIABLE GitHashtag )
set( ANCESTREE_VERSION \"${GitBranch}-${GitHashtag}\" )

set( Boost_USE_STATIC_LIBS ON )
find_package( Boost REQUIRED )

SET(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libstdc++")

if( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++ " )
endif()

include_directories( ${CPLEX_INC_DIR} ${CONCERT_INC_DIR} "${LIBLEMON_ROOT}/include" "src" ${Boost_INCLUDE_DIRS} )
link_directories( ${CPLEX_LIB_DIR} ${CONCERT_LIB_DIR} "${LIBLEMON_ROOT}/lib" )

set( CommonLibs
	m
	emon
)

add_executable( bk ${bk_src} ${bk_hdr} )
target_link_libraries( bk ${CommonLibs} )

