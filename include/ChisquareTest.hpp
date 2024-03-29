#ifndef CHISQUARETEST_HPP
#define CHISQUARETEST_HPP

#include "ITest.hpp"
#include "TestRunner.hpp"
#include <vector>
#include <stdexcept>
#include <numeric>

using namespace std;

#define ll long long int
#define all(d) d.begin(),d.end()

class ChiSquareTest : public ITest {
    private:
        vector<ll> freq;
    
    public:

        ChiSquareTest(const vector<ll> &freqarr)
            : freq(freqarr) {}
        
        pair<double,bool> CalculateChiSquare() const {
            const ll sum = accumulate(all(freq), 0);
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
                cout << "ChiSquare Test Result: " << result.first << (result.second? " Uniform\n" : " Not uniform\n");
            } catch(const exception &ex) {
                cout << "An error occurred during ChiSquare Test: " << ex.what() << endl;
            }
        }
};

#endif