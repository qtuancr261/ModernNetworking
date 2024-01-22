cmake_minimum_required(VERSION 3.27)
string(TIMESTAMP configurationTime "%y.%m.%d.%H" UTC)
project(server VERSION ${configurationTime} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    set(execName server)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(execName serverd)
endif ()

message(STATUS "OS type: " ${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_VERSION})
message(STATUS "OS processor architecture: " ${CMAKE_SYSTEM_PROCESSOR})
message(STATUS "Build type:  ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Default compiler flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "Additional compiler flags: ${_flags}")
message(STATUS "Version: ${configurationTime}")

# declare: system libs - it depends on your system installed
find_library(libbz2 bz2)
if (libbz2)
    message(STATUS "Found system library lzma: ${libbz2}")
else ()
    message(FATAL_ERROR "Could NOT find library bz2. Please install it via your system package manager to build this project !")
endif ()

find_library(liblzma lzma)
if (liblzma)
    message(STATUS "Found system library lzma: ${liblzma}")
else ()
    message(FATAL_ERROR "Could NOT find library lzma. Please install it via your system package manager to build this project !")
endif ()

find_library(liblz4 lz4)
if (liblz4)
    message(STATUS "Found system library lz4: ${liblz4}")
else ()
    message(FATAL_ERROR "Could NOT find library lz4. Please install it via your system package manager to build this project !")
endif ()

find_library(libz z)
if (libz)
    message(STATUS "Found system library z: ${libz}")
else ()
    message(FATAL_ERROR "Could NOT find library z. Please install it via your system package manager to build this project !")
endif ()

find_library(libsnappy snappy)
if (libsnappy)
    message(STATUS "Found system library snappy: ${libsnappy}")
else ()
    message(FATAL_ERROR "Could NOT find library snappy. Please install it via your system package manager to build this project !")
endif ()

find_library(libunwind unwind)
if (libunwind)
    message(STATUS "Found system library unwind: ${libunwind}")
else ()
    message(FATAL_ERROR "Could NOT find library unwind. Please install it via your system package manager to build this project !")
endif ()

find_library(libboost_context boost_context)
if (libboost_context)
    message(STATUS "Found system library boost_context: ${libboost_context}")
else ()
    message(FATAL_ERROR "Could NOT find library boost_context. Please install it via your system package manager to build this project !")
endif ()

find_library(libboost_iostreams boost_iostreams)
if (libboost_iostreams)
    message(STATUS "Found system library boost_iostreams: ${libboost_iostreams}")
else ()
    message(FATAL_ERROR "Could NOT find library boost_iostreams. Please install it via your system package manager to build this project !")
endif ()

find_library(libsodium sodium)
if (libsodium)
    message(STATUS "Found system library sodium: ${libsodium}")
else ()
    message(FATAL_ERROR "Could NOT find library sodium. Please install it via your system package manager to build this project !")
endif ()

find_library(libssl ssl)
if (libssl)
    message(STATUS "Found system library ssl: ${libssl}")
else ()
    message(FATAL_ERROR "Could NOT find library ssl. Please install it via your system package manager to build this project !")
endif ()

find_library(libcrypto crypto)
if (libcrypto)
    message(STATUS "Found system library crypto: ${libcrypto}")
else ()
    message(FATAL_ERROR "Could NOT find library crypto. Please install it via your system package manager to build this project !")
endif ()

find_library(libevent event)
if (libevent)
    message(STATUS "Found system library event: ${libevent}")
else ()
    message(FATAL_ERROR "Could NOT find library event. Please install it via your system package manager to build this project !")
endif ()

find_library(libdouble-conversion double-conversion)
if (libdouble-conversion)
    message(STATUS "Found system library double-conversion: ${libdouble-conversion}")
else ()
    message(FATAL_ERROR "Could NOT find library double-conversion. Please install it via your system package manager to build this project !")
endif ()

find_library(libiberty iberty)
if (libiberty)
    message(STATUS "Found system library iberty: ${libiberty}")
else ()
    message(FATAL_ERROR "Could NOT find library iberty. Please install it via your system package manager to build this project !")
endif ()

find_library(libgflags gflags)
if (libgflags)
    message(STATUS "Found system library gflags: ${libgflags}")
else ()
    message(FATAL_ERROR "Could NOT find library gflags. Please install it via your system package manager to build this project !")
endif ()

find_library(libglog glog)
if (libglog)
    message(STATUS "Found system library glog: ${libglog}")
else ()
    message(FATAL_ERROR "Could NOT find library glog. Please install it via your system package manager to build this project !")
endif ()

find_library(libpthread pthread)
if (libpthread)
    message(STATUS "Found system library pthread: ${libpthread}")
else ()
    message(FATAL_ERROR "Could NOT find library pthread. Please install it via your system package manager to build this project !")
endif ()

find_library(libdl dl)
if (libdl)
    message(STATUS "Found system library dl: ${libdl}")
else ()
    message(FATAL_ERROR "Could NOT find library dl. Please install it via your system package manager to build this project !")
endif ()

find_library(librt rt)
if (librt)
    message(STATUS "Found system library rt: ${librt}")
else ()
    message(FATAL_ERROR "Could NOT find library rt. Please install it via your system package manager to build this project !")
endif ()

add_library(libwangle STATIC IMPORTED)
set_target_properties(libwangle PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/Debug/lib/libwangle.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/RelWithDebInfo/lib/libwangle.a)

add_library(libfizz_test_support STATIC IMPORTED)
set_target_properties(libfizz_test_support PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/Debug/lib/libfizz_test_support.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/RelWithDebInfo/lib/libfizz_test_support.a)

add_library(libfizz STATIC IMPORTED)
set_target_properties(libfizz PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/Debug/lib/libfizz.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/RelWithDebInfo/lib/libfizz.a)

add_library(libfolly_exception_counter STATIC IMPORTED)
set_target_properties(libfolly_exception_counter PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/Debug/lib/libfolly_exception_counter.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/RelWithDebInfo/lib/libfolly_exception_counter.a)

add_library(libfollybenchmark STATIC IMPORTED)
set_target_properties(libfollybenchmark PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/Debug/lib/libfollybenchmark.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/RelWithDebInfo/lib/libfollybenchmark.a)

add_library(libfolly_exception_tracer STATIC IMPORTED)
set_target_properties(libfolly_exception_tracer PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/Debug/lib/libfolly_exception_tracer.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/RelWithDebInfo/lib/libfolly_exception_tracer.a)

add_library(libfolly_test_util STATIC IMPORTED)
set_target_properties(libfolly_test_util PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/Debug/lib/libfolly_test_util.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/RelWithDebInfo/lib/libfolly_test_util.a)

add_library(libfolly_exception_tracer_base STATIC IMPORTED)
set_target_properties(libfolly_exception_tracer_base PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/Debug/lib/libfolly_exception_tracer_base.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/RelWithDebInfo/lib/libfolly_exception_tracer_base.a)

add_library(libfolly STATIC IMPORTED)
set_target_properties(libfolly PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/Debug/lib/libfolly.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/RelWithDebInfo/lib/libfolly.a)

add_library(libfmt STATIC IMPORTED)
set_target_properties(libfmt PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/Debug/lib64/libfmt.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/RelWithDebInfo/lib64/libfmt.a)

add_library(libzstd STATIC IMPORTED)
set_target_properties(libzstd PROPERTIES
        IMPORTED_LOCATION_DEBUG ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/Debug/lib64/libzstd.a
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/../../../../clib/proxygen-deps/RelWithDebInfo/lib64/libzstd.a)



add_executable(${execName} main.cpp)
