#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <algorithm>
#include <numeric>
#include <cryptopp/hex.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace CryptoPP;

#define ll long long int
#define all(v) v.begin(),v.end()
#define endl '\n'

const string outputDirectory = "./resources/";
const string src = "./assets/";

// vector<unsigned char> readImage(const string &imagePath) {
//     ifstream file(imagePath, ios::binary);
//     if (!file) {
//         cout << "Cannot open the image with path: " << imagePath << endl;
//         return {};
//     }
//     file.seekg(0, ios::end);
//     streamsize size = file.tellg();
//     file.seekg(0, ios::beg);

//     vector<unsigned char> buffer(size);
//     if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
//         cout << "Cannot read the image with path: " << imagePath << endl;
//         return {};
//     }
//     return buffer;
// }

// bool writeImage(const string &distPath, const vector<unsigned char> &imageData) {
//     ofstream file(distPath, ios::binary | ios::out);
//     if (!file) {
//         cout << "Cannot open the file for writing: " << distPath << endl;
//         return false;
//     }

//     if (!file.write(reinterpret_cast<const char*>(imageData.data()), imageData.size())) {
//         cout << "Cannot write to file: " << distPath << endl;
//         return false;
//     }
//     return true;
// }

cv::Mat readImage(const string &imagePath) {
    cv::Mat image = cv::imread(imagePath,cv::IMREAD_COLOR);
    if(image.empty()) {
        cerr << "Cannot open the image with path: " << imagePath << endl;
    }
    return image;
}

void writeImage(const string &outputPath, const cv::Mat &image) {
    if (!filesystem::exists(outputDirectory)) {
        filesystem::create_directory(outputDirectory);
    }

    if(!cv::imwrite(outputPath,image)) {
        cerr << "Cannot write to file: " << outputPath << endl;
    }
    cout << "Written successfully, Path:" << outputPath << endl;
}

void modifyImage(cv::Mat &image) {
    unsigned char &val = (image.channels() != 3? image.at<uchar>(0,0) : image.at<cv::Vec3b>(0,0)[0]);
    val ^=1;
}


vector<unsigned char> encryptImage(const vector<unsigned char> &data, const SecByteBlock &key, const CryptoPP::byte iv[AES::BLOCKSIZE]) {
    string encrypted;
    try {
        CBC_Mode<AES>::Encryption encryptor;
        encryptor.SetKeyWithIV(key, key.size(), iv);
        ArraySource(reinterpret_cast<const CryptoPP::byte*>(data.data()), data.size(), true,
            new StreamTransformationFilter(encryptor,
                new StringSink(encrypted)
            )
        );
    } catch (const Exception &e) {
        cerr << e.what() << endl;
        exit(1);
    }
    return vector<unsigned char>(all(encrypted));
}

vector<unsigned char> vectorize(const cv::Mat &image) {
    vector<unsigned char> buffer;
    const string ext = ".jpg";
    if(!cv::imencode(ext,image,buffer)) {
        throw runtime_error("Failed to encode.");
    }
    return buffer;
}

cv::Mat matricize(const vector<unsigned char> &data) {
    cv:: Mat image= cv::imdecode(cv::Mat(data),cv::IMREAD_UNCHANGED);
    if(image.empty()) {
        throw runtime_error("Failed to decode.");
    }
    return image;
}

vector<char> decryptImage(const vector<char> &data, const SecByteBlock &key, const CryptoPP::byte iv[AES::BLOCKSIZE]) {
    string decrypted;
    try {
        CBC_Mode<AES>::Decryption decryptor;
        decryptor.SetKeyWithIV(key, key.size(), iv);
        ArraySource(reinterpret_cast<const CryptoPP::byte*>(data.data()), data.size(), true,
            new StreamTransformationFilter(decryptor,
                new StringSink(decrypted)
            )
        );
    } catch (const Exception &e) {
        cerr << e.what() << endl;
        exit(1);
    }
    return vector<char>(all(decrypted));
}

double NPCR(const vector<char> &img1, const vector<char> &img2) {
    if(img1.size() - img2.size())
    {
        cerr << "SizeDifferenceException" << endl;
        exit(1);
    }
    
    ll diff(0);
    for(ll o = 0; o < img1.size();o++)
        diff+=img1[o]!=img2[o];
    return (diff / (double) img1.size()) * 100.0;
}

double UACI(const vector<char> &img1, const vector<char> &img2) {
    if(img1.size()-img2.size())
    {
        cerr << "SizeDifferenceException" << endl;
        exit(1);
    }
    double s(0);
    for(ll o = 0; o < img1.size();o++) {
        s+=abs(static_cast<unsigned char>(img1[o]) - static_cast<unsigned char>(img2[o]))/255.0;
    }
    return (s/img1.size())*100.0;
}

double hammingDistance(const vector<char> &img1, const vector<char> &img2) {
    if(img1.size()-img2.size()) 
    {
        cerr << "SizeDiffernceException" << endl;
        exit(1);
    }

    ll dist(0);
    for(int o = 0; o < img1.size();o++)
    {
        ll x = (static_cast<unsigned char>(img1[o])) ^ (static_cast<unsigned char>(img2[o]));
        for(int bit = 0; bit < 8;bit++) {
            dist += (x >> bit) &1;
        }
    }
    return (dist/ (double) (img1.size()*8)) * 100;
}

vector<ll> getFreq(const vector<char> &img) {
    vector<ll> freq(256,0);
    for(int o = 0; o < img.size();o++)
        freq[static_cast<unsigned int>(static_cast<unsigned char>(img[o]))]++;
    return freq;
}

// map<ll,ll> getFreq(const vector<char> &img) {
//     map<ll,ll> mp;
//     for(int o = 0; o < img.size();o++)
//         mp[static_cast<unsigned int>(static_cast<unsigned char>(img[o]))]++;
//     return mp;
// }

// vector<ll> freq(vector<char> &original, vector<char> &encrypted) {
//     vector<ll> ogFreq = getFreq(original),encFreq = getFreq(encrypted);
// }

bool chiSqaure(const vector<ll> &freq) {
    const ll sum = accumulate(all(freq), 0);
    const double expectedFreq = (double) sum/256.0;
    double s(0);
    for(ll el : freq) {
        double x = el - expectedFreq;
        s+=((x*x)/expectedFreq);
    }
    const double criticalVal = 293.2478; 
    cout << s;
    return s < criticalVal;
}

//Helper functions.

void printKey(const SecByteBlock &key) {
    string hexKey;
    HexEncoder encoder;

    encoder.Attach(new StringSink(hexKey));
    encoder.Put(key,key.size());
    encoder.MessageEnd();

    cout << hexKey << endl;
} 

int32_t main() {
    const string str = "neon.jpg";
    string imagePath = src + str;
    string encryptedPath = outputDirectory + "encrypted_img.jpeg";
    string decryptedPath = outputDirectory + "decrypted_img.jpeg";
    cv::Mat colorImage = readImage(imagePath);
    if(colorImage.empty()) {
        cout << "Empty image" << endl;
        return -1;
    }
    cv::Mat modifiedColorImage = colorImage.clone();
    modifyImage(modifiedColorImage);

    vector<unsigned char> imageDate = vectorize(colorImage);

    // cv::Vec3b pixelValue = colorImage.at<cv::Vec3b>(1,1);
    // for(int o = 0; o < colorImage.rows;o++) {
    //     for(int i = 0; i < colorImage.cols;i++) {
    //         unsigned char &green = colorImage.at<cv::Vec3b>(o,i)[2];
    //         int val = green + 100;
    //         green = (unsigned char) min(max(val,0),255);
    //     }
    // }
    // cout << colorImage.at<cv::Vec3b>(0,0)[0] << endl;
    // cout << modifiedColorImage.at<cv::Vec3b>(0,0)[0] << endl;

    AutoSeededRandomPool prng;
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    prng.GenerateBlock(key, key.size());
    CryptoPP::byte iv[AES::BLOCKSIZE];
    prng.GenerateBlock(iv, sizeof(iv));

    vector<unsigned char> encryptedData= encryptImage(colorImage,key,iv);
    cv::Mat decryptedImage = matricize(encryptedData);
    
    writeImage(encryptedPath,decryptedImage);
    // writeImage(encryptedPath,colorImage);


    return 0;
}