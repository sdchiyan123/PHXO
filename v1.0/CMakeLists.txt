cmake_minimum_required(VERSION 3.20)
project(PHXO VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ===== CEF 154 路径 =====
set(CEF_ROOT "D:/CEF/cef_binary_154.0.34+g14c5a08+chromium-154.0.8037.98_windows64")

list(APPEND CMAKE_MODULE_PATH "${CEF_ROOT}/cmake")
find_package(CEF REQUIRED)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(PHXO_SOURCES
    phxo_app.cc
    phxo_handler.cc
    phxo_handler_win.cc
    phxo_win.cc
)

add_executable(PHXO WIN32 ${PHXO_SOURCES})

target_link_directories(PHXO PRIVATE
    "${CEF_ROOT}/build/libcef_dll_wrapper/Release"
    "${CEF_ROOT}/Release"
)

target_link_libraries(PHXO PRIVATE
    libcef_dll_wrapper
    libcef
    ${CEF_STANDARD_LIBS}
)

target_include_directories(PHXO PRIVATE "${CEF_ROOT}")

target_compile_options(PHXO PRIVATE /utf-8)

target_compile_definitions(PHXO PRIVATE
    NOMINMAX
    WIN32_LEAN_AND_MEAN
    UNICODE
    _UNICODE
    _HAS_EXCEPTIONS=0
    __STDC_CONSTANT_MACROS
    __STDC_FORMAT_MACROS
    CEF_API_VERSION=CEF_API_VERSION_LAST
)