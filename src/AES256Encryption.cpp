#include "AES256Encryption.hpp"
#include <vector>
#include <string>
#include "cryptopp/base64.h"
#include <cryptopp/filters.h>

using namespace std;
using namespace CryptoPP;

#define all(d) d.begin(),d.end()

AES256Encryption::AES256Encryption(const SecByteBlock& key, const CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE])
    : key_(key) {
    copy(iv, iv + AES::BLOCKSIZE, iv_); // look for later.
}

AES256Encryption::AES256Encryption() {
    GenerateKeyAndIV();
}

void AES256Encryption::GenerateKeyAndIV() {
    AutoSeededRandomPool rnd;
    key_.resize(AES::DEFAULT_KEYLENGTH);
    rnd.GenerateBlock(key_,key_.size());
    rnd.GenerateBlock(iv_,sizeof(iv_));
}

std::string EncodeBase64(const std::string& binaryInput) {
    std::string base64Output;
    CryptoPP::StringSource ss(binaryInput, true,
        new CryptoPP::Base64Encoder(
            new CryptoPP::StringSink(base64Output)
        )
    );
    return base64Output;
}

std::string DecodeBase64(const std::string& base64Input) {
    string binaryOutput;
    StringSource ss(base64Input, true,
        new CryptoPP::Base64Decoder(
            new CryptoPP::StringSink(binaryOutput)
        )
    );
    return binaryOutput;
}


// vector<uchar> AES256Encryption::Encrypt(const vector<uchar> &data) {
//     vector<uchar> encrypted;
//     try {
//         vector<uchar> newData(all(data));
//         CBC_Mode<AES>::Encryption encryptor;
//         encryptor.SetKeyWithIV(key_, key_.size(), iv_);
//         CryptoPP::ArraySource(newData.data(), newData.size(), true,
//             new CryptoPP::StreamTransformationFilter(encryptor,
//                 new CryptoPP::VectorSink(encrypted)
//             )
//         );
//     } catch(const CryptoPP::Exception& ex) {
//         throw runtime_error("Encryption failed: " + string(ex.what()));
//     }

//     return vector<uchar>(all(encrypted));
// }

vector<CryptoPP::byte> AES256Encryption::Encrypt(const vector<CryptoPP::byte> &plain) {
    vector<CryptoPP::byte> cipher;
    try {
        CBC_Mode<AES>::Encryption encryption;
        encryption.SetKeyWithIV(key_, AES::DEFAULT_KEYLENGTH, iv_);
        ArraySource(plain.data(), plain.size(), true,
                new StreamTransformationFilter(encryption,
                                               new VectorSink(cipher)
                                              )
               );
        } catch(const CryptoPP::Exception &ex) {
            throw runtime_error("shit" + string(ex.what()));
        }
    return cipher;
}

// vector<uchar> AES256Encryption::Decrypt(const vector<uchar> &encryptedData, Metadata &metadata) {
//     string decrypted;
//     // cout << "Size:" << encryptedData.size() << endl;
//     // for(int o  =0; o < 10;o++)
//         // cout << encryptedData[123] << ' ';
//     // cout << endl;
//     try {
//         vector<uchar> newData(all(encryptedData));
//         newData.insert(newData.end(), metadata.padding.begin(), metadata.padding.end());
//         CBC_Mode<AES>::Decryption decryptor;
//         decryptor.SetKeyWithIV(key_, key_.size(), iv_);
//         CryptoPP::ArraySource(
//             reinterpret_cast<const CryptoPP::byte*>(newData.data()), newData.size(), true,
//             new CryptoPP::StreamTransformationFilter(decryptor,
//                 new CryptoPP::StringSink(decrypted)
//             )
//         );
//     } catch (const CryptoPP::Exception& ex) {
//         throw runtime_error("Decryption failed: " + string(ex.what()));
//     }
//     return vector<uchar>(all(decrypted));
// }

vector<CryptoPP::byte> AES256Encryption::Decrypt(const vector<CryptoPP::byte> &cipher) {
    // cout << "ENCRYPTION SIZE: " << metadata.encrypted.size() << endl;
        vector<CryptoPP::byte> recovered;
        try {
            CBC_Mode<AES>::Decryption decryption;
            decryption.SetKeyWithIV(key_, AES::DEFAULT_KEYLENGTH, iv_);

            // Decrypt
            ArraySource(cipher.data(), cipher.size(), true,
                        new StreamTransformationFilter(decryption,
                                                    new VectorSink(recovered)
                                                    ) // StreamTransformationFilter
                    ); // ArraySource
        } catch (const CryptoPP::Exception& ex) {
            throw runtime_error("Decryption failed: " + string(ex.what()));
        }
        return recovered;
}





