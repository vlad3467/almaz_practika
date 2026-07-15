cmake_minimum_required(VERSION 3.19)
project(PortSniffer LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/external")

add_library(tins STATIC IMPORTED)
set_target_properties(tins PROPERTIES
    IMPORTED_LOCATION "${EXTERNAL_DIR}/libtins/lib/libtins.a"
    INTERFACE_INCLUDE_DIRECTORIES "${EXTERNAL_DIR}/libtins/include"
    INTERFACE_COMPILE_DEFINITIONS "TINS_STATIC"
)

qt_add_executable(PortSniffer
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    snifferworker.cpp
    snifferworker.h
    packetbuffer.cpp
    packetbuffer.h
)

target_link_libraries(PortSniffer PRIVATE
    Qt::Core
    Qt::Widgets
    tins
    ${EXTERNAL_DIR}/npcap/lib/libwpcap.a
    ${EXTERNAL_DIR}/npcap/lib/libPacket.a
    ${EXTERNAL_DIR}/openssl/libssl.a
    ${EXTERNAL_DIR}/openssl/libcrypto.a
    ws2_32
    iphlpapi
    crypt32
    ntdll
)

target_link_options(PortSniffer PRIVATE
    -static
    -static-libgcc
    -static-libstdc++
)