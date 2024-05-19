#ifndef AES256ENCRYPTION_HPP
#define AES256ENCRYPTION_HPP

#include "EncryptionStrategy.hpp"
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <stdexcept>
#include <cryptopp/base64.h>  
#include <cryptopp/osrng.h>
#include <utility>
#include <iostream>
#include "MetadataManager.hpp"
#include "Utils.hpp"

using namespace std;
using namespace CryptoPP;

class AES256Encryption : public EncryptionStrategy {
    CryptoPP::SecByteBlock key_;
    CryptoPP::byte iv_[AES::BLOCKSIZE] = {};

private:
    void GenerateKeyAndIV();
    CryptoPP::byte GenerateIV();

public:
    AES256Encryption(); 
    AES256Encryption(const SecByteBlock &key, const CryptoPP::byte iv[] = nullptr);

    vector<CryptoPP::byte> Encrypt(const vector<CryptoPP::byte> &plain) override;
    vector<CryptoPP::byte> Decrypt(const vector<CryptoPP::byte> &cipher) override;
    void SetConstantIV();
    void setKey(const CryptoPP::SecByteBlock & key);
    CryptoPP::SecByteBlock getKey();
    void GnerateRandomKey(CryptoPP::SecByteBlock &key, const short &choice);

    string GetKeyBase64() const;
    string GetIVBase64() const; //199 10 26 4 222 223 161 16 73 155 204 218 251 132 34 209
};

#endif
