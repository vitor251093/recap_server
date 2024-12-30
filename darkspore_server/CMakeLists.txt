cmake_minimum_required(VERSION 3.20.4)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
# set(CMAKE_CXX_FLAGS_DEBUG "-fconcepts")
# set(CMAKE_CXX_FLAGS_MINSIZEREL "-fconcepts")
# set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-fconcepts")
# set(CMAKE_CXX_FLAGS_RELEASE "-fconcepts")

project(recap_server VERSION 1.0.0)

# CPM package manager setup
include(cmake/get_cpm.cmake)

file(GLOB_RECURSE RECAP_HEADERS "${CMAKE_CURRENT_LIST_DIR}/source/*.h")
file(GLOB_RECURSE RECAP_SOURCES "${CMAKE_CURRENT_LIST_DIR}/source/*.cpp")

add_definitions(-D_WIN32_WINNT=0x0601 -D_CRT_SECURE_NO_WARNINGS -DWIN32_LEAN_AND_MEAN -DNOMINMAX)
add_definitions(-DBOOST_NETWORK_ENABLE_HTTPS -DBOOST_ASIO_DISABLE_CONCEPTS)
add_definitions(-DRAPIDJSON_HAS_STDSTRING)
add_definitions(-DSOL_STRINGS_ARE_NUMBERS=1 -DSOL_SAFE_FUNCTION=1 -DSOL_LUAJIT=1 -DSOL_EXCEPTIONS_SAFE_PROPAGATION=1)

add_executable(recap_server ${RECAP_SOURCES} ${RECAP_SOURCES})
target_include_directories(recap_server PRIVATE source)

# Boost
set(BOOST_INCLUDE_LIBRARIES "asio;bind;regex;beast")
CPMAddPackage(
    NAME Boost
    VERSION 1.84.0
    URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
    URL_HASH SHA256=2e64e5d79a738d0fa6fb546c6e5c2bd28f88d268a2a080546f74e5ff98f29d0e
    OPTIONS "BOOST_ENABLE_CMAKE ON")
target_link_libraries(recap_server PRIVATE boost_regex boost_asio boost_beast boost_bind)

# pugixml
CPMAddPackage("gh:zeux/pugixml@1.14")
target_link_libraries(recap_server PRIVATE pugixml)

# RapidJSON
CPMAddPackage(NAME rapidjson
    GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
    GIT_TAG v1.1.0
    OPTIONS "RAPIDJSON_BUILD_EXAMPLES OFF"
            "RAPIDJSON_BUILD_TESTS OFF"
            "RAPIDJSON_BUILD_DOC OFF")
target_include_directories(recap_server PRIVATE "${rapidjson_SOURCE_DIR}/include")

# OpenSSL
CPMAddPackage(
    GIT_REPOSITORY https://github.com/jimmy-park/openssl-cmake.git
    GIT_TAG 5e5cef2e3c1713cc775ffe490bd0ff1c12a7ced7
    OPTIONS "OPENSSL_TARGET_VERSION 1.1.1b"
            "OPENSSL_CONFIGURE_OPTIONS no-shared\\\\;no-tests"
            "OPENSSL_ENABLE_PARALLEL OFF"
            "OPENSSL_BUILD_VERBOSE ON"
            "OPENSSL_CONFIGURE_VERBOSE ON")
target_link_libraries(recap_server PRIVATE OpenSSL::SSL OpenSSL::Crypto OpenSSL::applink)

# LuaJIT
CPMAddPackage(
    NAME luajit
    GIT_REPOSITORY https://github.com/LuaJIT/LuaJIT.git
    VERSION 2.1.0-beta3
    DOWNLOAD_ONLY YES)
if(luajit_ADDED)
    add_library(luajit SHARED IMPORTED)
    file(GLOB_RECURSE LUAJIT_SOURCES "${luajit_SOURCE_DIR}/src/*.h" "${luajit_SOURCE_DIR}/src/*.c")

    if(MSVC)
        include(cmake/get_findvcvars.cmake)
        find_package(Vcvars REQUIRED)
        set(LUAJIT_BUILD_COMMAND ${Vcvars_LAUNCHER} ${luajit_SOURCE_DIR}/src/msvcbuild.bat)
        set(LUAJIT_BUILD_OUTPUT ${luajit_SOURCE_DIR}/src/lua51.dll)
        set_target_properties(luajit PROPERTIES IMPORTED_IMPLIB ${luajit_SOURCE_DIR}/src/lua51.lib)
    else()
        set(LUAJIT_BUILD_COMMAND make)
        set(LUAJIT_BUILD_OUTPUT ${luajit_SOURCE_DIR}/src/libluajit.so)
    endif()

    set_target_properties(luajit PROPERTIES IMPORTED_LOCATION ${LUAJIT_BUILD_OUTPUT})
    add_custom_command(
        OUTPUT ${LUAJIT_BUILD_OUTPUT}
        COMMAND ${LUAJIT_BUILD_COMMAND}
        DEPENDS ${LUAJIT_SOURCES}
        WORKING_DIRECTORY ${luajit_SOURCE_DIR}/src
        VERBATIM)
    add_custom_target(luajit-build DEPENDS ${LUAJIT_BUILD_OUTPUT})
    add_dependencies(luajit luajit-build)
    target_include_directories(luajit SYSTEM INTERFACE $<BUILD_INTERFACE:${luajit_SOURCE_DIR}/src>)

    target_link_libraries(recap_server PRIVATE luajit)
endif()

# Sol
CPMAddPackage("gh:ThePhD/sol2@3.3.1")
target_link_libraries(recap_server PRIVATE sol2)

# GLM
CPMAddPackage(
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8)
target_link_libraries(recap_server PRIVATE glm::glm)

# cpp-base64
CPMAddPackage(
    NAME cpp_base64
    GIT_REPOSITORY https://github.com/ReneNyffenegger/cpp-base64.git
    GIT_TAG V2.rc.08
    DOWNLOAD_ONLY YES)
if(cpp_base64_ADDED)
    FILE(GLOB cpp_base64_sources ${cpp_base64_SOURCE_DIR}/*.cpp)
    list(REMOVE_ITEM cpp_base64_sources "${cpp_base64_SOURCE_DIR}/test.cpp"
                                        "${cpp_base64_SOURCE_DIR}/test-google.cpp")
    add_library(cpp_base64 STATIC ${cpp_base64_sources})
    target_include_directories(cpp_base64 PUBLIC $<BUILD_INTERFACE:${cpp_base64_SOURCE_DIR}>)
    target_link_libraries(recap_server PRIVATE cpp_base64)
endif()

# lodepng
CPMAddPackage(
    NAME lodepng
    GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
    GIT_TAG 0b1d9ccfc2093e5d6620cd9a11d03ee6ff6705f5
    DOWNLOAD_ONLY YES)
if(lodepng_ADDED)
    FILE(GLOB lodepng_sources ${lodepng_SOURCE_DIR}/*.cpp)
    list(REMOVE_ITEM lodepng_sources "${lodepng_SOURCE_DIR}/lodepng_benchmark.cpp"
                                     "${lodepng_SOURCE_DIR}/lodepng_fuzzer.cpp"
                                     "${lodepng_SOURCE_DIR}/lodepng_unittest.cpp")
    add_library(lodepng STATIC ${lodepng_sources})
    target_include_directories(lodepng PUBLIC $<BUILD_INTERFACE:${lodepng_SOURCE_DIR}>)
    target_link_libraries(recap_server PRIVATE lodepng)
endif()

# RakNet
CPMAddPackage(
    NAME raknet
    VERSION 3.902
    URL http://www.jenkinssoftware.com/raknet/downloads/RakNet-3.902.zip
    URL_HASH SHA256=8c45d0c25a77ef095e060bcbbc01e198eb98a7a1f713fdf067bfe01a919e4274
    DOWNLOAD_ONLY YES)
if(raknet_ADDED)
    # Apply patches
    set(RAKNET_PATCH "${CMAKE_CURRENT_LIST_DIR}/cmake/patches/RakNet-3.902.patch")
    execute_process(COMMAND git init WORKING_DIRECTORY ${raknet_SOURCE_DIR})
    execute_process(COMMAND git apply --ignore-whitespace --verbose ${RAKNET_PATCH} WORKING_DIRECTORY ${raknet_SOURCE_DIR})

    add_subdirectory(${raknet_SOURCE_DIR} ${raknet_BINARY_DIR})
    if(WIN32 AND NOT UNIX)
        target_link_libraries(recap_server PRIVATE DLL)
    else()
        target_link_libraries(recap_server PRIVATE RakNetDynamic)
    endif()
endif()
