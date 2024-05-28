#ifndef UACI_HPP
#define UACI_HPP

#include "ITest.hpp"
#include "TestRunner.hpp"
#include <vector>
#include <stdexcept>

using namespace std;

#define ll long long int

class UACITest : public ITest {
    private:
        vector<int> img1;
        vector<int> img2;
    
    public:

        UACITest(const vector<int> &image1,const vector<int> &image2)
            : img1(image1), img2(image2) {}
        
        double CalculateUACI() const {
            if(img1.size() - img2.size()) {
                throw runtime_error("SizeDifferenceException");
            }
            double s(0);
            for(ll o = 0; o < img1.size();o++) {
                s+=(abs(img1[o] - img2[o])/255.0);
            }
            return ((s/img1.size())*100.0);
        }

        void runTest() const override {
            try {
                double result = CalculateUACI();
                Utils::print("UACI Test Result: " + to_string(result) + "%","Yellow");
            } catch(const exception &ex) {
                Utils::print("An error occurred during UACI Test: " + string(ex.what()),"Red");
            }
        }
};

#endif
