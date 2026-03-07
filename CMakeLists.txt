cmake_minimum_required(VERSION 3.20)
project(QuantTradingEngine VERSION 1.0.0 LANGUAGES CXX)

# ============================================================================
# CMAKE CONFIGURATION
# ============================================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable compiler warnings
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# ============================================================================
# DIRECTORIES
# ============================================================================
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# ============================================================================
# SOURCE FILES
# ============================================================================
set(SOURCES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/EuropeanOption.cpp
    ${SOURCE_DIR}/EuropeanCall.cpp
    ${SOURCE_DIR}/EuropeanPut.cpp
)

# ============================================================================
# EXECUTABLE
# ============================================================================
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})

# ============================================================================
# COMPILER FEATURES
# ============================================================================
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Math library (if needed on some systems)
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE m)
endif()

# ============================================================================
# OUTPUT DIRECTORY
# ============================================================================
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# ============================================================================
# OPTIONAL: INSTALL TARGETS (for system installation)
# ============================================================================
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY ${INCLUDE_DIR}/ DESTINATION include)
