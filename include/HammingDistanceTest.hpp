#ifndef HAMMINGDISTANCETEST_HPP
#define HAMMINGDISTANCETEST_HPP

#include "ITest.hpp"
#include "TestRunner.hpp"
#include <vector>
#include <stdexcept>

using namespace std;

class HammingDistanceTest : public ITest {
    private:
        vector<int> img1;
        vector<int> img2;
    
    public:

        HammingDistanceTest(const vector<int> &image1,const vector<int> &image2)
            : img1(image1), img2(image2) {}
        
        double CalculateHammingDistance() const {
            if(img1.size() - img2.size()) {
                throw runtime_error("SizeDifferenceException");
            }

            ll dist(0);
            for(int o = 0; o < img1.size();o++)
            {
                ll x = (img1[o] ^ img2[o]);
                for(int bit = 0; bit < 8;bit++) {
                    dist += (x >> bit) &1;
                }
            }
            return (dist/ (double) (img1.size()*8)) * 100;
        }

        void runTest() const override {
            try {
                double result = CalculateHammingDistance();
                Utils::print("Hamming Distance Test Result: " + to_string(result) + "%","Yellow");
            } catch(const exception &ex) {
                Utils::print("An error occurred during Hamming Distance Test: " + string(ex.what()) ,"Red");
            }
        }
};

#endif