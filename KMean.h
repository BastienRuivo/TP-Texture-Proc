#pragma once

#include <array>
#include <utility>
#include <vector>
#include <stdlib.h>
#include <limits>
#include <sciplot/sciplot.hpp>

using namespace sciplot;


template<int dim>
class KMeanPoint {
public :
    std::array<float,dim> coord;
    KMeanPoint(std::array<float, dim> values){
        coord = std::move(values);
    }; 

    static KMeanPoint random(){
        std::array<float,dim> buff;
        for (size_t i = 0; i < dim; i++)
        {
            buff[i]= (rand() / (float)(RAND_MAX));
        }
        return KMeanPoint(buff);
    }

    static KMeanPoint zero(){
        std::array<float,dim> buff;
        for (size_t i = 0; i < dim; i++)
        {
            buff[i]= 0;
        }
        return KMeanPoint(buff);
    }

    float distance2(const KMeanPoint other){
        float res = 0;
        for (size_t i = 0; i < dim; i++)
        {
            res += (coord[i] - other.coord[i]) * (coord[i] - other.coord[i]);
        }
        return res;
    }

    KMeanPoint<dim> operator+(const KMeanPoint<dim>& other){
        std::array<float,dim> buff;
        for (size_t i = 0; i < dim; i++)
        {
            buff[i]= coord[i] + other.coord[i];
        }
        return KMeanPoint(buff);
    }

    KMeanPoint<dim>& operator+=(const KMeanPoint<dim>& other){
        for (size_t i = 0; i < dim; i++)
        {
            coord[i] += other.coord[i];
        }
        return *this;
    }

    KMeanPoint<dim> operator/(const int& other){
        std::array<float,dim> buff;
        for (size_t i = 0; i < dim; i++)
        {
            buff[i]= coord[i] / other;
        }
        return KMeanPoint(buff);
    }

    KMeanPoint<dim>& operator/=(const int& other){
        for (size_t i = 0; i < dim; i++)
        {
            coord[i] /= other;
        }
        return *this;
    }

    KMeanPoint<dim> operator*(const float& other){
        std::array<float,dim> buff;
        for (size_t i = 0; i < dim; i++)
        {
            buff[i]= coord[i] * other;
        }
        return KMeanPoint(buff);
    }

    KMeanPoint<dim>& operator*=(const float& other){
        for (size_t i = 0; i < dim; i++)
        {
            coord[i] *= other;
        }
        return *this;
    }

    KMeanPoint<dim> operator-(const KMeanPoint<dim>& other){
        std::array<float,dim> buff;
        for (size_t i = 0; i < dim; i++)
        {
            buff[i]= coord[i] - other.coord[i];
        }
        return KMeanPoint(buff);
    }

    KMeanPoint<dim>& operator-=(const KMeanPoint<dim>& other){
        for (size_t i = 0; i < dim; i++)
        {
            coord[i] -= other.coord[i];
        }
        return *this;
    }

    KMeanPoint<dim> operator-(){
        std::array<float,dim> buff;
        for (size_t i = 0; i < dim; i++)
        {
            buff[i]= -coord[i];
        }
        return KMeanPoint(buff);
    }
};

template <int dim>
class KMean {
private:
    std::vector<std::pair<uint, KMeanPoint<dim>>> points;
    size_t k;

    std::vector<KMeanPoint<dim>> centroids;
public:
    KMean(size_t k, std::vector<KMeanPoint<dim>> points) : k(k) {
        for (auto & point : points)
        {
            points.push_back(std::make_pair(0, point));
        }
    }
    

    void init(){
        // init centroids
        for(int i = 0; i < k; i++){
            centroids.push_back(std::make_pair(i, KMeanPoint<dim>::random()));
        }

    };

    bool step() {

        std::vector<KMeanPoint<dim>> newCentroids(centroids.size(), KMeanPoint<dim>::zero());
        
        #pragma omp parallel for
        for (size_t i = 0; i < points.size(); i++)
        {
            float minDist = std::numeric_limits<float>::max();
            for (size_t j = 0; j < centroids.size(); j++)
            {
                float dist = points[i].second.distance2(centroids[j]);
                if (dist < minDist)
                {
                    minDist = dist;
                    points[i].first = j;
                }   
            }
        }

        std::vector<size_t> nbPoints(newCentroids.size(), 0);
        for (size_t i = 0; i < points.size(); i++)
        {
            newCentroids[points[i].first] += points[i].second;
            nbPoints[points[i].first]++;
        }

        int nbChanged = 0;

        for (size_t i = 0; i < newCentroids.size(); i++)
        {
            newCentroids[i] /= nbPoints[i];
            if(newCentroids[i].distance2(centroids[i]) > 0.0001){
                nbChanged++;
            }
            centroids[i] = newCentroids[i];
        }

        return !nbChanged;
    }


    void run(){
        init();
        while(!step());
    }

    std::vector<KMeanPoint<dim>> getCentroids(){
        return centroids;
    }

    std::vector<std::pair<uint, KMeanPoint<dim>>> getPoints(){
        return points;
    }

    
    
};