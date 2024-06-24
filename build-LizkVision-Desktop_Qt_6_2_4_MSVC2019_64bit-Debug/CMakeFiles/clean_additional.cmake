# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\LizkVision_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\LizkVision_autogen.dir\\ParseCache.txt"
  "LizkVision_autogen"
  )
endif()
