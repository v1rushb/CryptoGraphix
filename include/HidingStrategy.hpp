#ifndef HIDINGSTRATEGY_HPP
#define HIDINGSTRATEGY_HPP

#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;


class HidingStrategy {
public:
    virtual void hideMessage(cv::Mat& img, const string& message) = 0;
    virtual string extractMessage(const cv::Mat& img, int messageLength) = 0;
    virtual ~HidingStrategy() {};
};

#endif