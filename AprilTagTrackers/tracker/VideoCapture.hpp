#pragma once

#include "config/VideoStream.hpp"
#include "RefPtr.hpp"
#include "utils/SteadyTimer.hpp"

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include <condition_variable>
#include <memory>
#include <mutex>

namespace tracker
{

struct CapturedFrame
{
    cv::Mat image;
    utils::SteadyTimer::TimePoint timestamp;
};

inline void swap(CapturedFrame& lhs, CapturedFrame& rhs) // NOLINT(*-naming)
{
    using std::swap;
    swap(lhs.image, rhs.image);
    swap(lhs.timestamp, rhs.timestamp);
}

class AwaitedFrame
{
public:
    void Set(CapturedFrame& inFrame)
    {
        { // lock scope
            std::lock_guard lock(mMutex);
            swap(inFrame, mFrame);
            mIsReady = true;
        }
        mReadyCond.notify_one();
    }
    void Get(CapturedFrame& outFrame)
    {
        std::unique_lock lock{mMutex};
        mReadyCond.wait(lock, [&] { return mIsReady; });

        mIsReady = false;
        swap(mFrame, outFrame);
    }

private:
    CapturedFrame mFrame{};
    std::mutex mMutex{};
    std::condition_variable mReadyCond{};
    bool mIsReady = false;
};

class VideoCapture
{
public:
    /// fake api for user to specify custom ps3eye capture implementation
    /// must not conflict with existing cv::VideoCapture api
    static constexpr int CAP_PS3EYE = 9100;

    /// instance is linked to a CameraInfo, so a list of VideoCaptures will sync with the list of cameras in gui
    explicit VideoCapture(RefPtr<cfg::Camera> cameraInfo) : mCameraInfo(cameraInfo) {}

    bool TryOpen();
    void Close();
    /// blocks till frame is ready, matches fps of camera
    bool TryReadFrame(cv::Mat& outImage);
    bool IsOpen() const { return mCapture && mCapture->isOpened(); }

private:
    bool TryOpenCapture();
    bool TryOpenGStreamerCapture(int index);
    void SetCaptureOptions();
    void LogCaptureOptions();

    RefPtr<cfg::Camera> mCameraInfo;
    std::unique_ptr<cv::VideoCapture> mCapture = std::make_unique<cv::VideoCapture>();
};

} // namespace tracker
