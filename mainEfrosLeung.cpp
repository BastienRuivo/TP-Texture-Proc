#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <fstream>

#include "EfrosLeung.h"


int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <image> <seed>" << std::endl;
        return 1;
    }
    auto name = argv[1];
    auto seed = atoi(argv[2]);
    std::vector<int> patchSizes = {9};
    std::vector<int> resSizes = {96};
    int nbTests = 1;
    srand(seed);
    // open file res.csv
    // write header which are patch size, res, time

    std::ofstream file;
    file.open("res.csv");
    file << "Resolution,Patch,Time" << std::endl;
    std::cout<<"Begin computations..."<<std::endl;
    for(int j = 0; j < patchSizes.size(); j++) {
        for(int i = 0; i < resSizes.size(); i++) {
            int64 totalTime = 0;
            for(int k = 0; k < nbTests; k++) {
                EfrosLeung efrosLeung(name, patchSizes[j], resSizes[i], resSizes[i], seed);
                totalTime += efrosLeung.run();
                std::cout<<"Patch size "<<patchSizes[j]<<" Res "<<resSizes[i]<<" Test "<<k<< " Time "<<totalTime<<std::endl;
                auto res = efrosLeung.getTarget();
                if(k == 0)cv::imwrite(std::string(name) + std::string("_") +std::to_string(patchSizes[j])+"_"+std::to_string(resSizes[i])+"_"+std::to_string(k)+".png", res);
            }
            file << resSizes[i] << "," << patchSizes[j] << "," << (totalTime/nbTests)<< std::endl;
        }
    }
    file.close();
    std::cout<<"End computations..."<<std::endl;
    return 0;
}