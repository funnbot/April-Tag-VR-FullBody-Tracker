# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("AprilTagTrackers")

#only supported for now
set(PLATFORM_NAME "win")
set(PROCESSOR_ARCH "64")

set(wxBUILD_SHARED "0" CACHE BOOL "")
set(BUILD_SHARED_LIBS "0" CACHE BOOL "")

# Find prebuilt libraries
find_package(OpenCV REQUIRED PATHS "opencv/build/install")
#    OpenVR does not include any generated cmake files, but the paths are always known
find_library(OpenVRSDK openvr_api REQUIRED PATHS "${CMAKE_CURRENT_SOURCE_DIR}/openvr/lib/${PLATFORM_NAME}${PROCESSOR_ARCH}" NO_DEFAULT_PATH)
set(OPENVR_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/openvr/headers")

# Find libraries to build
add_subdirectory("apriltag")
set(APRILTAG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/apriltag")
add_subdirectory("wxWidgets")
add_subdirectory("AprilTagTrackers")

install(TARGETS AprilTagTrackers RUNTIME DESTINATION bin)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT AprilTagTrackers)
set_target_properties("AprilTagTrackers" PROPERTIES LINK_FLAGS /SUBSYSTEM:WINDOWS )
