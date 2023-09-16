#include "EfrosLeung.h"

#include <iostream>
#include <chrono>

EfrosLeung::EfrosLeung(const std::string& path, int patchSize, int targetWidth, int targetHeight, int seed)
    : patchSize(patchSize), targetWidth(targetWidth), targetHeight(targetHeight), seed(seed)
{
    img = cv::imread(path, cv::IMREAD_COLOR);
    if (img.empty()) {
        //std::cout << "Could not read the image: " << std::endl;
        exit(1);
    }
    this->patchSize = patchSize;
    this->targetWidth = targetWidth;
    this->targetHeight = targetHeight;

    init();
}

void EfrosLeung::init()
{
    target = cv::Mat(targetHeight, targetWidth, CV_8UC3, cv::Scalar(0, 0, 0));
    mask = cv::Mat::zeros(targetHeight, targetWidth, CV_8UC1);
    distances = cv::Mat(img.rows, img.cols, CV_32SC1);
    srand(seed);
    // choose a random patch from the image and place it at the middle

    cv::Point2i patch;
    patch.x = rand() % (img.cols - patchSize/2) + patchSize/2;
    patch.y = rand() % (img.rows - patchSize/2) + patchSize/2;

    // Copy the patch to the target image and fill the mask with 1
    cv::Rect roi(patch.x - patchSize/2, patch.y - patchSize/2, patchSize, patchSize);
    cv::Mat patchImg = img(roi);
    cv::Rect targetRoi(targetWidth/2 - patchSize/2, targetHeight/2 - patchSize/2, patchSize, patchSize);
    patchImg.copyTo(target(targetRoi));

    // fill the mask with 1
    for (int i = targetWidth/2 - patchSize/2; i < targetWidth/2 + patchSize/2 + 1; i++)
    {
        for (int j = targetHeight/2 - patchSize/2; j < targetHeight/2 + patchSize/2 + 1; j++)
        {
            mask.at<uchar>(i, j) = 1;
        }
    }
}

void EfrosLeung::run() {
    cv::Point2i pixel;
    cv::Point2i patch;
    auto begin = std::chrono::high_resolution_clock::now();
    auto previous = begin;
    int n = 0;
    int nb = targetWidth * targetHeight - patchSize * patchSize - 1;
    for (int i = 0; i < targetWidth * targetHeight - patchSize * patchSize; i++)
    {
        pixel = selectPixel();
        patch = selectPatch(pixel);
        if(i%targetWidth == 0) {
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            auto elapsedSincePrevious = std::chrono::duration_cast<std::chrono::milliseconds>(end - previous);
            previous = end;
            std::cout << "Iteration " << i << " / " << nb << " :: " << elapsed.count() << " ms" << " :: " << elapsedSincePrevious.count() << " ms" << std::endl;
        }
        color(pixel, patch);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "Total time : " << elapsed.count() << " ms" << std::endl;
}

cv::Point2i EfrosLeung::selectPixel()
{
    //std::cout<<"select pixel"<<std::endl;
    cv::Point2i pixel;
    int maxNeighborhood = 0;

    for (int i = 0; i < targetWidth; i++)
    {
        for (int j = 0; j < targetHeight; j++)
        {
            if (mask.at<uchar>(i, j) == 0) {
                int neighbors = getNeighborhood(i, j);
                if (neighbors > maxNeighborhood) {
                    maxNeighborhood = neighbors;
                    pixel.x = i;
                    pixel.y = j;
                } else if (neighbors == maxNeighborhood && rand() % 2 == 0) {
                    pixel.x = i;
                    pixel.y = j;
                }
            }
        }
    }

    //mask.at<uchar>(pixel.x, pixel.y) = 1;
    //std::cout<<"selected "<<pixel<<std::endl;
    return pixel;
}

int EfrosLeung::getNeighborhood(int i, int j) {
    int neighbors = 0;
    for (int k = -patchSize/2; k < patchSize/2 + 1; k++)
    {
        for (int l = -patchSize/2; l < patchSize/2 + 1; l++)
        {
            if (i + k >= 0 && i + k < targetWidth && j + l >= 0 && j + l < targetHeight && mask.at<uchar>(i + k, j + l) == 1) {
                neighbors++;
            }
        }
    }
    return neighbors;
}

cv::Point2i EfrosLeung::selectPatch(const cv::Point2i& pixel)
{
    //std::cout<<"select patch"<<std::endl;
    int minDistance = INT_MAX;
    cv::Point2i patch;
    for (int i = patchSize/2; i < img.rows - patchSize/2 - 1; i++)
    {
        for (int j = patchSize/2; j < img.cols - patchSize/2 - 1; j++)
        {
            int distance = getDistance(i, j, pixel);
            this->distances.at<int>(i, j) = distance;
            if (distance < minDistance) {
                minDistance = distance;
            }
        }
    }

    for (int i = patchSize/2; i < img.rows - patchSize/2; i++)
    {
        for (int j = patchSize/2; j < img.cols - patchSize/2; j++)
        {
            if ((float)this->distances.at<int>(i, j) > minDistance * (1 - EPSILON) && (float)this->distances.at<int>(i, j) < minDistance * (1 + EPSILON)) {
                patch.x = i;
                patch.y = j;
            }
        }
    }
    return patch;
}

int EfrosLeung::getDistance(int i, int j, const cv::Point2i& pixel)
{
    int distance = 0;
    for (int k = -(patchSize/2); k < patchSize/2 + 1; k++)
    {
        for (int l = -patchSize/2; l < patchSize/2 + 1; l++)
        {
            if (pixel.x + k >= 0 && pixel.x + k < targetWidth && pixel.y + l >= 0 && pixel.y + l < targetHeight && mask.at<uchar>(pixel.x + k, pixel.y + l) == 1) {
                cv::Vec3b targetPixel = target.at<cv::Vec3b>(pixel.x + k, pixel.y + l);
                cv::Vec3b imgPixel = img.at<cv::Vec3b>(i + k, j + l);
                distance += pow(targetPixel[0] - imgPixel[0], 2) + pow(targetPixel[1] - imgPixel[1], 2) + pow(targetPixel[2] - imgPixel[2], 2);
            }
        }
        ////std::cout<<std::endl;
    }
    return distance;
}

void EfrosLeung::color(const cv::Point2i& pixel, const cv::Point2i& patch)
{
    //std::cout<<"color"<<std::endl;
    for (int i = -patchSize/2; i < patchSize/2 + 1; i++)
    {
        for (int j = -patchSize/2; j < patchSize/2 + 1; j++)
        {
            if (pixel.x + i >= 0 && pixel.x + i < targetWidth && pixel.y + j >= 0 && pixel.y + j < targetHeight && mask.at<uchar>(pixel.x + i, pixel.y + j) == 0) {
                target.at<cv::Vec3b>(pixel.x + i, pixel.y + j) = img.at<cv::Vec3b>(patch.x + i, patch.y + j);
                mask.at<uchar>(pixel.x + i, pixel.y + j) = 1;
            }
        }
    }
}

void EfrosLeung::show()
{
    cv::imshow("Target", target);
    cv::waitKey(0);
}