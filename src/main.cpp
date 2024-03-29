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

using namespace std;
using namespace CryptoPP;

#define all(v) v.begin(),v.end();
#define ll long long int

int main() {
    try {
        ImageReader reader;
        ImageWriter writer;
        cv::Mat image = reader.ReadImage("../assets/besho.jpg");
        // cv::Mat image = Utils::GenerateRandomImage(460,500);
        cv::Mat image2 = reader.ReadImage("../assets/neon.PNG");
        // cv::Mat image2 = Utils::GenerateRandomImage(4096,2160,3);
        IEncrypt firstenc(make_unique<AES256Encryption>());
        cv::Mat encryptedImage = firstenc.Encrypt(image);
        cv::Mat encryptedImage2 = firstenc.Encrypt(image2);

        // vector<int> img1 = {1,23,12,41,41,23,12,512,3,12,5412,3,12,5412,3,123,1254,123,12,4123,12};
        // vector<int> img1;
        // for(int o = 0; o < 10000;o++)
        //     img1.push_back(o%256);
        // vector<int> img2(img1.rbegin(),img1.rend());
        // vector<ll> freq = Utils::getFreq(image);
        // TestRunner runner;
        // runner.registerTest("NPCR",make_shared<NPCRTest>(img1, img2));
        // runner.run("NPCR");
        // runner.registerTest("UACI",make_shared<UACITest>(img1,img2));
        // runner.run("UACI");
        // runner.registerTest("Hamming Distance",make_shared<HammingDistanceTest>(img1,img2));
        // runner.run("Hamming Distance");
        // runner.registerTest("Chisqaure",make_shared<ChiSquareTest>(freq));
        // runner.run("Chisqaure");
        // runner.registerTest("Correlation",make_shared<CorrelationTest>(image2));
        // runner.run("Correlation");
        // runner.registerTest("Information Entropy",make_shared<InformationEntropyTest>(image2));
        // runner.run("Information Entropy");
        // IEncrypt encryptor(make_unique<AES256Encryption>());
        // cv::Mat newImage2 = encryptor.Encrypt(image2);
        // runner.registerTest("Encryption Quality",make_shared<EncryptionQualityTest>(image,newImage2));
        // runner.run("Encryption Quality");
        cv::Mat decryptedImage = firstenc.Decrypt(encryptedImage);
        cv::Mat decryptedImage2 = firstenc.Decrypt(encryptedImage2);

        writer.WriteImage("../assets/test_write.jpg", decryptedImage);
        writer.WriteImage("../assets/test_write2.jpg", decryptedImage2);
        cout << "Image written successfully." << endl;
    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return -1;
    }

    return 0;
}
