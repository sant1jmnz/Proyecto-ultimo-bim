# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Trabajo_Integrador_Ramirez_SanMartin_JImenez_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Trabajo_Integrador_Ramirez_SanMartin_JImenez_autogen.dir/ParseCache.txt"
  "Trabajo_Integrador_Ramirez_SanMartin_JImenez_autogen"
  )
endif()
