#ifndef IHIDE_HPP
#define IHIDE_HPP

#include "HidingStrategy.hpp"
#include "EncryptionStrategy.hpp"
#include "IEncrypt.hpp"
#include "Utils.hpp"


class IHide {
private:
    shared_ptr<HidingStrategy> hide;
    shared_ptr<IEncrypt> encryptor;

public:
    IHide(shared_ptr<HidingStrategy> hid,shared_ptr<IEncrypt> encrypt = nullptr) 
        : hide(hid), encryptor(encrypt) {}

    void embedMessage(cv::Mat& img, const string& message, bool useEncryption = 0) {
        string newMessage = message;
        if(useEncryption && encryptor) {
            vector<CryptoPP::byte> encrypted = encryptor->Encrypt(Utils::StringToByteVector(message));
            newMessage =  Utils::ByteVectorToString(encrypted);
        }
        hide->hideMessage(img,newMessage);
    }

    string retrieveMessage(cv::Mat& img, int messageLength, bool useDecryption = 0) {
        string extractedMessage = hide->extractMessage(img,messageLength);

        if (useDecryption && encryptor) {
            vector<CryptoPP::byte> decrypted = encryptor->Decrypt(stringToVectorByte(extractedMessage));
            extractedMessage = Utils::ByteVectorToString(decrypted);
        }

        return extractedMessage;
    }
};

#endif
