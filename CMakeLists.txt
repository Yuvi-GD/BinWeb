cmake_minimum_required(VERSION 3.10)
project(NativeWebApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories to match user expectations (build/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# --- 1. Build the Asset Embedder Tool ---
add_executable(embedder tools/embedder.cpp)

# --- 2. Define Paths ---
set(WEB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/web")
set(GENERATED_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/core/web_content.h")

# --- 3. Run Embedder Pre-Build ---
add_custom_command(
    OUTPUT ${GENERATED_HEADER}
    COMMAND embedder "${WEB_DIR}" "${GENERATED_HEADER}"
    DEPENDS embedder "${WEB_DIR}/index.html"
    COMMENT "Embedding web assets into C++ header..."
)

# --- 4. Main Application ---
# Add the webview library
add_subdirectory(libs/webview)

# Define source files
set(SOURCES 
    platform/windows/main.cpp
    core/NativeApp.cpp
    ${GENERATED_HEADER} # Add generated header to sources to trigger generation
)

add_executable(NativeWebApp ${SOURCES})

# Link libraries
target_link_libraries(NativeWebApp PRIVATE webview::core_static)

# Include directories
target_include_directories(NativeWebApp PRIVATE 
    libs/webview/core/include
    core
)

# Windows-specific settings
if(WIN32)
    target_compile_definitions(NativeWebApp PRIVATE WEBVIEW_EDGE)
    set_target_properties(NativeWebApp PROPERTIES WIN32_EXECUTABLE ON)
endif()