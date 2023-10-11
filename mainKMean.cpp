#include <iostream>



#include <fstream>

#include "KMean.h"
#include "GradientHistogram.h"


int main(void) {
    srand(42);
    std::vector<KMeanPoint<16>> pointsToTrain;
    std::vector<KMeanPoint<16>> pointsToTest;
    std::vector<int> pointsToTrainImageIndex;
    std::vector<int> pointsToTestImageIndex;
    size_t nbImages = 112;
    int patchSize = 64;
    for(size_t imId = 1; imId <= nbImages; imId++) {
        std::cout<<"loading image " << imId <<" / " <<nbImages<<std::endl;
        cv::Mat img = cv::imread("../classification/D" + std::to_string(imId) + "_COLORED.tif", cv::IMREAD_COLOR);
        cv::Mat sobelx = cv::Mat::zeros(img.size(), CV_32F);
        cv::Mat sobely = cv::Mat::zeros(img.size(), CV_32F);
        cv::Sobel(img, sobelx, CV_32F, 1, 0);
        cv::Sobel(img, sobely, CV_32F, 0, 1);
        for(int i = 0; i < img.rows - patchSize; i+=patchSize) {
            for(int j = 0; j < img.cols - patchSize; j+=patchSize) {
                cv::Mat patchx = sobelx(cv::Rect(j, i, patchSize, patchSize));
                cv::Mat patchy = sobely(cv::Rect(j, i, patchSize, patchSize));
                GradientHistogram<16> hist;
                hist.fillHistogram(patchx, patchy);
                KMeanPoint<16> point(hist.getHistogram());
                if(rand() % 100 < 70) {
                    pointsToTrain.push_back(point);
                    pointsToTrainImageIndex.push_back(imId);
                } else {
                    pointsToTest.push_back(point);
                    pointsToTestImageIndex.push_back(imId);
                }
            }
        }
    }
    


    KMean<16> kmean(112, pointsToTrain);
    kmean.init();
    kmean.run();

    // open predicted.csv
    std::ofstream file;
    file.open("../predicted.csv");
    file << "idImage,patchId,clusterId" << std::endl;
    for(int i = 0; i < pointsToTest.size(); i++) {
        auto cluster = kmean.predict(pointsToTest[i]);
        file << pointsToTestImageIndex[i] << "," << i << "," << cluster << std::endl;
    }
    file.close();

    // open train.csv
    file.open("../train.csv");
    file << "idImage,patchId,clusterId" << std::endl;
    for(int i = 0; i < pointsToTrain.size(); i++) {
        auto cluster = kmean.getCentroid(i);
        file << pointsToTrainImageIndex[i] << "," << i << "," << cluster << std::endl;
    }
    file.close();


    return 0;
}