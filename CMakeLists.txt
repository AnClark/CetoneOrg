cmake_minimum_required (VERSION 3.20)

project (CetoneOrg
    VERSION 1.0.0
    LANGUAGES C CXX
)

# Metadata (for CPack)
set (AUTHOR "AnClark Liu")
set (INSTALL_DIRECTORY ${PROJECT_NAME})
set (PRODUCTBUILD_IDENTIFIER "com.anclark.cetone.org")

# Explicitily specify C++ standard to prevent build error on Github CI - macOS build
set (CMAKE_CXX_STANDARD 17)

# Build options
option (CETONE_BUILD_JACK_STANDALONE "Build JACK standalone version" OFF)
if (CETONE_BUILD_JACK_STANDALONE)
    set (TARGET_JACK jack)
endif ()

# GitHub CI's Ubuntu runner cannot directly run lv2-ttl-generator.exe, even though Wine and wine-binfmt is installed.
# And, LV2 is not so common on Windows (only REAPER, Ardour and Harrison Mixbus support LV2 on Windows).
# So disable LV2 on Windows by default.
option (CONFIG_BUILD_LV2_ON_WINDOWS "Build LV2 on Windows (including cross-compiling)." OFF)
if (WIN32 AND CONFIG_BUILD_LV2_ON_WINDOWS)
    message (STATUS "Win32 environment and LV2 build is enabled, will build LV2 plugin")
    set (TARGET_LV2 lv2)
elseif (WIN32)
    message (STATUS "Win32 environment and LV2 build is disabled. Bypass LV2")
else ()
    message (STATUS "Non-Win32 environment, will build LV2 plugin")
    set (TARGET_LV2 lv2)
endif ()

# Generate dynamic metadata file
configure_file (cmake/metadata.h.in ${PROJECT_BINARY_DIR}/metadata.gen.h @ONLY)

add_subdirectory (DPF)

include_directories (
    Sources/
    .
    ${PROJECT_BINARY_DIR}
)

dpf_add_plugin (${PROJECT_NAME}
    TARGETS vst2 vst3 ${TARGET_LV2} clap ${TARGET_JACK}
    FILES_DSP
        Sources/CetoneOrg.cpp
        Sources/CetoneOrgDPF.cpp
        Sources/statics.cpp
        Sources/Synth.cpp
    #FILES_UI
    #    Sources/CetoneUI.cpp
    #    Sources/CetoneUIHelper.cpp
    #    Images/CetoneArtwork.cpp
    #    Fonts/CetoneFonts.cpp
)

# CPack stuff
include (cmake/Packaging.cmake)
