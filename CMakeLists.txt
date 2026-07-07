cmake_minimum_required(VERSION 3.16)
project(PortSniffer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(tins STATIC IMPORTED)
set_target_properties(tins PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/external/libtins/lib/libtins.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external/libtins/include"
    INTERFACE_COMPILE_DEFINITIONS "TINS_STATIC"
)

add_executable(sniffer main.cpp)

target_link_libraries(sniffer PRIVATE
    tins
    ${CMAKE_SOURCE_DIR}/external/npcap/lib/libwpcap.a
    ${CMAKE_SOURCE_DIR}/external/npcap/lib/libPacket.a
    C:/msys64/mingw64/lib/libws2_32.a
    C:/msys64/mingw64/lib/libiphlpapi.a
    C:/msys64/mingw64/lib/libssl.dll.a
    C:/msys64/mingw64/lib/libcrypto.dll.a
    C:/msys64/mingw64/lib/libcrypt32.a
    C:/msys64/mingw64/lib/libntdll.a
    C:/msys64/mingw64/lib/libpthread.a
)