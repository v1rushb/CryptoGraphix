#pragma
#include "IEncrypt.hpp"
#include "Utils.hpp"
#include <vector>
#include <iostream>
// #include "Macros.h"

using namespace std;
using namespace CryptoPP;

IEncrypt::IEncrypt(unique_ptr<EncryptionStrategy> strategy)
    : strategy(move(strategy)) {
        isInstantiated = true;
    }

IEncrypt::~IEncrypt() {
        isInstantiated = false;
    }
vector<int> IEncrypt::Vectorize(const cv::Mat &newImg) {
    cv::Mat img = newImg.clone();
    vector<int> buffer;
    buffer.reserve(img.rows * img.cols * img.channels());
    if(img.channels() == 3) {
        for(int o = 0; o < img.rows;o++) {
            for(int i = 0; i < img.cols;i++) {
                const cv::Vec3b &pixel = img.at<cv::Vec3b>(o,i);
                for(int x = 0; x < img.channels();x++) {
                    buffer.push_back(pixel[x]);
                }
            }
        }
    } else if(img.channels() == 1) {
        for(int o = 0; o < img.rows;o++) {
            for(int i = 0; i < img.cols;i++) {
                const uchar &pixel = img.at<uchar>(o,i);
                buffer.push_back(pixel);
            }
        }
    } else {
        throw runtime_error("Bad image format.");
    }
    return buffer;
}

void IEncrypt::changeKey(string &stringKey) {
    CryptoPP::SecByteBlock key = Utils::StringToSecByteBlock(stringKey);
    strategy->setKey(key);
}

void IEncrypt::changeKey(CryptoPP::SecByteBlock key) {
    strategy->setKey(key);
}

void IEncrypt::AssignRandomKey(CryptoPP::SecByteBlock &key, const short &choice) {
    strategy->GnerateRandomKey(key,choice);
    IEncrypt::changeKey(key);
}

CryptoPP::SecByteBlock IEncrypt::getKey() {
    return strategy->getKey();
}

bool IEncrypt::isNotCached() {
    return metadataManager.isEmpty();
}

cv::Mat IEncrypt::makeMatrix(long int rows, long int cols) {
    cv::Scalar defaultColor = (0,0,0);
    cv::Mat coloredMat(rows,cols,CV_8UC3,defaultColor);
    return coloredMat;
}

cv::Mat IEncrypt::setMatrix(const vector<CryptoPP::byte> &data, long int rows, long int cols) {
    cv::Mat img(rows, cols, CV_8UC3);
    vector<int> conv;
    conv.reserve(rows * cols * 3);
    for(auto el : data)
        conv.push_back(static_cast<int>(el));
    int ctr(0);
    long int expectedSize = img.total() * img.elemSize();
    for (int o = 0; o < img.rows; o++) {
        for (int i = 0; i < img.cols; i++) {
            if (ctr + 2 < expectedSize) {
                cv::Vec3b &pixel = img.at<cv::Vec3b>(o, i);
                pixel[0] = conv[ctr++];
                pixel[1] = conv[ctr++];
                pixel[2] = conv[ctr++];
            }
        }
    }
    return img;
}


cv::Mat IEncrypt::Encrypt(const cv::Mat &img) {
    vector<int> vectorizedImage = Utils::Vectorize(img);

    vector<CryptoPP::byte> output = Utils::IntVectorToByte(vectorizedImage);
    vector<CryptoPP::byte> encryptedData = strategy->Encrypt(output);

    Metadata metadata = {
        img.rows,
        img.cols,
        img.channels(),
        encryptedData,
    };

    cv::Mat image = Utils::Matricize(img.rows,img.cols,img.channels(),encryptedData);
    vector<int> newVectorizedImage = Utils::Vectorize(image);

    vector<CryptoPP::byte> output2 = Utils::IntVectorToByte(newVectorizedImage);

    string res = Utils::IntVectorToString(newVectorizedImage);

    metadataManager.storeMetadata(metadata,res);
    return image;
}

cv::Mat IEncrypt::Decrypt(const cv::Mat &encryptedImg) {
    vector<int> encryptedData = Utils::Vectorize(encryptedImg);
    // LOG_INFO("SIZE: " + to_string(encryptedData.size()));
    // LOG_INFO(("size " +  to_string(encryptedData.size())));
    Utils::print(to_string(encryptedData.size()),"Red");

    vector<CryptoPP::byte> output = Utils::IntVectorToByte(encryptedData);

    string res = Utils::IntVectorToString(encryptedData);

    Metadata metadata = metadataManager.getMetadata(res);

    // cv::Mat socImage = 
    //
    // vector<CryptoPP::byte> decryptedData = strategy->Decrypt(metadata.encrypted);
    vector<CryptoPP::byte> decryptedData = strategy->Decrypt(output);

    // cv::Mat image = Utils::Matricize(metadata.width,metadata.height,metadata.channels,decryptedData);
    cv::Mat image = Utils::Matricize(encryptedImg.rows,encryptedImg.cols,encryptedImg.channels(),decryptedData);
    return image;
}


vector<CryptoPP::byte> IEncrypt::Encrypt(const vector<CryptoPP::byte> &plainData) {

    return strategy->Encrypt(plainData);
}

vector<CryptoPP::byte> IEncrypt::Decrypt(const vector<CryptoPP::byte> &cipherData) {
    return strategy->Decrypt(cipherData);
}

bool IEncrypt::isInstantiated = false;