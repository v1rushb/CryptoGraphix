#ifndef ENCRYPTIONSTRATEGY_HPP
#define ENCRYPTIONSTRATEGY_HPP

#include <opencv2/opencv.hpp>
#include <cryptopp/secblock.h>
#include <cryptopp/aes.h>
#include <opencv2/opencv.hpp>
#include <utility>
#include "MetadataManager.hpp"


using namespace std;

class EncryptionStrategy {
public:
    virtual ~EncryptionStrategy() = default;

    virtual vector<CryptoPP::byte>  Encrypt(const vector<CryptoPP::byte> &plain) = 0;
    virtual vector<CryptoPP::byte>  Decrypt(const vector<CryptoPP::byte> &cipher) = 0;
    virtual void setKey(const CryptoPP::SecByteBlock &key) = 0;
    virtual CryptoPP::SecByteBlock getKey() = 0;
    virtual void GnerateRandomKey(CryptoPP::SecByteBlock &key, const short &choice) = 0;
};

#endif
