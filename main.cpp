//
//  main.cpp
//  Assignment2
//
//  Created by Gurman Brar and Aryan Singh on 2020-01-28.
//  Copyright © 2020 Gurman Brar and Aryan Singh. All rights reserved.



#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <fstream>
#include "ClassHeader.hpp"
#include <cassert>

using namespace std;
    
// Constructor that takes an array of coefficients and the size of the array
// To produce a Polynomial object
Polynomial::Polynomial(int A[], int size) {
        for(int i = 0; i < size + 1; i++){
            polynomial_coefficients.push_back(A[size - i]);
        }
        polynomial_coefficients.resize(size);
    }
    
    
// Empty constrcutor (default) that produces random Polynomial object
Polynomial::Polynomial(){
    
        // Resize the vector to a randomly generated degree of variables
    int random_size = rand() % 1001;
        
        // Loop through the newly sized vector at each index and store the new coefficient
        for(int i = 0; i < random_size + 1; i++){
            
            // Store the random coefficient in a int variable
            int random_coefficients = (rand() % 2001) - 1000;
            
            // Make sure the coefficient is not out of range and push it to the vector
            if(random_coefficients < 1000 && random_coefficients > -1000){
                polynomial_coefficients.push_back(random_coefficients);
            }
        }
    polynomial_coefficients.resize(random_size);
    }
    
// Polynomial object constructor that takes filename as a parameter and reads the
// Object attributes from the file
Polynomial::Polynomial(string fileName){
        
        // Create an instance of the input stream object
        ifstream my_ifstream;
        
        // Open the specified filename in the constructor
        my_ifstream.open(fileName);
        
        // Check to see if the input stream has failed (reading, writting, etc.)
        if(!my_ifstream.fail()){
            
            int new_size;
            
            // Obtain the first line and set it to the new size variable and resize the vector to the polynomial size
            my_ifstream>> new_size;
            
            int coefficient;
            // Populate the vector with the coefficients in the file
            for(int i = 0; i < new_size; i ++){
                coefficient = 0;
                
                if(my_ifstream >> coefficient){
                    polynomial_coefficients.push_back(coefficient);
                } else polynomial_coefficients.push_back(0);
            }
            polynomial_coefficients.resize(new_size);
        }
        
        // Close the input stream
        my_ifstream.close();
        
    }

// Overloaded equals equals operator
bool Polynomial::operator==(const Polynomial& target) const{
         
        bool is_equal = true;
    
        if(target.polynomial_coefficients.size() != polynomial_coefficients.size())
            is_equal = false;
        
        if(target.polynomial_coefficients[0] != polynomial_coefficients[0]) is_equal = false;
    
        for(int i = 0; i < target.polynomial_coefficients.size() && is_equal; i++){
            if(target.polynomial_coefficients[i] != polynomial_coefficients[i]){
                is_equal = false;
                break;
            }
        }
        return is_equal;
}
    
// Overloaded addition operator
Polynomial Polynomial::operator+(const Polynomial& target) const{
        Polynomial output;
        
        for(int i = 0; i < target.polynomial_coefficients.size() + 1; i++){
            output.polynomial_coefficients[i] = target.polynomial_coefficients[i] + polynomial_coefficients[i];
        }
        output.polynomial_coefficients.resize(polynomial_coefficients.size());
        return output;
    }
    
// Overloaded subtraction operator
Polynomial Polynomial::operator-(const Polynomial& target) const{
        Polynomial output;
        
        for(int i = 0; i < target.polynomial_coefficients.size() + 1; i++){
                output.polynomial_coefficients[i] = polynomial_coefficients[i] - target.polynomial_coefficients[i];
        }

        if(target.polynomial_coefficients.size() >= polynomial_coefficients.size()) output.polynomial_coefficients.resize(target.polynomial_coefficients.size());
        else output.polynomial_coefficients.resize(polynomial_coefficients.size());
    
        return output;
}
    
// Overloaded multiplication operator
Polynomial Polynomial::operator*(const Polynomial& target) const{
    long new_size = polynomial_coefficients.size() + target.polynomial_coefficients.size();
    
    int new_data[new_size];
        for(int i = 0; i < target.polynomial_coefficients.size();i++){
            for(int j = 0; j < polynomial_coefficients.size(); j++){
                new_data[i + j] = target.polynomial_coefficients[i] * polynomial_coefficients[j];
            }
        }
    
    Polynomial output(new_data, new_size);
    return output;
}
    
// Method that will print the called objects polynomial coefficients
void Polynomial::print(){
    if(polynomial_coefficients.size()!= 0){
        for(int i = 0; i < polynomial_coefficients.size() + 1; i ++){
            cout<< setw(5) << polynomial_coefficients[polynomial_coefficients.size()-i] << "x^" << i << "+ " << endl;
        }
    } else cout<<"Polynomial is empty" << endl;
}

// Method that will return an object of Polynomial that is the derivative of called
// object
Polynomial Polynomial::derivative() const{
        Polynomial output;
        
        for(int i = 1; i < polynomial_coefficients.size(); i ++){
                output.polynomial_coefficients.push_back(polynomial_coefficients[i] * i);
        }
        
        output.polynomial_coefficients.resize(polynomial_coefficients.size() - 1);
    
        return output;
    }

void PolynomialTesting::constructors(){
    
    // Create a test array for constructor testing
    int randoms[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    
    // Init the objects using the three constructors
    Polynomial p1;
    Polynomial p2(randoms, 12);
    Polynomial p3("polynomial_test.txt");
    
    assert(p1.polynomial_coefficients.size() >= 0 && p1.polynomial_coefficients.size() <= 1000);
    cout<< "Default constructor size test passed" << endl;
    
    bool co_check = true;
    for(int i = 0; i < p1.polynomial_coefficients.size() && co_check; i++){
        if(p1.polynomial_coefficients[i] >= -1000 && p1.polynomial_coefficients[i] <= 1000){
            co_check = true;
        } else co_check = false;
    }
    assert(co_check);
    cout<< "all coefficients are within range and contain a number (default constructor)"<< endl;
    
    assert(p2.polynomial_coefficients.size() == 12);
    cout<<"Array contructor size test passed" << endl;
    
    for(int j = 0; j < 12; j++){
        assert(p2.polynomial_coefficients[12 - j] == randoms[j]);
    }
    cout<<"All coefficients are the same as the array (array constructor)" << endl;
    
    assert(p3.polynomial_coefficients.size() == 5);
    cout<<"The polynomial is of the correct degree in the test file" << endl;
    
    for(int k = 0; k < 5; k++){
       assert(p3.polynomial_coefficients[k] == randoms[k]);
    }
    cout<<"The coefficients match the polynomials (file constructor)" << endl;
}

void PolynomialTesting::operators(){
    
    // Init the Polynomial objects that will be used for testing (all random)
    Polynomial p1;
    Polynomial p2;
    Polynomial p3;
    Polynomial p4;
    Polynomial p5;
    Polynomial p6;
    Polynomial p7 = p1 + p2;
    Polynomial p8 = p3 - p4;
    Polynomial p9 = p5 * p6;
    Polynomial p10;
    Polynomial p11 = p10.derivative();
    
    if(p1.polynomial_coefficients.size() > p2.polynomial_coefficients.size())
        assert(p7.polynomial_coefficients.size() == p1.polynomial_coefficients.size());
    else assert(p7.polynomial_coefficients.size() == p2.polynomial_coefficients.size());
    cout<<"Addition operator works" << endl;
    
    if(p3.polynomial_coefficients.size() >= p4.polynomial_coefficients.size())
        assert(p8.polynomial_coefficients.size() == p3.polynomial_coefficients.size());
    else assert(p8.polynomial_coefficients.size() == p4.polynomial_coefficients.size());
    cout<<"subtraction operator works" << endl;
    
    assert(p11.polynomial_coefficients.size() == p10.polynomial_coefficients.size() - 1);
    cout<<"Derivative operator works" << endl;
    
    assert(p9.polynomial_coefficients.size() == p5.polynomial_coefficients.size() + p6.polynomial_coefficients.size());
    assert(p9.polynomial_coefficients[p9.polynomial_coefficients.size() - 1] != 0);
    cout<<"Multiplication operator works" << endl;
}

// Visual tests inorder to see if the output on the console is functional
void PolynomialTesting::print_test(){
    Polynomial p1;
    cout<<setw(5)<<"If the following has printed the print method has worked sucesfully."<<endl;
    p1.print();
}

// Method that runs all driver tests
void PolynomialTesting::run(){
    print_test();
    constructors();
    operators();
}
    
int main(){
    
    // Random generator seed
    srand(time(0));
    
    // Polynomial test class object
    PolynomialTesting pt1;
    
    // Assertion and driver code
    pt1.run();
    cout<<setw(5)<<"------------------------" << endl;
    cout<<setw(5)<<"------------------------" << endl;
    cout<<setw(5)<<"------------------------" << endl;
    
    // Final message if all tests are passed
    cout<<"*** Program has been tested and runs accordingly ***" << endl;
    
    return 0;
}
