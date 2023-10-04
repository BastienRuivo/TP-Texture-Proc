#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <fstream>

#include "KMean.h"

int main(void) {
    srand(42);

    std::vector<KMeanPoint<2>> points;

    std::vector<KMeanPoint<2>> center;

    center.push_back(KMeanPoint<2>({0.25,0.25}));
    center.push_back(KMeanPoint<2>({0.25,0.75}));
    center.push_back(KMeanPoint<2>({0.75,0.25}));
    center.push_back(KMeanPoint<2>({0.75,0.75}));

    for (size_t i = 0; i < 100; i++)
    {
        for (size_t j = 0; j < center.size(); j++)
        {
            points.push_back(center[j] + (KMeanPoint<2>::random() / 4.0) - KMeanPoint({0.125,0.125}));
        }
    }

    Plot2D plot;
    // Set the x and y labels
    plot.xlabel("x");
    plot.ylabel("y");

    // Set the x and y ranges
    plot.xrange(0.0, 1.0);
    plot.yrange(0.0, 1.0);

    // Set the legend to be on the bottom along the horizontal
    plot.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);

    // Plot the data
    std::vector<float> x(points.size());
    std::vector<float> y(points.size());
    for (size_t i = 0; i < points.size(); i++)
    {
        x[i] = points[i].coord[0];
        y[i] = points[i].coord[1];
        //std::cout<<"v = {" << x[i] << " " << y[i] << " } "<<std::endl;
        //plot.drawPoints(points.coord, points).pointType(0);
    }

    plot.drawPoints(x, y).pointType(0);

    Figure fig = {{plot}};
    Canvas canvas = {{fig}};

    canvas.show();
    

    return 0;
}