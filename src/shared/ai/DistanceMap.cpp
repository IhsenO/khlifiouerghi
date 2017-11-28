/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "DistanceMap.h"
#include <iostream>
#include "UtilsAI.hpp"
#include <queue>

using namespace state;
using namespace engine;
using namespace std;

namespace ai{

    //DistanceMap::DistanceMap(int width, int height) : width(width), height(height), map(width*height) {
    //}

    DistanceMap::DistanceMap() {
        
    }

    void DistanceMap::init(int width, int height) {
        this->width = width;
        this->height = height;
        //cout << width << endl;
        //this->setHeight(state.getMonde().getHeight());
        for(int i = 0; i < width*height; i++){
            this->map.push_back(true);
            this->weights.push_back(9999);
        }
        
        this->directions.push_back(UP);
        this->directions.push_back(RIGHT);
        this->directions.push_back(DOWN);
        this->directions.push_back(LEFT);
    }
 
    
    int DistanceMap::getHeight() const {
        return this->height;
    }

    int DistanceMap::getWidth() const {
        return this->width;
    }

    void DistanceMap::setHeight(int height) {
        this->height = height;
    }

    void DistanceMap::setWidth(int width) {
        this->width = width;
    }
    
    


    void DistanceMap::update(state::State& state) {
        for(int i = 0; i < this->height; i++)
            for(int j = 0; j < this->width; j++){
                //cout << this->map.size() << endl;
                if(canAccessAIDist(state, j, i)) this->map[i*width + j] = true;
                else this->map[i*width + j] = false;
            }
    }

    void DistanceMap::afficher() {
        
        for(int i = 0; i < height; i++){ 
		for(int j = 0; j < width; j++){
			if(map[i*width + j] == true){
				cout << "o ";
			}
			else{
				cout << "x ";
			}
		}
		cout << '\n';
	}
        
    }

    void DistanceMap::afficherPoids() {
        for(int i = 0; i < height; i++){ 
		for(int j = 0; j < width; j++){
			if(weights[i*width + j] < 10){
				cout << weights[i*width + j];
                                cout << "  ";
			}
                        else if(weights[i*width + j] == 9999){
                                cout << "x  ";
                        }
			else{
				cout << weights[i*width + j];
                                cout << " ";
			}
		}
		cout << '\n';
	}
    }

    void DistanceMap::addQueue(int x, int y) {
        pointsQueue.push(Point(x,y,0));
    }

    void DistanceMap::clearQueue() {
        pointsQueue = priority_queue<Point, vector<Point>, PointCompareWeight>();
    }

    
    void DistanceMap::dijkstra() {
                
        //this->map[yTo*width + xTo] = true;
        //vector<Point> ferme;
        //queue<Point> pointsQueue;
        //priority_queue<Point, vector<Point>, PointCompareWeight> pointsQueue;
        //pointsQueue.push(Point(xFrom, yFrom,0));
        //vector<int> weights(this->width*this->height);
        for(int i = 0; i < (int)weights.size(); i++)
            weights[i] = 9999;
            
        while(!pointsQueue.empty()){
            
            Point p = pointsQueue.top();
            pointsQueue.pop();

            weights[p.getY()*width + p.getX()] = p.getWeight();
            //if(p.getX() == xTo && p.getY() == yTo)
            //    return p.getWeight();

            for(Direction d : this->directions){
                Point pp = p.transform(d);
                if(pp.getX() >= 0 && pp.getX() < width && pp.getY() >= 0 && pp.getY() < height){
                    if(map[pp.getY()*width + pp.getX()] != false){
                        pp.setWeight(p.getWeight() + 1);                                           
                        if(weights[pp.getY()*width + pp.getX()] > pp.getWeight()){
                            pointsQueue.push(pp);
                            //sortQueue(pointsQueue);
                            
                        //cout << "poid debut : "<<pointsQueue.front().getWeight() << " poid fin : "<<pointsQueue.back().getWeight() << endl; 
                        }
                    
                    }
                }
            }
        }
        
        //return -1;
          
    }
 

    void DistanceMap::sortQueue(std::queue<Point>& queue) {
        
        vector<Point> tmp;
        //cout << queue.size() << endl;
        while(!queue.empty()){
            tmp.push_back(queue.front());
            queue.pop();
        }
              
        for(int i = tmp.size() - 1; i >= 0; i--){
		for(int j = 0; j < i; j++){
			if(tmp[j+1].getWeight() <= tmp[j].getWeight()){
				Point pTmp = tmp[j];
				tmp[j] = tmp[j+1];
				tmp[j+1] = pTmp;
			}
		}
	}
      
        for(int i = 0; i < (int)tmp.size(); i++)
            queue.push(tmp[i]);       
    }
    
    

}