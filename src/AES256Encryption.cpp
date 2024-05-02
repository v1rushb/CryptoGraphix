#include "AES256Encryption.h"
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

// void setKey(const CryptoPP::SecByteBlock & key) {
//     key_ = key;
// }

void AES256Encryption::GenerateKeyAndIV() {
    AutoSeededRandomPool rnd;
    key_.resize(AES::DEFAULT_KEYLENGTH);
    rnd.GenerateBlock(key_,key_.size());
    rnd.GenerateBlock(iv_,sizeof(iv_));
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
            throw runtime_error("Why does it have to be an error all the time?" + string(ex.what()));
        }
    return cipher;
}

vector<CryptoPP::byte> AES256Encryption::Decrypt(const vector<CryptoPP::byte> &cipher) {
        vector<CryptoPP::byte> recovered;
        try {
            CBC_Mode<AES>::Decryption decryption;
            decryption.SetKeyWithIV(key_, AES::DEFAULT_KEYLENGTH, iv_);
            ArraySource(cipher.data(), cipher.size(), true,
                        new StreamTransformationFilter(decryption,
                                                    new VectorSink(recovered)
                                                    )
                    );
        } catch (const CryptoPP::Exception& ex) {
            throw runtime_error("Decryption failed: " + string(ex.what()));
        }
        return recovered;
}