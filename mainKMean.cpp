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
    int patchSize = 128;
    for(size_t imId = 1; imId <= nbImages; imId++) {
        std::cout<<"loading image " << imId <<" / " <<nbImages<<std::endl;
        cv::Mat input = cv::imread("../classification/D" + std::to_string(imId) + "_COLORED.tif");
        cv::Mat input2 = input.clone();
        cv::Mat sobelx = cv::Mat::zeros(input.size(), CV_32F);
        cv::Mat sobely = cv::Mat::zeros(input.size(), CV_32F);
        cv::Sobel(input, sobelx, CV_32F, 1, 0);
        cv::Sobel(input, sobely, CV_32F, 0, 1);

        auto sx = sobelx.clone();
        auto sy = sobely.clone();
        
        for(int i = 0; i < input.rows - patchSize; i+=patchSize) {
            for(int j = 0; j < input.cols - patchSize; j+=patchSize) {
                auto roi = cv::Rect(j, i, patchSize, patchSize);
                GradientHistogram<16> hist;
                hist.fillHistogram(sx(roi), sy(roi));
                KMeanPoint<16> point(hist);
                cv::waitKey(0);
                if(rand() % 100 < 70) {
                    pointsToTrain.push_back(point);
                    pointsToTrainImageIndex.push_back(imId);
                } else {
                    pointsToTest.push_back(point);
                    pointsToTestImageIndex.push_back(imId);
                    cv::imwrite("../patches/D" + std::to_string(imId) + "_" + std::to_string(i) + "_" + std::to_string(j) + ".png", input2(roi));
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
    std::vector<cv::Mat> mats = {
        cv::imread("../patches/D1_0_256.png_27_128_0.png"),
        cv::imread("../patches/D2_0_256.png_27_128_0.png"),
        cv::imread("../patches/D3_0_384.png_27_128_0.png")
    };
    std::vector<cv::Mat> mats2 = {
        cv::imread("../patches/D1_NOISED.png"),
        cv::imread("../patches/D2_NOISED.png"),
        cv::imread("../patches/D3_NOISED.png")
    };
    

    for (size_t i = 0; i < mats.size(); i++)
    {
        // sobel
        cv::Mat sobelx = cv::Mat::zeros(mats[i].size(), CV_32F);
        cv::Mat sobely = cv::Mat::zeros(mats[i].size(), CV_32F);
        cv::Sobel(mats[i], sobelx, CV_32F, 1, 0);
        cv::Sobel(mats[i], sobely, CV_32F, 0, 1);
        // histogram
        GradientHistogram<16> hist;
        hist.fillHistogram(sobelx, sobely);
        // kmean
        auto cluster = kmean.predict(KMeanPoint<16>(hist));

        // NOISED
        cv::Mat sobelx2 = cv::Mat::zeros(mats2[i].size(), CV_32F);
        cv::Mat sobely2 = cv::Mat::zeros(mats2[i].size(), CV_32F);
        cv::Sobel(mats2[i], sobelx2, CV_32F, 1, 0);
        cv::Sobel(mats2[i], sobely2, CV_32F, 0, 1);
        // histogram
        GradientHistogram<16> hist2;
        hist2.fillHistogram(sobelx2, sobely2);
        // kmean
        auto cluster2 = kmean.predict(KMeanPoint<16>(hist2));

        // Noised Blurred
        auto Blur = mats2[i].clone();
        cv::GaussianBlur(mats2[i], Blur, cv::Size(3, 3), 0, 0);
        cv::Mat sobelx3 = cv::Mat::zeros(Blur.size(), CV_32F);
        cv::Mat sobely3 = cv::Mat::zeros(Blur.size(), CV_32F);
        cv::Sobel(Blur, sobelx3, CV_32F, 1, 0);
        cv::Sobel(Blur, sobely3, CV_32F, 0, 1);
        // histogram
        GradientHistogram<16> hist3;
        hist3.fillHistogram(sobelx3, sobely3);
        // kmean
        auto cluster3 = kmean.predict(KMeanPoint<16>(hist3));

        cv::imwrite("../patches/D" + std::to_string(i+1) + "_NOISED_BLURRED.png", Blur);
        

        std::cout << "Generated " << cluster << " noised " << cluster2 << " noised + blurred " << cluster3 << std::endl;
    }
    


    return 0;
}