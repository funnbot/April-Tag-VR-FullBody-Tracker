#pragma once
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/aruco.hpp>
#include "Quaternion.h"

//#include "Language_English.h"
#include "Language.h"

const bool USE_UDP = true;

class Parameters
{
public:
    std::string version = "0.5.5";
    std::string driverversion = "0.5.5";

    Parameters();
    void Load();
    void Save();
    std::string cameraAddr = "0";
    int cameraApiPreference = 0;
    cv::Mat camMat;
    cv::Mat distCoeffs;
    cv::Mat stdDeviationsIntrinsics;
    std::vector<double> perViewErrors;
    std::vector<std::vector<cv::Point2f>> allCharucoCorners;
    std::vector<std::vector<int>> allCharucoIds;
    std::vector<cv::Ptr<cv::aruco::Board>> trackers;
    int trackerNum = 1;
    double markerSize = 0.05;
    int numOfPrevValues = 5;
    double quadDecimate = 1;
    double searchWindow = 0.25;
    bool usePredictive = true;
    int calibrationTracker = 0;
    bool ignoreTracker0 = false;
    bool rotateCl = false;
    bool rotateCounterCl = false;
    bool coloredMarkers = true;
    double calibOffsetX = 0;
    double calibOffsetY = 100;
    double calibOffsetZ = 100;
    double calibOffsetA = 180;
    double calibOffsetB = 0;
    double calibOffsetC = 0;
    bool circularWindow = true;
    double smoothingFactor = 0.5;
    int camFps = 30;
    int camHeight = 0;
    int camWidth = 0;
    cv::Mat wtranslation;
    Quaternion<double> wrotation;
    bool cameraSettings = false;
    bool chessboardCalib = false;
    double camLatency = 0;
    bool circularMarkers = false;
    double trackerCalibDistance = 0.5;
    int cameraCalibSamples = 15;
    bool settingsParameters = false;
    double cameraAutoexposure = 0;
    double cameraExposure = 0;
    double cameraGain = 0;
    bool trackerCalibCenters = false;
    float depthSmoothing = 0;
    float additionalSmoothing = 0;
    int markerLibrary = 0;
    int markersPerTracker = 45;
    int languageSelection = 0;
    double calibScale = 1;
    bool useApriltagIOS = false;


    cv::Ptr<cv::aruco::DetectorParameters> aruco_params = cv::aruco::DetectorParameters::create();

    Lang language;

};
