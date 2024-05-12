include(${CMAKE_SOURCE_DIR}/cmake/warnings.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/sanitizers.cmake)

# the following function was taken from:
# https://github.com/cpp-best-practices/cmake_template/blob/main/ProjectOptions.cmake
macro(check_sanitizer_support)
    if ((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
        set(supports_ubsan ON)
    else ()
        set(supports_ubsan OFF)
    endif ()

    if ((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
        set(supports_asan OFF)
    else ()
        set(supports_asan ON)
    endif ()
endmacro()

check_sanitizer_support()

if (PROJECT_IS_TOP_LEVEL)
    option(cpt_lib_warnings_as_errors "Treat warnings as errors" ON)
    option(cpt_lib_enable_undefined_behavior_sanitizer "Enable undefined behavior sanitizer" ${supports_ubsan})
    option(cpt_lib_enable_address_sanitizer "Enable address sanitizer" ${supports_asan})
    option(cpt_lib_tests "Build tests using Google Test" ON)
else ()
    option(cpt_lib_warnings_as_errors "Treat warnings as errors" OFF)
    option(cpt_lib_enable_undefined_behavior_sanitizer "Enable undefined behavior sanitizer" OFF)
    option(cpt_lib_enable_address_sanitizer "Enable address sanitizer" OFF)
    option(cpt_lib_tests "Build tests using Google Test" OFF)
endif ()

add_library(cpt_lib_warnings INTERFACE)
set_warnings(cpt_lib_warnings ${cpt_lib_warnings_as_errors})

add_library(cpt_lib_sanitizers INTERFACE)
enable_sanitizers(cpt_lib_sanitizers ${cpt_lib_enable_address_sanitizer} ${cpt_lib_enable_undefined_behavior_sanitizer})

add_library(cpt_lib_project_options INTERFACE
            lib/NotUsedYet.cpp)
target_link_libraries(cpt_lib_project_options
                      INTERFACE cpt_lib_warnings
                      INTERFACE cpt_lib_sanitizers
)