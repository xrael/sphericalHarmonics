//
//  main.cpp
//  SphericalHarmonics
//
//  Created by Manuel Diaz Ramos on 12/19/15.
//  Copyright © 2015 Manuel Diaz Ramos. All rights reserved.
//

#include <iostream>
#include "sphericalHarmonics.hpp"
#include "coeffLoader.hpp"
#include <math.h>
#include <vector>


int main(int argc, const char * argv[]) {
    
    //double mu = 4.46275472004e5; //[m^3/s^2]
    //double radius = 16000.0;//6378136.3;
    
    //EGM2008 data
    double matlabMu = 3.986004418000000e+14;
    double mu = matlabMu; //3986004.415e8; //[m^3/s^2]
    double radius = 6378137.0;//6378136.3; //[m]
    
    
    unsigned int degree = 121;
    
    double pos[3], acc[3];
    
    std::vector<double> pos_vec(3), acc_vec(3);
    
    
    std::string coefficient_file = "/Users/manu/Library/Mobile Documents/com~apple~CloudDocs/CU-Boulder/AVS-Lab/Spherical Harmonics/coefficients/GGM03S.txt";

    pos[0] = 7000000.0; //32.0;//6378136.3;
    pos[1] = 0.0;
    pos[2] = 0.0;
    pos_vec[0] = pos[0];
    pos_vec[1] = pos[1];
    pos_vec[2] = pos[2];
    
    coeffLoaderCSV* loader = new coeffLoaderCSV();
    
    sphericalHarmonics* sphericalHarm = new sphericalHarmonics(loader, coefficient_file, degree, mu, radius);
    
    //Copy test
    sphericalHarmonics* otherSpherical = new sphericalHarmonics(*sphericalHarm);
    
    sphericalHarmonics oneAnotherSpherical = *sphericalHarm; //Copy!
    
    
#ifdef DEBUG
    sphericalHarm->printCoefficients();
    sphericalHarm->computeField(pos, degree, acc, true);
    printf("Position [%.15f,%.15f,%.15f]. Field: [%.15f,%.15f,%.15f].\n", pos[0], pos[1], pos[2], acc[0], acc[1], acc[2]);
    sphericalHarm->getFieldVector(pos_vec, degree, acc_vec, true);
    printf("Position [%f,%f,%f]. Field Vector: [%f,%f,%f].\n", pos_vec[0], pos_vec[1], pos_vec[2], acc_vec[0], acc_vec[1], acc_vec[2]);

    otherSpherical->computeField(pos, degree, acc, true);
    printf("Position [%.15f,%.15f,%.15f]. Field: [%.15f,%.15f,%.15f].\n", pos[0], pos[1], pos[2], acc[0], acc[1], acc[2]);
    otherSpherical->getFieldVector(pos_vec, degree, acc_vec, true);
    printf("Position [%f,%f,%f]. Field Vector: [%f,%f,%f].\n", pos_vec[0], pos_vec[1], pos_vec[2], acc_vec[0], acc_vec[1], acc_vec[2]);
    
    oneAnotherSpherical.computeField(pos, degree, acc, true);
    printf("Position [%.15f,%.15f,%.15f]. Field: [%.15f,%.15f,%.15f].\n", pos[0], pos[1], pos[2], acc[0], acc[1], acc[2]);
    oneAnotherSpherical.getFieldVector(pos_vec, degree, acc_vec, true);
    printf("Position [%f,%f,%f]. Field Vector: [%f,%f,%f].\n", pos_vec[0], pos_vec[1], pos_vec[2], acc_vec[0], acc_vec[1], acc_vec[2]);
    
    
#else
    double R = 7000000.0; // [m]
    unsigned int samples = 10;
    
    for (unsigned int i = 0; i < samples; i++)
    {
        for (unsigned int j = 0; j < samples; j++)
        {
            double latitude = -M_PI/2.0 + M_PI / samples * i;
            double longitude = 2.0 * M_PI / samples * j;
            
            pos[0] = R * cos(latitude) * cos(longitude);
            pos[1] = R * cos(latitude)* sin(longitude);
            pos[2] = R * sin(latitude);
            pos_vec[0] = pos[0];
            pos_vec[1] = pos[1];
            pos_vec[2] = pos[2];
            
            sphericalHarm->computeField(pos, degree, acc, true);
            
            printf("Latitude: %f, Longitude: %f\n", latitude*180.0/M_PI, longitude*180.0/M_PI);
            printf("Position [%f,%f,%f]. Field: [%f,%f,%f].\n", pos[0], pos[1], pos[2], acc[0], acc[1], acc[2]);
            
            sphericalHarm->getFieldVector(pos_vec, degree, acc_vec, true);
            
            printf("Latitude: %f, Longitude: %f\n", latitude*180.0/M_PI, longitude*180.0/M_PI);
            printf("Position [%f,%f,%f]. Field Vector: [%f,%f,%f].\n", pos_vec[0], pos_vec[1], pos_vec[2], acc_vec[0], acc_vec[1], acc_vec[2]);
        }
    }
#endif
    
    delete sphericalHarm;
    
    delete loader;
    
    return 0;
}
