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


int main(int argc, const char * argv[]) {
    
    //double mu = 4.46275472004e5; //[m^3/s^2]
    //double radius = 16000.0;//6378136.3;
    
    //EGM2008 data
    double matlabMu = 3.986004418000000e+14;
    double mu = matlabMu; //3986004.415e8; //[m^3/s^2]
    double radius = 6378137.0;//6378136.3; //[m]
    
    
    unsigned int degree = 121;
    
    double pos[3], acc[3];
    
    
    std::string coefficient_file = "/Users/manu/Library/Mobile Documents/com~apple~CloudDocs/CU-Boulder/AVS-Lab/Spherical Harmonics/coefficients/EGM2008_to2190_TideFree";

    pos[0] = 7000000.0; //32.0;//6378136.3;
    pos[1] = 0.0;
    pos[2] = 0.0;
    
    coeffLoaderCSV* loader = new coeffLoaderCSV(' ');
    
    sphericalHarmonics* sphericalHarm = new sphericalHarmonics(loader, coefficient_file, degree, mu, radius);
    
#ifdef DEBUG
    sphericalHarm->printCoefficients();
    sphericalHarm->computeField(pos, degree, acc, true);
    printf("Position [%.15f,%.15f,%.15f]. Field: [%.15f,%.15f,%.15f].\n", pos[0], pos[1], pos[2], acc[0], acc[1], acc[2]);
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
            
            sphericalHarm->computeField(pos, degree, acc, true);
            
            printf("Latitude: %f, Longitude: %f\n", latitude*180.0/M_PI, longitude*180.0/M_PI);
            printf("Position [%f,%f,%f]. Field: [%f,%f,%f].\n", pos[0], pos[1], pos[2], acc[0], acc[1], acc[2]);
        }
    }
#endif
    
    return 0;
}
