#pragma once

#include <array>
#include <utility>
#include <vector>
#include <stdlib.h>
#include <limits>
#include <string>
#include <ostream>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <chrono>

template<int dim>
class KMeanPoint {
public :
    std::array<float,dim> coord;
    KMeanPoint(std::array<float, dim> values){
        coord = std::move(values);
    }; 

    static KMeanPoint random(float min, float max){
        std::array<float,dim> buff;
        for (size_t i = 0; i < dim; i++)
        {
            buff[i]= min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
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

    float distance2(const KMeanPoint & other) const{
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
    
    friend std::ostream& operator<<(std::ostream& os, const KMeanPoint<dim>& point){
        for (size_t i = 0; i < dim; i++)
        {
            os << point.coord[i];
            if(i != dim - 1){
                os << ", ";
            }
        };
        return os;
    }
};

template <int dim>
class KMean {
private:
    std::vector<std::pair<uint, KMeanPoint<dim>>> points;
    size_t k;

    std::vector<KMeanPoint<dim>> centroids;
public:
    KMean(size_t k, std::vector<KMeanPoint<dim>> pts) : k(k) {
        for (auto & point : pts)
        {
            points.push_back(std::make_pair(0, point));
        }
    }
    

    void init(){
        // init centroids
        std::cout<<"initializing " << k << " centroids and " << points.size() << "points" << std::endl;
        assert(points.size() > 0);
        assert(points.size() >= k);

        std::vector<int> pickedPoints;
        
        for(int i = 0; i < k; i++){
            int index = rand() % points.size();
            while(std::find(pickedPoints.begin(), pickedPoints.end(), index) != pickedPoints.end()){
                index = rand() % points.size();
            }
            centroids.push_back(points[index].second);
            pickedPoints.push_back(index);
            std::cout<< "centroid " << i << " initialized with point " << index << " = " << points[index].second << std::endl;
        }

        std::cout<<"Centroids initialized !"<<std::endl;

    };

    bool step() {

        std::vector<KMeanPoint<dim>> newCentroids(k, KMeanPoint<dim>::zero());

        //#pragma omp parallel for
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
        
        // for (size_t i = 0; i < nbPoints.size(); i++)
        // {
        //     std::cout<<"nbPoints["<<i<<"] = "<<nbPoints[i]<<std::endl;
        // }
        

        int nbChanged = 0;

        for (size_t i = 0; i < newCentroids.size(); i++)
        {
            newCentroids[i] /= nbPoints[i];
            if(newCentroids[i].distance2(centroids[i]) > 0){
                nbChanged++;
            }
            centroids[i] = newCentroids[i];
        }

        return nbChanged == 0;
    }


    void run(){
        int i = 0;
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        while(!step()) {
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::cout << "iteration " << i << " done in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
            begin = std::chrono::steady_clock::now();
            i++;
        }
        std::cout<<"finished in "<<i<<" steps"<<std::endl;
    }

    std::vector<KMeanPoint<dim>> getCentroids(){
        return centroids;
    }

    std::vector<KMeanPoint<dim>> getPoints(int centroid){
        std::vector<KMeanPoint<dim>> res;
        for (size_t i = 0; i < points.size(); i++)
        {
            if(points[i].first == centroid){
                res.push_back(points[i].second);
            }
        }
        return res;
    }

    std::vector<std::pair<uint, KMeanPoint<dim>>> getPoints(){
        return points;
    }

    void saveToCsv(const std::string & filename) const {
        //open file
        std::ofstream file(filename);
        //write header
        for (size_t i = 0; i < dim; i++)
        {
            file << "x" << i << ",";
        }
        file << "cluster" << std::endl;

        //write data
        for (size_t i = 0; i < points.size(); i++)
        {
            file << points[i].second << "," << points[i].first << std::endl;
        }
    
        file.close();
        
    }

    int predict(const KMeanPoint<dim> & p) const {
        float minDist = std::numeric_limits<float>::max();
        int res = -1;
        for (size_t i = 0; i < centroids.size(); i++)
        {
            float dist = centroids[i].distance2(p);
            if (dist < minDist)
            {
                minDist = dist;
                res = i;
            }   
        }
        return res;
    }

    int getCentroid(int i){
        return points[i].first;
    }
    
    
};