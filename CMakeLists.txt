cmake_minimum_required (VERSION 3.20)

project (CetoneOrg
    VERSION 1.0.0
    LANGUAGES C CXX
)

# Explicitily specify C++ standard to prevent build error on Github CI - macOS build
set (CMAKE_CXX_STANDARD 17)

add_subdirectory (DPF)

include_directories (
    Sources/
    .
)

dpf_add_plugin (${PROJECT_NAME}
    TARGETS vst2 vst3 lv2 clap jack
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
