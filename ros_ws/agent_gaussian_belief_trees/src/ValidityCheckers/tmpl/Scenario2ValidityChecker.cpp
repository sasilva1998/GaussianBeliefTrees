/*
 * 
 *
 *  Created on: Apr 22, 2015
 *      Author: juandhv (Juan David Hernandez Vega, juandhv@eia.udg.edu)
 *      
 *  State checker. Check is a given configuration (SE2 state) is collision-free.
 *  The workspace is represented by convex obstacles (hyperplanes).
 */

#include "EuclideanScenario2ValidityChecker.hpp"

#include <iostream>
#include <cmath>

EuclideanScenario2ValidityChecker::EuclideanScenario2ValidityChecker(const ob::SpaceInformationPtr &si) :
    ob::StateValidityChecker(si)
{
}


bool EuclideanScenario2ValidityChecker::inCollision(const ob::State *state, 
                         double X1, double Y1, 
                         double X2, double Y2) const
{ 
    
        // Find the nearest point on the  
        // rectangle to the center of  
        // the circle 

        Eigen::Matrix2d Cov = state->as<R2BeliefSpace::StateType>()->getCovariance();
        double R = 2*sqrt(Cov(0,0));

        double Xc = state->as<R2BeliefSpace::StateType>()->getX();
        double Yc = state->as<R2BeliefSpace::StateType>()->getY();


        // if (R < 5){
        //     std::cout << Xc << " " << Yc << std::endl;
        // }

        // Find the nearest point on the  
        // rectangle to the center of  
        // the circle 
        double Xn = std::max(X1, std::min(Xc, X2)); 
        double Yn = std::max(Y1, std::min(Yc, Y2)); 
        
        // Find the distance between the  
        // nearest point and the center  
        // of the circle 
        // Distance between 2 points,  
        // (x1, y1) & (x2, y2) in  
        // 2D Euclidean space is 
        // ((x1-x2)**2 + (y1-y2)**2)**0.5 
        double Dx = Xn - Xc; 
        double Dy = Yn - Yc; 
        return (Dx * Dx + Dy * Dy) <= R * R; 
}

bool EuclideanScenario2ValidityChecker::inCollision(const ob::State *state) const{

    //scenario 2
    if (inCollision(state, 0.0, 50, 40, 80)){
        return true;
    }
    else if (inCollision(state, 50, 50, 100, 80)){
        return true;
    }
    return false;
}

// bool Scenario2ValidityChecker::inCollisionWithObstacle(const ob::State *state, std::vector<double > obstacle)
// {
//     const ob::RealVectorStateSpace::StateType *state_R2;

//     return false;

// }

bool EuclideanScenario2ValidityChecker::isValid(const ob::State *state) const
{
    // for each obstacles
    // check if mean + 2sigma is in collision
    // return validity
    // return true;
    const double x = state->as<R2BeliefSpace::StateType>()->getX();
    const double y = state->as<R2BeliefSpace::StateType>()->getY();
    if (x > 100.0 || x < 0.0 || y < 0.0 || y > 100.0){
        return false;
    }

    return !(inCollision(state));
}

EuclideanScenario2ValidityChecker::~EuclideanScenario2ValidityChecker()
{

}