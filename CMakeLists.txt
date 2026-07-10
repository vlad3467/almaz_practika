cmake_minimum_required(VERSION 3.19)
project(PortSniffer LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

add_library(tins STATIC IMPORTED)
set_target_properties(tins PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/external/libtins/lib/libtins.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external/libtins/include"
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

install(TARGETS PortSniffer
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET PortSniffer
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})