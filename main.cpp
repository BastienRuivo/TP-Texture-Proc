#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "EfrosLeung.h"


int main(int argc, char** argv) {
    if (argc != 5) {
        std::cout << "Usage: " << argv[0] << " <image> <patch size> <res> <seed>" << std::endl;
        return 1;
    }
    auto name = argv[1];
    auto patchSize = atoi(argv[2]);
    auto res = atoi(argv[3]);
    auto seed = atoi(argv[4]);
    EfrosLeung efrosLeung(name, patchSize, res, res, seed);
    efrosLeung.run();
    cv::imwrite("result.png", efrosLeung.getTarget());
    efrosLeung.show();
    return 0;
}