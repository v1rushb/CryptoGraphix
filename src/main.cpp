#include "ImageReader.h"
#include "ImageWriter.h"
#include <iostream>
// #include "AESImageEncryptor.h"
#include "IEncrypt.hpp"
#include <cryptopp/osrng.h>
#include <vector>
#include <utility>
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
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/ccm.h>
#include <cryptopp/base64.h>
#include <opencv2/opencv.hpp>
#include <bitset>
#include "AES256Encryption.hpp"
#include "Utils.hpp"
#include "NPCRTest.hpp"
#include "UACI.hpp"
#include "HammingDistanceTest.hpp"
#include "ChisquareTest.hpp"
#include "CorrelationTest.hpp"
#include "InformationEntropyTest.hpp"
#include "EncryptionQualityTest.hpp"
#include "LSB.hpp"
#include <bitset>
#include "IHide.hpp"

using namespace std;
using namespace CryptoPP;

#define all(v) v.begin(),v.end();
#define ll long long int
#define ull unsigned long long

// void hideMessage(cv::Mat &img, const string &message) {
//     if(message.size() > img.cols * img.rows) {
//         cerr << "Too large for LSB." << endl;
//         return;
//     }
//     string data;
//     for(char ch : message) {
//         bitset<8> bits(static_cast<ull>(ch));
//         data+=bits.to_string();
//     }

    
//     int bitIndex(0);
//     for(int o = 0; o < img.rows && bitIndex < data.size(); o++) {
//         for(int i = 0; i  < img.cols && bitIndex < data.size();i++) {

//             if(img.channels() == 3) {
//                 cv::Vec3b &pixel = img.at<cv::Vec3b>(o,i);
//                 uchar &blue = pixel[0];
//                 if(data[bitIndex] =='1') {
//                     blue |=1;
//                 } else {
//                     blue &= ~1;
//                 }
//             } else {
//                 uchar &wb = img.at<uchar>(o,i);
//                 if(data[bitIndex] =='1') {
//                     wb |=1;
//                 } else {
//                     wb &= ~1;
//                 }
//             }
//             ++bitIndex;
//         }
//     }
// }

// string extractMessage(const cv::Mat &img, int len) {
//     len*=8;
//     string data;
//     int bitIndex(0);
//     for(int o = 0; o < img.rows && bitIndex < len; o++) {
//         for(int i = 0; i  < img.cols && bitIndex < len;i++) {
//             if(img.channels() == 3) {
//             uchar blue = img.at<cv::Vec3b>(o,i)[0];
//             data += to_string(blue&1);
//             } else {
//                 uchar wb = img.at<uchar>(o,i);
//                 data+=to_string(wb&1);
//             }
//             ++bitIndex;             
//         }
//     }

//     string msg;
//     for(int o = 0; o < data.size();o+=8) {
//         bitset<8> bits(data.substr(o,8));
//         msg += static_cast<char>(bits.to_ulong());
//     }
//     return msg;
// }


int main() {
    try {
        ImageReader reader;
        ImageWriter writer;
        cv::Mat image = reader.ReadImage("../assets/BaboonRGB.bmp");
        // cv::Mat image = Utils::GenerateRandomImage(460,500);
        // cv::Mat image2 = reader.ReadImage("../assets/neon.PNG");
        // cv::Mat image2 = Utils::GenerateRandomImage(4096,2160,3);
        IEncrypt firstenc(make_unique<AES256Encryption>());
        // string secretmsg = "Hi bruv";
        // vector<uint8_t> messageData(secretmsg.begin(),secretmsg.end());
        // LSB lsbsteg;
// 
        // cv::Mat stegoImage = lsbsteg.hideData(image,messageData);
// 
        // int originalMessageSize = secretmsg.length();
        // vector<uint8_t> extractData = lsbsteg.retrieveData(stegoImage,originalMessageSize);
        // string extractedMessage(extractData.begin(), extractData.end());
        // cout << extractedMessage << endl;

        // hideMessage(image,msg);
        // // cout << "Hi" << endl;
        auto lsb = make_shared<LSB>();
        IHide service(lsb);
        const string msg = "God Bless Gaza";
        service.embedMessage(image,msg);
        cout << service.retrieveMessage(image,msg.length()) << endl;
        // cv::Mat encryptedImage = firstenc.Encrypt(image);
        // cout << extractMessage(encryptedImage,msg.length()) << endl;
        // cv::Mat encryptedImage2 = firstenc.Encrypt(image2);

        // vector<ll> freq = Utils::getFreq(encryptedImage);
        // for(auto &el : freq)
        //     cout << el << ' ';
        // cout << endl;
        // vector<int> img1 = Utils::Vectorize(image);
        // vector<int> img2 = Utils::Vectorize(encryptedImage);
        // TestRunner runner;
        // runner.registerTest("NPCR",make_shared<NPCRTest>(img1, img2));
        // runner.run("NPCR");
        // runner.registerTest("UACI",make_shared<UACITest>(img1,img2));
        // runner.run("UACI");
        // runner.registerTest("Hamming Distance",make_shared<HammingDistanceTest>(img1,img2));
        // runner.run("Hamming Distance");
        // runner.registerTest("Chisqaure",make_shared<ChiSquareTest>(freq));
        // runner.run("Chisqaure");
        // runner.registerTest("Correlation",make_shared<CorrelationTest>(encryptedImage));
        // runner.run("Correlation");
        // runner.registerTest("Information Entropy",make_shared<InformationEntropyTest>(encryptedImage));
        // runner.run("Information Entropy");
        // runner.registerTest("Encryption Quality",make_shared<EncryptionQualityTest>(image,encryptedImage));
        // runner.run("Encryption Quality");
        // cv::Mat decryptedImage = firstenc.Decrypt(encryptedImage);

        // writer.WriteImage("../assets/test_write.jpg", encryptedImage);
        // // writer.WriteImage("../assets/test_write2.jpg", encryptedImage2);
        // cout << "Image written successfully." << endl;
    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return -1;
    }

    return 0;
}
