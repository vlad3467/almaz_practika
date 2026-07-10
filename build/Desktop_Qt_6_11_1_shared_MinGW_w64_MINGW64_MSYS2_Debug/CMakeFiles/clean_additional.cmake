# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PortSniffer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PortSniffer_autogen.dir\\ParseCache.txt"
  "PortSniffer_autogen"
  )
endif()
