﻿#pragma once

#pragma warning(push)
#pragma warning(disable:4996)
#include <wx/wx.h>
#pragma warning(pop)

#include "Config.h"
#include "Localization.h"

class Connection;
class GUI;
class Parameters;
class Tracker;

class MyApp : public wxApp
{
    Tracker* tracker;
    Connection* conn;
    GUI* gui;

    // Various configs exist for duration of app
    // Other classes should only use these as (const) references.
    UserConfig user_config;
    CalibrationConfig calib_config;
    ArucoConfig aruco_config;
    Localization lcl = Localization(user_config.langId);

public:
    virtual int OnExit() wxOVERRIDE;
    virtual bool OnInit() wxOVERRIDE;
    void ButtonPressedCamera(wxCommandEvent&);
    void ButtonPressedCameraPreview(wxCommandEvent&);
    void ButtonPressedCameraCalib(wxCommandEvent&);
    void ButtonPressedCameraCalibPreview(wxCommandEvent&);
    void ButtonPressedTimeProfile(wxCommandEvent&);
    void ButtonPressedConnect(wxCommandEvent&);
    void ButtonPressedTrackerCalib(wxCommandEvent&);
    void ButtonPressedStart(wxCommandEvent&);
    void ButtonPressedSpaceCalib(wxCommandEvent&);
    void ButtonPressedMulticamAutocalib(wxCommandEvent&);
    void ButtonPressedLockHeight(wxCommandEvent&);
    void ButtonPressedDisableOut(wxCommandEvent&);
    void ButtonPressedDisableOpenVrApi(wxCommandEvent&);
};
