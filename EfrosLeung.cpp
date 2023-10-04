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
    patch.x = rand() % (img.cols - patchSize) + patchSize/2;
    patch.y = rand() % (img.rows - patchSize) + patchSize/2;

    assert(patch.x + patchSize/2 < img.cols && patch.y + patchSize/2 < img.rows);

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

    this->aa = cv::Point2i(targetWidth/2 - patchSize/2 - 1, targetHeight/2 - patchSize/2 - 1);
    if(aa.x < 0) aa.x = 0;
    if(aa.y < 0) aa.y = 0;
    this->bb = cv::Point2i(targetWidth/2 + patchSize/2 + 2, targetHeight/2 + patchSize/2 + 1);
    if(bb.x > targetWidth) bb.x = targetWidth;
    if(bb.y > targetHeight) bb.y = targetHeight;
}

int64 EfrosLeung::run() {
    cv::Point2i pixel = selectPixel();
    cv::Point2i patch;
    auto begin = std::chrono::high_resolution_clock::now();
    auto previous = begin;
    int n = 0;
    while(pixel.x != -1)
    {
        patch = selectPatch(pixel);
        if(n%targetWidth == 0) {
            //auto end = std::chrono::high_resolution_clock::now();
            //auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            //auto elapsedSincePrevious = std::chrono::duration_cast<std::chrono::milliseconds>(end - previous);
            //previous = end;
            //std::cout << "Iteration " << n << " :: Previous patch "<< patch << " :: Time " << elapsed.count() << " ms" << " :: " << elapsedSincePrevious.count() << " ms" << std::endl;
        }
        color(pixel, patch);
        pixel = selectPixel();
        n++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    //std::cout << "Total time : " << elapsed.count() << " ms" << std::endl;
    return elapsed.count();
}

cv::Point2i EfrosLeung::selectPixel()
{
    cv::Point2i pixel;
    int maxNeighborhood = 0;
    
    for (int i = aa.x; i < bb.x; i++)
    {
        for (int j = aa.x; j < bb.y; j++)
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
    
    if(maxNeighborhood == 0) return cv::Point2i(-1, -1);

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
    float minDistance = INT_MAX;
    cv::Point2i patch(-1, -1);
    int wps = img.rows - patchSize/2 - 1;
    int hps = img.cols - patchSize/2 - 1;
    #pragma omp parallel for
    for (int i = patchSize/2; i < wps; i++)
    {
        for (int j = patchSize/2; j < hps; j++)
        {
            int distance = getDistance(i, j, pixel);
            this->distances.at<int>(i, j) = distance;
            //std::cout<<distance<<std::endl;
            if (distance != 0 && distance < minDistance) {
                minDistance = distance;
            }
        }
    }

    for (int i = patchSize/2; i < img.rows - patchSize/2 - 1; i++)
    {
        for (int j = patchSize/2; j < img.cols - patchSize/2 - 1; j++)
        {
            //std::cout<< minDistance * (1.0 - EPSILON) << " < " << (float)this->distances.at<int>(i, j) << " < " << minDistance * (1.0 + EPSILON) << std::endl;
            if ((float)this->distances.at<int>(i, j) > minDistance * (1.0 - EPSILON) && (float)this->distances.at<int>(i, j) < minDistance * (1.0 + EPSILON) && (rand()%2 == 1 || patch.x == -1)) {
                patch = cv::Point2i(i, j);
            }
        }
    }

    assert(patch.x != -1 && patch.y != -1);

    //std::cout<<patch<<std::endl;
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
    if(pixel.x - 1 < aa.x) aa.x = pixel.x - 1;
    else if (pixel.x + 2 > bb.x) bb.x = pixel.x + 2;
    if(pixel.y - 1 < aa.y) aa.y = pixel.y - 1;
    else if (pixel.y + 2 > bb.y) bb.y = pixel.y + 2;

    if(aa.x < 0) aa.x = 0;
    if(aa.y < 0) aa.y = 0;
    if(bb.x > targetWidth) bb.x = targetWidth;
    if(bb.y > targetHeight) bb.y = targetHeight;

    target.at<cv::Vec3b>(pixel.x, pixel.y) = img.at<cv::Vec3b>(patch.x, patch.y);
    mask.at<uchar>(pixel.x, pixel.y) = 1;

    


    // for (int i = -patchSize/2; i < patchSize/2 + 1; i++)
    // {
    //     for (int j = -patchSize/2; j < patchSize/2 + 1; j++)
    //     {
    //         if (pixel.x + i >= 0 && pixel.x + i < targetWidth && pixel.y + j >= 0 && pixel.y + j < targetHeight && mask.at<uchar>(pixel.x + i, pixel.y + j) == 0) {
    //             //std::cout<<patch.x << " " << patch.y << " " << patch.x + i << " " << patch.y + j << std::endl;
    //             assert(patch.x + i >= 0 && patch.x + i < img.rows && patch.y + j >= 0 && patch.y + j < img.cols);
    //             target.at<cv::Vec3b>(pixel.x + i, pixel.y + j) = img.at<cv::Vec3b>(patch.x + i, patch.y + j);
    //             mask.at<uchar>(pixel.x + i, pixel.y + j) = 1;
    //         }
    //     }
    // }
}

void EfrosLeung::show()
{
    cv::imshow("Target", target);
    cv::waitKey(0);
}

cv::Mat EfrosLeung::getTarget() const
{
    return target;
}