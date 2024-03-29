#ifndef NPCRTEST_HPP
#define NPCRTEST_HPP

#include "ITest.hpp"
#include "TestRunner.hpp"
#include <vector>
#include <stdexcept>

using namespace std;

#define ll long long int

class NPCRTest : public ITest {
    private:
        vector<int> img1;
        vector<int> img2;
    
    public:

        NPCRTest(const vector<int> &image1,const vector<int> &image2)
            : img1(image1), img2(image2) {}
        
        double CalculateNPCR() const {
            if(img1.size() - img2.size()) {
                throw runtime_error("SizeDifferenceException");
            }
            ll diff(0);
            for(ll o = 0; o < img1.size();o++) {
                diff+= (img1[o]!=img2[o]);
            }
            return (static_cast<double>(diff)/img1.size()) *100.0;
        }

        void runTest() const override {
            try {
                double result = CalculateNPCR();
                cout << "NPCR Test Result: " << result << '%' << endl;
            } catch(const exception &ex) {
                cout << "An error occurred during NPCR Test: " << ex.what() << endl;
            }
        }
};

#endif