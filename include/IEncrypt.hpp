#ifndef IENCRYPT_HPP
#define IENCRYPT_HPP

#include "EncryptionStrategy.hpp"
#include "MetadataManager.hpp"
#include <opencv2/opencv.hpp>
#include <memory>
#include <string>
#include "Utils.hpp"

using namespace std;

class IEncrypt {
private:
    unique_ptr<EncryptionStrategy> strategy;
    MetadataManager metadataManager;
    vector<int> Vectorize(const cv::Mat &img);
    cv::Mat Matricize(vector<uchar> & data,Metadata size);
    cv::Mat setMatrix(const vector<uchar> &data, long int rows, long int cols);
    cv::Mat makeMatrix(long int rows, long int cols);
    static bool isInstantiated;

public:
    IEncrypt(unique_ptr<EncryptionStrategy> strategy);

    ~IEncrypt();

    cv::Mat EncryptImage(const cv::Mat &img);
    cv::Mat DecryptImage(const cv::Mat &encryptedImg);
    vector<CryptoPP::byte>  EncryptText(const vector<CryptoPP::byte> &data);
    vector<CryptoPP::byte>  DecryptText(const vector<CryptoPP::byte> &encryptedText);
    void changeKey(string &stringKey);
    void changeKey(CryptoPP::SecByteBlock key);
    CryptoPP::SecByteBlock getKey();
    static bool checkIsInstantiated() {
        return isInstantiated;
    }
    bool isNotCached();
    void AssignRandomKey(CryptoPP::SecByteBlock &key, const short &choice = 1);


};

#endif
