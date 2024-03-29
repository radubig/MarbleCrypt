cmake_minimum_required(VERSION 3.20)

project(MarbleCrypt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

# disable sanitizers when releasing executables without explicitly requested debug info
# use generator expressions to set flags correctly in both single and multi config generators
set(is_debug "$<CONFIG:Debug>")
set(is_rel_with_deb "$<CONFIG:RelWithDebInfo>")
set(debug_mode "$<OR:${is_debug},${is_rel_with_deb}>")

###############################################################################

# custom functions

function(set_custom_stdlib_and_sanitizers target add_apple_asan)
    if(MSVC)
        target_compile_options(${target} PRIVATE "$<${debug_mode}:/fsanitize=address>")
        return()
    endif()

    if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        target_compile_options(${target} PRIVATE -stdlib=libc++)
        target_link_options(${target} PRIVATE -stdlib=libc++)
    endif()

    if(APPLE)
        # first check Apple since Apple is also a kind of Unix
        if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" AND add_apple_asan MATCHES true)
            target_compile_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=address,undefined>")
            target_link_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=address,undefined>")
        endif()
    elseif(UNIX)
        if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
            if("${CMAKE_CXX_COMPILER_VERSION}" MATCHES "12.")
                # check leaks on Linux since macOS does not support the leaks sanitizer yet
                # leaks sanitizer is enabled by default on Linux, so we do not need to enable it explicitly
                target_compile_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=address,undefined>")
                target_link_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=address,undefined>")
            elseif("${CMAKE_CXX_COMPILER_VERSION}" MATCHES "13.")
                # use semi-colons instead of spaces to separate arguments
                # it is recommended to quote generator expressions in order to avoid unintentional splitting
                target_compile_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=memory,undefined;-fsanitize-recover=memory,undefined;-fsanitize-memory-track-origins>")
                target_link_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=memory,undefined;-fsanitize-recover=memory,undefined;-fsanitize-memory-track-origins;-Wl,-rpath,tools/llvm-project/build/lib>")
            else()
                message("No matching Clang version to add sanitizer flags!")
            endif()
        endif()
    endif()
endfunction()

###############################################################################

# external dependencies with FetchContent
include(FetchContent)

# NOTE: Also update env vars used for caching in .github/workflows/cmake.yml
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        863fef024619da7f59b6404087b454337a172ac1 # 2.6.x as of 2022-08-30
)

FetchContent_MakeAvailable(SFML)

set_custom_stdlib_and_sanitizers(sfml-system false)
set_custom_stdlib_and_sanitizers(sfml-window false)
set_custom_stdlib_and_sanitizers(sfml-graphics false)

###############################################################################

# external dependencies with find_package

find_package(Threads REQUIRED)
if(APPLE)
elseif(UNIX)
    find_package(X11)
endif()

###############################################################################

# Custom include commands
file(GLOB_RECURSE Src "src/*")
add_executable(${PROJECT_NAME} ${Src})
target_include_directories(${PROJECT_NAME} PRIVATE include)

###############################################################################

# target definitions

if(GITHUB_ACTIONS)
  message("NOTE: GITHUB_ACTIONS defined")
  target_compile_definitions(${PROJECT_NAME} PRIVATE GITHUB_ACTIONS)
endif()

###############################################################################

if(WARNINGS_AS_ERRORS)
    set_property(TARGET ${PROJECT_NAME} PROPERTY COMPILE_WARNING_AS_ERROR ON)
endif()

# custom compiler flags
message("Compiler: ${CMAKE_CXX_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION}")
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive- /wd4244 /wd4267 /wd4996 /external:anglebrackets /external:W0)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

###############################################################################

# sanitizers
set_custom_stdlib_and_sanitizers(${PROJECT_NAME} true)

###############################################################################

# use SYSTEM so clang-tidy does not report warnings from these directories
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${SFML_SOURCE_DIR}/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system Threads::Threads)

if(APPLE)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} X11)
endif()

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# update name in .github/workflows/cmake.yml:29 when changing "bin" name here
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY data DESTINATION bin)
