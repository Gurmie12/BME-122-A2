//
//  ClassHeader.hpp
//  Assignment2
//
//  Created by Gurman Brar and Aryan Singh on 2020-01-31.
//  Copyright © 2020 Gurman Brar and Aryan Singh. All rights reserved.
//

#ifndef ClassHeader.hpp

#define ClassHeader.hpp

#include <vector>

using namespace std;

class Polynomial {
    
    vector<int> polynomial_coefficients;
    
public:
    
    Polynomial(int A[], int size);
    
    Polynomial();
    
    Polynomial(string fileName);
    
    bool operator==(const Polynomial& target) const;
    
    Polynomial operator+(const Polynomial& target) const;
    
    Polynomial operator-(const Polynomial& target) const;
    
    Polynomial operator*(const Polynomial& target) const;
    
    void print();
    
    Polynomial derivative() const;
    
    friend class PolynomialTesting;
};

class PolynomialTesting {
public:
    void constructors();
    
    void run();
    
    void operators();
    
    void print_test();
};

#endif
