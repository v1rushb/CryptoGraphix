#ifndef IENCRYPTOR_H
#define IENCRYPTOR_H

#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;

class IEncryptor {
public:
    virtual ~IEncryptor() = default;

    virtual pair<cv::Mat,vector<unsigned char>> Encrypt(const cv::Mat &img) const = 0;
    virtual vector<unsigned char> Decrypt(const std::vector<unsigned char>& data) const = 0;
};

#endif
