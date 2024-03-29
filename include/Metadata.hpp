#ifndef METADATA_HPP
#define METADATA_HPP

#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;

struct Metadata {
    long int width;
    long int height;
    int channels;
    vector<CryptoPP::byte> encrypted;
};

#endif
