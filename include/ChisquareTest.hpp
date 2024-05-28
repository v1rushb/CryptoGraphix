#ifndef CHISQUARETEST_HPP
#define CHISQUARETEST_HPP

#include "ITest.hpp"
#include "TestRunner.hpp"
#include <vector>
#include <stdexcept>
#include <numeric>
#include "Utils.hpp"

using namespace std;

#define ll long long int

class ChiSquareTest : public ITest {
    private:
        vector<ll> freq;
    
    public:

        ChiSquareTest(const vector<ll> &freqarr)
            : freq(freqarr) {}
        
        pair<double,bool> CalculateChiSquare() const {
            const ll sum = accumulate(freq.begin(),freq.end(), 0);
            const double expectedFreq = (double) sum/256.0;
            double s(0);
            for(ll el : freq) {
                double x = el - expectedFreq;
                s+=((x*x)/expectedFreq);
            }
            const double criticalVal = 293.2478; 
            return {s,s < criticalVal};
        }

        void runTest() const override {
            try {
                auto result = CalculateChiSquare();
                  Utils::print("ChiSquare Test Result: " + to_string(result.first) + (result.second? " Uniform\n" : " Not uniform\n"),"Yellow");
            } catch(const exception &ex) {
                  Utils::print("An error occurred during ChiSquare Test: " + string(ex.what()),"Red");
            }
        }
};

#endif