cmake_minimum_required(VERSION 3.15)
project(Svg)

# Use C++-17 by default.
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set the module path to include scripts
# CMake - Contains project local modules.
#
# CMake/Modules - Contains project independent modules.
#   GitUpdate.cmake invokes python ${Svg_SOURCE_DIR}/gitupdate.py
#   to pull all submodules and update to head.
#   If this fails, it will attempt to invoke git directly to pull 
#   submodules. 
list(APPEND CMAKE_MODULE_PATH 
  ${Svg_SOURCE_DIR}/CMake 
  ${Svg_SOURCE_DIR}/CMake/Modules
)
include(Configure)
if (NOT Configure_SUCCEEDED)
   return()
endif()



if (Svg_ExternalTarget)
    set(TargetFolders ${Svg_TargetFolders})
    set(TargetName    ${Svg_TargetName})
    set(TargetGroup   ${Svg_TargetGroup})
else()
    add_subdirectory(CMake)

    set(TargetFolders TRUE)
    set(TargetName Svg)
    set(TargetGroup )

    set(Svg_INCLUDE  ${Svg_SOURCE_DIR})
    set(Svg_LIBRARY  ${TargetName})
endif()

add_subdirectory(Svg)

if (Svg_BUILD_TEST)
    if (NOT Svg_ExternalTarget)
        add_gtest_source(Extern/ThirdParty)
    endif()

    set(TargetGroup Units)
    add_subdirectory(Test)
endif()
