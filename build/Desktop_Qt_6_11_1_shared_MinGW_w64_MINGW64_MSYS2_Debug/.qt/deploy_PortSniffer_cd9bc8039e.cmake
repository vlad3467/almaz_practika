include("D:/REPOS/PortSniffer/build/Desktop_Qt_6_11_1_shared_MinGW_w64_MINGW64_MSYS2_Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/PortSniffer-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "D:/REPOS/PortSniffer/build/Desktop_Qt_6_11_1_shared_MinGW_w64_MINGW64_MSYS2_Debug/PortSniffer.exe"
    GENERATE_QT_CONF
)
