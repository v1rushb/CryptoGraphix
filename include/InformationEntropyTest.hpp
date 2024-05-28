#ifndef INFORMATIONENTROPYTEST_HPP
#define INFORMATIONENTROPYTEST_HPP

#include "ITest.hpp"
#include "TestRunner.hpp"
#include <vector>
#include <stdexcept>
#include "Utils.hpp"
#include <opencv2/opencv.hpp>

using namespace std;

#define ll long long int

class InformationEntropyTest : public ITest {
    private:
        cv::Mat img;
    
    public:

        InformationEntropyTest(const cv::Mat &image)
            : img(image) {}
        
        long double CalculateInformationEntropy(const cv::Mat &img) const {
            vector<ll> freq = Utils::getImgFreq(img);
            const short channels = img.channels();
            long double val = 0.0;
            const ll picSize = img.cols * img.rows* channels;
            for(int o = 0; o < 256;o++) {
                if(freq[o] > 0) {
                    long double prob = (freq[o] / (picSize * 1.0));
                    val -= prob * log2(prob);
                }
            }
            return val;
        }

        void runTest() const override {
            try {
                long double result = CalculateInformationEntropy(img);
                Utils::print("Information Entropy Test Result: " + to_string(result),"Yellow");
            } catch(const exception &ex) {
                Utils::print("An error occurred during Information Entropy Test: " + string(ex.what()),"Red");
            }
        }
};

#endif