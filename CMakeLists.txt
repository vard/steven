project(steven)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
set (CMAKE_CXX_FLAGS " -Wall -std=c++0x -stdlib=libc++ -v")

#set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -stdlib=libc++")
add_executable(${PROJECT_NAME} ${SRC_LIST})

#set(GCC_CXX_FLAGS ${GCC_CXX_FLAGS} "-all_load -lstdc++")

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost COMPONENTS thread filesystem system program_options REQUIRED)
#if(Boost_FOUND)
#   target_link_libraries(steven ${Boost_LIBRARIES})
#endif()

#find_library(OPENSSL_LIBRARIES ssl /usr/local/opt/openssl/ REQUIRED)

#list( APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")
target_link_libraries(steven ${Boost_LIBRARIES} libcasablanca.dylib libcommon_utilities.dylib /usr/local/lib/libmongoclient.a /usr/local/opt/openssl/lib/libssl.a /usr/local/opt/openssl/lib/libcrypto.a )



