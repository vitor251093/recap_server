cmake_minimum_required(VERSION 3.20.4)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_DEBUG "-fconcepts")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-fconcepts")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-fconcepts")
set(CMAKE_CXX_FLAGS_RELEASE "-fconcepts")

set(HEADERS
    CMAKE_HEADERS
)

set(SOURCES
    CMAKE_SOURCES
)

add_definitions(-D_WIN32_WINNT=0x0601 -D_CRT_SECURE_NO_WARNINGS -DWIN32_LEAN_AND_MEAN -DNOMINMAX)
add_definitions(-DBOOST_NETWORK_ENABLE_HTTPS -DBOOST_ASIO_DISABLE_CONCEPTS)
add_definitions(-DRAPIDJSON_HAS_STDSTRING)
add_definitions(-DSOL_STRINGS_ARE_NUMBERS=1 -DSOL_SAFE_FUNCTION=1 -DSOL_LUAJIT=1 -DSOL_EXCEPTIONS_SAFE_PROPAGATION=1)

project(recap_server VERSION 1.0.0)
add_executable(recap_server ${SOURCES})
include_directories(source/)
include_directories(source/raknet)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

# Boost
set(Boost_INCLUDE_DIR libs/boost_1_70_0)
set(Boost_LIBRARY_DIR libs/boost_1_70_0/stage/lib)
find_package(Boost 1.70.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
target_link_libraries(recap_server ${Boost_LIBRARIES} )

# pugixml
add_subdirectory(libs/pugixml-1.10)
target_link_libraries(recap_server PUBLIC pugixml)

# RapidJSON
set(RAPIDJSON_BUILD_EXAMPLES OFF)
set(RapidJSON_INCLUDE_DIRS libs/rapidjson-1.1.0/include)
add_subdirectory(libs/rapidjson-1.1.0)
target_link_libraries(recap_server ${RapidJSON_LIBRARIES})
include_directories(${RapidJSON_INCLUDE_DIRS})

# RakNet
add_subdirectory(libs/raknet-3.902-mod)
include_directories(libs/raknet-3.902-mod/Source)
target_link_libraries(recap_server PUBLIC /recap/libs/raknet-3.902-mod/Lib/DLL/libRakNetDynamic.so)

# OpenSSL
set(OPENSSL_ROOT_DIR libs/openssl-1.1.1b)
set(OPENSSL_INCLUDE_DIR libs/openssl-1.1.1b/include)
set(OPENSSL_CRYPTO_LIBRARY /usr/local/lib)
set(OPENSSL_SSL_LIBRARY /usr/local/lib/libssl.so)
set(OPENSSL_FIND_VERSION 1.1.1b)
find_package(OpenSSL REQUIRED)
target_link_libraries(recap_server PUBLIC ${OPENSSL_LIBRARIES} )
include_directories(${OPENSSL_INCLUDE_DIR})

# Sol
include_directories(/usr/include/luajit-2.1)
include_directories(libs/sol2)

# Threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(recap_server PRIVATE Threads::Threads)

