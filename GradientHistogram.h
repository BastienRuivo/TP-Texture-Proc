#pragma once
#include <vector>
#include <array>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

template<int dim>
class GradientHistogram
{
private:
    std::array<float, dim> histogram;
public:
    GradientHistogram() {
        histogram.fill(0);
    }

    float getHistogram(int i) const {
        return histogram[i];
    }

    void fillHistogram(const cv::Mat & imx, const cv::Mat & imy) {
        const float inv = 1.0 / (2.0 * M_PI * dim);
        for (int y = 0; y < imx.rows; y++)
        {
            for (int x = 0; x < imy.cols; x++)
            {
                float gx = (imx.at<float>(y, x, 0));
                float gy = (imy.at<float>(y, x, 0));
                float angle = atan2(gy, gx);
                int i = (angle + M_PI) / (2.0 * M_PI) * dim;
                histogram[i]++;
            }
        }

    }
    
    ~GradientHistogram() {

    }

    friend std::ostream& operator<<(std::ostream& os, const GradientHistogram<dim>& hist) {
        for (size_t i = 0; i < dim; i++)
        {
            os << hist.histogram[i] << " ";
        }
        return os;
    }
};
