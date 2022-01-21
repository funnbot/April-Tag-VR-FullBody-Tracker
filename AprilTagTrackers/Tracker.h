﻿#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <math.h>

#include <opencv2/aruco.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include <WinSock2.h>

#include "MyApp.h"

#include "Quaternion.h"

constexpr bool NO_STEAM_MODE = true;

struct TrackerStatus {
    cv::Vec3d boardRvec, boardTvec, boardTvecDriver;
    bool boardFound, boardFoundDriver;
    std::vector<std::vector<double>> prevLocValues;
    cv::Point2d maskCenter;
};

struct UDP_Server {
    const int PORT = 7709;
    SOCKET socket;
    struct sockaddr_in addr;
    WSADATA wsa;

    std::mutex mutex;
    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners;
    std::vector<cv::Point2f> centers;
};

class Connection;
class GUI;
class Parameters;

class Tracker
{
public:
    Tracker(Parameters*, Connection*, MyApp*);
    void StartCamera(std::string id, int apiPreference);
    void StartCameraCalib();
    void StartTrackerCalib();
    void Start();

    bool mainThreadRunning = false;
    bool cameraRunning = false;
    bool previewCamera = false;
    bool previewCameraCalibration = false;
    bool showTimeProfile = false;
    bool recalibrate = false;
    bool manualRecalibrate = false;
    bool multicamAutocalib = false;
    bool lockHeightCalib = false;
    bool disableOut = false;

    UDP_Server server{};

    GUI* gui;

    cv::Mat wtranslation = (cv::Mat_<double>(4, 4) << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    Quaternion<double> wrotation = Quaternion<double>(1, 0, 0, 0);

    double calibScale = 1;

private:
    void CameraLoop();
    void CopyFreshCameraImageTo(cv::Mat& image);
    void CalibrateCamera();
    void CalibrateCameraCharuco();
    void CalibrateTracker();
    void MainLoop();

    int drawImgSize = 480;

    cv::VideoCapture cap;

    // cameraImage and imageReady are protected by cameraImageMutex.
    // Use CopyFreshCameraImageTo in order to get the latest camera image.
    std::mutex cameraImageMutex;
    cv::Mat cameraImage;
    bool imageReady = false;

    Parameters* parameters;
    Connection* connection;

    std::thread cameraThread;
    std::thread mainThread;

    std::vector<cv::Ptr<cv::aruco::Board>> trackers;
    bool trackersCalibrated = false;

    //Quaternion

    //Quaternion<double> q;

    clock_t last_frame_time;

    MyApp* parentApp;
};
