//
//  sphericalHarmonics.hpp
//  SphericalHarmonics
//
//  Created by Manuel Diaz Ramos on 12/19/15.
//  Copyright © 2015 Manuel Diaz Ramos. All rights reserved.
//

#ifndef sphericalHarmonics_h
#define sphericalHarmonics_h

#include <string>
#include <vector>
#include <math.h>
#include "coeffLoader.hpp"

////////////////////////// DEBUG ///////////////////////
#ifdef DEBUG
#define DEBUG_SPHERICAL_HARM
#endif
////////////////////////////////////////////////////////

/*!
 @brief Implents the computation of a field represented using spherical harmonics. Two methods are needed:
 - The constructor: receives an object that loads the coefficients up to a degree given by max_degree into memory (loader).
 - computeField(): compute the field at the position pos given in a body frame.
 */
class sphericalHarmonics
{
public:
    sphericalHarmonics();
    sphericalHarmonics(coeffLoader* loader, const std::string& filename, const unsigned int max_degree, const double mu, const double reference_radius);
    sphericalHarmonics(const sphericalHarmonics& x);
    virtual ~sphericalHarmonics();
    
    //Overloaded operators
    sphericalHarmonics& operator=(const sphericalHarmonics& hg);
    
    // Getters
    double          getClm(const unsigned int degree, const unsigned int order) const;
    double          getSlm(const unsigned int degree, const unsigned int order) const;
    unsigned int    getMaxDegree() const;
    double          getReferenceRadius() const;
    double          getGravitationalParameter() const;
    
    // Setters
    void setCoefficientLoader(coeffLoader* loader);
    
    // The important method!!
    void            computeField(const double pos[3], unsigned int degree, double  acc[3], bool include_zero_degree) const;
    
    // This method does the same computeField() does but using a different interface
    std::vector<double> getFieldVector(const std::vector<double>& pos, unsigned int degree, std::vector<double>& acc, bool include_zero_degree) const;
    
    std::string getLastErrorMessage(void);

#ifdef DEBUG_SPHERICAL_HARM
    void printCoefficients() const;
#endif
    
protected:
    unsigned int    _maxDegree;         // Maximum degree (l)
    double          _referenceRadius;   // Reference Radius (the coefficients are computed using this value
    double          _mu;                // Gravitational Parameter
    double**        _C_bar;             // C coefficient set
    double**        _S_bar;             // S coefficient set
    double**        _A_bar;             // Normalized 'derived' Assoc. Legendre Polynomials
    double*         _Re;                // Powers of projection of pos onto x_ecf (re)
    double*         _Im;                // Powers of projection of pos onto y_ecf (im)
    double**        _N1;
    double**        _N2;
    double**        _Nquot_1;
    double**        _Nquot_2;
    
    coeffLoader*  _coeffLoader;
    
    std::string _errorMessage;
    
    bool initialize();
    void deallocate();
    void copy(const sphericalHarmonics& x);
    
    static bool allocateArray(double** a, const unsigned int degree);
    static bool allocateArray(double*** a, const unsigned int degree);
    static void deallocateArray(double* a, const unsigned int degree);
    static void deallocateArray(double** a,  const unsigned int degree);
    static void copyArray(double* a, double* b, const unsigned int degree);
    static void copyArray(double** a,  double** b,  const unsigned int degree);

private:
    static double getK(const unsigned int degree);
    //--------------------------------------------------------------------
};

#endif /* sphericalHarmonics_h */
