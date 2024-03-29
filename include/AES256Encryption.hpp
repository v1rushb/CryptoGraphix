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

using namespace std;
using namespace CryptoPP;

class AES256Encryption : public EncryptionStrategy {
    CryptoPP::SecByteBlock key_;
    CryptoPP::byte iv_[AES::BLOCKSIZE];

private:
    void GenerateKeyAndIV();

public:
    AES256Encryption(); 
    AES256Encryption(const SecByteBlock& key, const CryptoPP::byte iv[AES::BLOCKSIZE]);

    vector<CryptoPP::byte> Encrypt(const vector<CryptoPP::byte> &plain) override;
    vector<CryptoPP::byte> Decrypt(const vector<CryptoPP::byte> &cipher,Metadata &metadata) override;

    string GetKeyBase64() const;
    string GetIVBase64() const;
};

#endif
