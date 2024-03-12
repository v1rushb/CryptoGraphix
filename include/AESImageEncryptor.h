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
    vector<unsigned char> Vectorize(const cv::Mat &img) const;
    cv::Mat Matricize(const vector<unsigned char> &data, long int height, long int width) const;
    vector<unsigned char> Encode(const vector<unsigned char> &data);
    vector<unsigned char> Decode(const string& encoded);

public:
    AESImageEncryptor();
    AESImageEncryptor(const SecByteBlock& key, const CryptoPP::byte iv[AES::BLOCKSIZE]);

    pair<cv::Mat, vector<unsigned char>> Encrypt(const cv::Mat &img) const override;
    vector<unsigned char> Decrypt(const vector<unsigned char>& data) const override;

    string GetKeyBase64() const;
    string GetIVBase64() const;


};

#endif

//