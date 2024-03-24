#ifndef IENCRYPTOR_H
#define IENCRYPTOR_H

#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;

class IEncryptor {
public:
    virtual ~IEncryptor() = default;

    virtual pair<cv::Mat,pair<vector<unsigned char>,vector<int>>> Encrypt(const cv::Mat &img) const = 0;
    virtual cv::Mat Decrypt(const pair<vector<unsigned char>,vector<int>> &p) const = 0;
};

#endif
