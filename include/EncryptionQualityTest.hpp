#ifndef ENCRYPTIONQUALITYTEST_HPP
#define ENCRYPTIONQUALITYTEST_HPP

#include "ITest.hpp"
#include "TestRunner.hpp"
#include <vector>
#include <stdexcept>
#include "Utils.hpp"
#include <opencv2/opencv.hpp>

using namespace std;

#define ll long long int
class EncryptionQualityTest : public ITest {
    private:
        cv::Mat img1,img2;
    
    public:
        EncryptionQualityTest(const cv::Mat &image1, const cv::Mat &image2)
            : img1(image1),img2(image2) {}

        long double CalculateEncryptionQuality(const cv::Mat &img1, const cv::Mat &img2) const {
            long double ans(0.0);
            vector<ll> img1Freq = Utils::getImgFreq(img1);
            vector<ll> img2Freq = Utils::getImgFreq(img2);

            for(int o = 0; o < 256;o++) {
                ans+= abs(img1Freq[o]-img2Freq[o]);
            }
            return ans/256.0;
        }

        void runTest() const override {
            try {
                long double result = CalculateEncryptionQuality(img1,img2);
                Utils::print("Encryption Quality Test Result: " + to_string(result),"Yellow");
            } catch(const exception &ex) {
                Utils::print("An error occurred during Encryption Quality Test: " + string(ex.what()),"Yellow");
            }
        }
};

#endif