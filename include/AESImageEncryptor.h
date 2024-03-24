#ifndef AESIMAGEENCRYPTOR_H
#define AESIMAGEENCRYPTOR_H

#include "IEncryptor.h"
#include <cryptopp/secblock.h>
#include <cryptopp/aes.h>
#include <opencv2/opencv.hpp>
#include <utility>

using namespace std;
using namespace CryptoPP;
class AESImageEncryptor : public IEncryptor {
    CryptoPP::SecByteBlock key_;
    CryptoPP::byte iv_[AES::BLOCKSIZE];

private:
    void GenerateKeyAndIV();
    vector<int> Vectorize(const cv::Mat &img) const;
    cv::Mat Matricize(const vector<unsigned char> &data, long int height, long int width) const;
    string Encode(const vector<unsigned char> &data) const;
    vector<unsigned char> Decode(const vector<unsigned char> &encoded) const;
    cv::Mat makeMatrix(long int rows, long int cols) const;
    void embedSize(vector<long int> &data, long int rows, long int cols) const;
    void removeEmbededSize(vector<long int> &data) const;
    cv::Mat setMatrix(const vector<int> &data, long int rows, long int cols) const;

public:
    AESImageEncryptor();
    AESImageEncryptor(const SecByteBlock& key, const CryptoPP::byte iv[AES::BLOCKSIZE]);

    pair<cv::Mat,pair<vector<unsigned char>,vector<int>>> Encrypt(const cv::Mat &img) const override;
    cv::Mat Decrypt(const pair<vector<unsigned char>,vector<int>> &p) const override;

    string GetKeyBase64() const;
    string GetIVBase64() const;


};

#endif

//