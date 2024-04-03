#ifndef IENCRYPT_HPP
#define IENCRYPT_HPP

#include "EncryptionStrategy.hpp"
#include "MetadataManager.hpp"
#include <opencv2/opencv.hpp>
#include <memory>
#include <string>

using namespace std;

class IEncrypt {
private:
    unique_ptr<EncryptionStrategy> strategy;
    MetadataManager metadataManager;
    vector<int> Vectorize(const cv::Mat &img);
    cv::Mat Matricize(vector<uchar> & data,Metadata size);
    cv::Mat setMatrix(const vector<uchar> &data, long int rows, long int cols);
    cv::Mat makeMatrix(long int rows, long int cols);

public:
    IEncrypt(unique_ptr<EncryptionStrategy> strategy)
        : strategy(move(strategy)) {}

    cv::Mat EncryptImage(const cv::Mat &img);
    cv::Mat DecryptImage(const cv::Mat &encryptedImg);
    string EncryptText(string);
    string DecryptText(string);
};

#endif
