#include "AES256Encryption.h"
#include <vector>
#include <string>
#include "cryptopp/base64.h"
#include <cryptopp/filters.h>

using namespace std;
using namespace CryptoPP;

#define all(d) d.begin(),d.end()

AES256Encryption::AES256Encryption(const SecByteBlock& key, const CryptoPP::byte iv[])
    : key_(key) {
    if (iv) {
        memcpy(iv_, iv, AES::BLOCKSIZE);
    } else {
        SetConstantIV();
    }
}



void AES256Encryption::setKey(const CryptoPP::SecByteBlock & key) {
    key_ = key;
}

CryptoPP::SecByteBlock AES256Encryption::getKey() {
    return key_;
}

void AES256Encryption::SetConstantIV() {
    const CryptoPP::byte iv_const[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    memcpy(iv_, iv_const, CryptoPP::AES::BLOCKSIZE);
}

void AES256Encryption::GnerateRandomKey(CryptoPP::SecByteBlock &key, const short &choice) {
    AutoSeededRandomPool rnd;
    size_t keySize;
    switch (choice) {
    case 1:
        keySize = 16;
        break;
    case 2:
        keySize = 24;
        break;
    case 3:
        keySize = 32;
        break;
    default:
        keySize = 16;
        break;
    }
    key.CleanNew(keySize);
    rnd.GenerateBlock(key.data(), key.size());
}
AES256Encryption::AES256Encryption() {
    GenerateKeyAndIV();
    SetConstantIV();
}

// void setKey(const CryptoPP::SecByteBlock & key) {
//     key_ = key;
// }

void AES256Encryption::GenerateKeyAndIV() {
    AutoSeededRandomPool rnd;
    key_.resize(AES::MAX_KEYLENGTH);
    rnd.GenerateBlock(key_,key_.size());
    SetConstantIV();
    // rnd.GenerateBlock(iv_,sizeof(iv_));
}

string EncodeBase64(const string& binaryInput) {
    string base64Output;
    StringSource ss(binaryInput, true,
        new Base64Encoder(
            new StringSink(base64Output)
        )
    );
    return base64Output;
}

string DecodeBase64(const string& base64Input) {
    string binaryOutput;
    StringSource ss(base64Input, true,
        new Base64Decoder(
            new StringSink(binaryOutput)
        )
    );
    return binaryOutput;
}

//CBC (too many bugs to fix) (for later: make use of the database to save image metadata which will contain padding and image size etc..)
// vector<CryptoPP::byte> AES256Encryption::Encrypt(const vector<CryptoPP::byte> &plain) {
//     vector<CryptoPP::byte> cipher;
//     try {
//         CBC_Mode<AES>::Encryption encryption;
//         encryption.SetKeyWithIV(key_, AES::DEFAULT_KEYLENGTH, iv_);
//         ArraySource(plain.data(), plain.size(), true,
//                 new StreamTransformationFilter(encryption,
//                                                new VectorSink(cipher)
//                                               )
//                );
//         } catch(const CryptoPP::Exception &ex) {
//             throw CustomException("Encryption Failed: " + string(ex.what()));
//         }
//     return cipher;
// }

// vector<CryptoPP::byte> AES256Encryption::Decrypt(const vector<CryptoPP::byte> &cipher) {
//         vector<CryptoPP::byte> recovered;
//         try {
//             CBC_Mode<AES>::Decryption decryption;
//             decryption.SetKeyWithIV(key_, AES::DEFAULT_KEYLENGTH, iv_);
//             ArraySource(cipher.data(), cipher.size(), true,
//                         new StreamTransformationFilter(decryption,
//                                                     new VectorSink(recovered)
//                                                     )
//                     );
//         } catch (const CryptoPP::Exception& ex) {
//             throw CustomException("Decryption failed: " + string(ex.what()));
//         }
//         return recovered;
// }

//CTR
vector<CryptoPP::byte> AES256Encryption::Encrypt(const vector<CryptoPP::byte>& plain) {
        vector<CryptoPP::byte> cipher;
        try {
            CryptoPP::CTR_Mode<CryptoPP::AES>::Encryption encryption;
            encryption.SetKeyWithIV(key_, CryptoPP::AES::DEFAULT_KEYLENGTH, iv_);
            CryptoPP::ArraySource(plain.data(), plain.size(), true,
                new CryptoPP::StreamTransformationFilter(encryption,
                    new CryptoPP::VectorSink(cipher)
                )
            );
        } catch(const CryptoPP::Exception &ex) {
            throw runtime_error("Encryption Failed: " + string(ex.what()));
        }
        return cipher;
    }

vector<CryptoPP::byte> AES256Encryption::Decrypt(const vector<CryptoPP::byte>& cipher) {
        vector<CryptoPP::byte> recovered;
        try {
            CryptoPP::CTR_Mode<CryptoPP::AES>::Decryption decryption;
            decryption.SetKeyWithIV(key_, CryptoPP::AES::DEFAULT_KEYLENGTH, iv_);
            CryptoPP::ArraySource(cipher.data(), cipher.size(), true,
                new CryptoPP::StreamTransformationFilter(decryption,
                    new CryptoPP::VectorSink(recovered)
                )
            );
        } catch (const CryptoPP::Exception& ex) {
            throw runtime_error("Decryption failed: " + string(ex.what()));
        }
        return recovered;
    }