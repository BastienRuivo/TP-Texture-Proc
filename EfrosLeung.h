#pragma once

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>

class EfrosLeung
{
private:
    cv::Mat img;
    cv::Mat target;
    cv::Mat mask;
    cv::Mat distances;
    int patchSize;
    int targetWidth, targetHeight;
    int seed;

    cv::Point2i aa;
    cv::Point2i bb;

    void init();
    cv::Point2i selectPixel();
    cv::Point2i selectPatch(const cv::Point2i& pixel);

    int getNeighborhood(int i, int j);
    int getDistance(int i, int j, const cv::Point2i& pixel);
    void color(const cv::Point2i& pixel, const cv::Point2i& patch);

public:
    const float EPSILON = 0.5f;
    EfrosLeung(const std::string& path, int patchSize, int targetWidth, int targetHeight, int seed = 42);
    void run();
    void show();
    cv::Mat getTarget() const;
    ~EfrosLeung() {}
};