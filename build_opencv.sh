#!/bin/bash -e

CMAKE_CMD=cmake
GIT_CMD=git

SOURCE_PATH=${1:-"/tmp"} # download to /tmp or specify one with first argument
INSTALL_PATH=${2:-"/usr/lib"} # install in /usr/lib or specify with second argument

OPENCV_NAME="opencv"
OPENCV_VERSION=4.5.3
OPENCV_MODULES="aruco"
CVCONTRIB_DIR="opencv_contrib"
BUILD_DIR="build"

CMAKE_OPTS=\
(-DBUILD_TESTS:BOOL=OFF -DBUILD_PERF_TESTS:BOOL=OFF \
-DOPENCV_EXTRA_MODULES_PATH="../${CVCONTRIB_DIR}/modules" \
-DINSTALL_CREATE_DISTRIB=ON \
-DCMAKE_INSTALL_PREFIX="${INSTALL_PATH}/${OPENCV_NAME}")

cd "$SOURCE_PATH"
if [[ ! -d "$OPENCV_NAME" ]]; then
    $GIT_CMD clone --config advice.detachedHead=false \
              --filter=tree:0 \
              --depth 1 \
              --branch "$OPENCV_VERSION" \
              "https://github.com/opencv/opencv" \
              "$OPENCV_NAME" \
              || exit 1
fi

cd "$OPENCV_NAME"
if [[ ! -d "$CVCONTRIB_DIR" ]]; then
    $GIT_CMD clone --no-checkout \
              --sparse \
              --filter=tree:0 \
              --depth 1 \
              --branch $OPENCV_VERSION \
              "https://github.com/opencv/opencv_contrib" \
              "$CVCONTRIB_DIR" \
              || exit 1
fi

cd "$CVCONTRIB_DIR"
$GIT_CMD sparse-checkout init
$GIT_CMD sparse-checkout set
for mod in $OPENCV_MODULES; do
    $GIT_CMD sparse-checkout add "/modules/${mod}/*" || exit 1
done
$GIT_CMD checkout
cd ..

[[ ! -d "$BUILD_DIR" ]] && mkdir "$BUILD_DIR"

cd "$BUILD_DIR" && \
    $CMAKE_CMD "${CMAKE_OPTS[@]}" -S .. && \
    $CMAKE_CMD --build . --config release && \
    $CMAKE_CMD --build . --config debug && \
    $CMAKE_CMD --build . --target install --config release && \
    $CMAKE_CMD --install . --target install --config debug 