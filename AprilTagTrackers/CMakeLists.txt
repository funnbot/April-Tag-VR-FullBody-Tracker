# CMakeList.txt : CMake project for AprilTagTrackers, include source and define
# project specific logic here.
#

# Add source to this project's executable.
file(GLOB attSOURCE "*.cpp" "*.h")
add_executable(AprilTagTrackers ${attSOURCE})

target_include_directories(AprilTagTrackers PUBLIC ${OPENVR_INCLUDE_DIR} ${APRILTAG_INCLUDE_DIR})
target_link_libraries(AprilTagTrackers ${OpenCV_LIBS} ${OpenVRSDK} apriltag wx::net wx::core wx::base)