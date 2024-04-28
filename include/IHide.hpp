#ifndef IHIDE_HPP
#define IHIDE_HPP

#include "HidingStrategy.hpp"
#include "EncryptionStrategy.hpp"
#include "IEncrypt.hpp"
#include "Utils.hpp"

#include <typeinfo>


class IHide {
private:
    shared_ptr<HidingStrategy> hide;
    shared_ptr<IEncrypt> encryptor;

public:
    IHide(shared_ptr<HidingStrategy> hid,shared_ptr<IEncrypt> encrypt = nullptr) 
        : hide(hid), encryptor(encrypt) {}

    void embedMessage(cv::Mat& img, const string& message, bool useEncryption = 0) {
        string newMessage = message;
        cout << typeid(newMessage).name() << endl;
        if(useEncryption && encryptor) {
            vector<CryptoPP::byte> encrypted = encryptor->EncryptText(Utils::StringToByteVector(message));
            newMessage =  Utils::ByteVectorToString(encrypted);
        }
        hide->hideMessage(img,newMessage);
    }

    string retrieveMessage(cv::Mat& img, int messageLength, bool useDecryption = 0) {
        string extractedMessage = hide->extractMessage(img,messageLength);

        if (useDecryption && encryptor) {
            // cout << typeid(extractedMessage).name() << endl;
            vector<CryptoPP::byte> decrypted = encryptor->DecryptText(Utils::StringToByteVector(extractedMessage));
            extractedMessage = Utils::ByteVectorToString(decrypted);
        }

        return extractedMessage;
    }
};

#endif
