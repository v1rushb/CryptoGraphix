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
    string SHA256HashString(const string& input) {
        string output;

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

    void storeMetadata(Metadata &metadata, const string &encryptedDataString) {
        string hashedEncryptedDataString = SHA256HashString(encryptedDataString);
        metadataMap[hashedEncryptedDataString] = metadata;
    }

    Metadata getMetadata(const string &encryptedDataString) {
        string hashedEncryptedDataString = SHA256HashString(encryptedDataString);
        if (metadataMap.find(hashedEncryptedDataString) != metadataMap.end()) {
            return metadataMap[hashedEncryptedDataString];
        } else {
            throw runtime_error("Metadata not found for the given encrypted data string.");
        }
    }

    bool isEmpty() {
        return !metadataMap.size();
    }
};

#endif
