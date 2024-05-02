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
    IEncrypt(unique_ptr<EncryptionStrategy> strategy)
        : strategy(move(strategy)) {
            isInstantiated = true;
        }

    ~IEncrypt() {
        isInstantiated = false;
    }

    cv::Mat EncryptImage(const cv::Mat &img);
    cv::Mat DecryptImage(const cv::Mat &encryptedImg);
    vector<CryptoPP::byte>  EncryptText(const vector<CryptoPP::byte> &data);
    vector<CryptoPP::byte>  DecryptText(const vector<CryptoPP::byte> &encryptedText);
    void changeKey(string &stringKey) {
        CryptoPP:: SecByteBlock key;
        Utils::StringIntoSecByteBlock(key, stringKey);
        strategy->setKey(key);
    }
    static bool checkIsInstantiated() {
        return isInstantiated;
    }

    bool isNotCached() {
        return metadataManager.isEmpty();
    }
};

#endif
