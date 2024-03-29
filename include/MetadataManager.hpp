#ifndef METADATAMANAGER_HPP
#define METADATAMANAGER_HPP

#include "Metadata.hpp"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>

using namespace std;


class MetadataManager {
private:
    map<string, Metadata> metadataMap;

public:
    string SHA256HashString(const std::string& input) {
        std::string output;

        CryptoPP::SHA256 hash;

        CryptoPP::StringSource ss(input, true,
            new CryptoPP::HashFilter(hash,
                new CryptoPP::HexEncoder(
                    new CryptoPP::StringSink(output)
                )
            )
        );

        return output;
    }
    void storeMetadata(Metadata& metadata, const string &encryptedDataString) {
        // string encryptedDataString(encryptedData.begin(),encryptedData.end());
        cout << encryptedDataString[234] << endl;
        string hashedEncryptedDataString = SHA256HashString(encryptedDataString);
        cout << hashedEncryptedDataString << endl;
        metadataMap[hashedEncryptedDataString] = metadata;
    }
    Metadata getMetadata(const string &encryptedDataString) {
        // string encryptedDataString (encryptedData.begin(),encryptedData.end());
        cout << encryptedDataString[234] << endl;
        string hashedEncryptedDataString = SHA256HashString(encryptedDataString);
        cout << hashedEncryptedDataString << endl;
        for(auto &el : metadataMap)
            cout << el.second.width <<endl;
        return metadataMap[hashedEncryptedDataString];
    }
};

#endif
