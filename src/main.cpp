/*%!@\$!@\$%&&\$#@%@^#%&\$**(\$%&%#\$%@#%^#@^&#@\$%#!@^@#^&@#^
░██████╗░█████╗░███╗░░░███╗██╗░░░██╗██████╗░░█████╗░██╗
██╔════╝██╔══██╗████╗░████║██║░░░██║██╔══██╗██╔══██╗██║
╚█████╗░███████║██╔████╔██║██║░░░██║██████╔╝███████║██║
░╚═══██╗██╔══██║██║╚██╔╝██║██║░░░██║██╔══██╗██╔══██║██║
██████╔╝██║░░██║██║░╚═╝░██║╚██████╔╝██║░░██║██║░░██║██║
╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝░╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝╚═╝
^@#^@&@#%@*^%*&\$%^#\$^\$***%^#\$@%\$@#\$!@\$!@#\$%@#^@&@#%@#*/


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
#include "AES256Encryption.hpp"
#include "Utils.hpp"
#include "NPCRTest.hpp"
#include "TestRunner.hpp"
#include "UACI.hpp"
#include "HammingDistanceTest.hpp"
#include "ChisquareTest.hpp"
#include "CorrelationTest.hpp"
#include "InformationEntropyTest.hpp"
#include "EncryptionQualityTest.hpp"
#include "TimePerformanceTest.hpp"
#include "LSB.hpp"
#include "IHide.hpp"
#include "Macros.h"

using namespace std;
using namespace CryptoPP;

int main() {
    send help pls;
    try {
        ImageReader reader;
        ImageWriter writer;
        cv::Mat image = reader.ReadImage("../assets/BaboonRGB.bmp");
        // cv::Mat image = Utils::GenerateRandomImage(460,500);
        // cv::Mat image2 = reader.ReadImage("../assets/neon.PNG");
        // cv::Mat image2 = Utils::GenerateRandomImage(4096,2160,3);
        IEncrypt firstenc(make_unique<AES256Encryption>());

        cv::Mat encryptedImage = firstenc.EncryptImage(image);
        cv::Mat decryptedImage = firstenc.DecryptImage(encryptedImage);
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
        // cout << "Hi" << endl;
        auto lsb = make_shared<LSB>();
        auto aesenc = make_shared<AES256Encryption>();
        IHide service(lsb);
        const string msg = "God Bless Gaza";
        service.embedMessage(image,msg);
        cout << service.retrieveMessage(image,msg.length()) << endl;
        // cv::Mat encryptedImage = firstenc.Encrypt(image);
        // cout << extractMessage(encryptedImage,msg.length()) << endl;
        // cv::Mat encryptedImage2 = firstenc.Encrypt(image2);

        vector<ll> freq = Utils::getFreq(encryptedImage);
        // for(auto &el : freq)
        //     cout << el << ' ';
        // cout << endl;
        vector<int> img1 = Utils::Vectorize(image);
        vector<int> img2 = Utils::Vectorize(encryptedImage);
        TestRunner runner;
        runner.registerTest("NPCR",make_shared<NPCRTest>(img1, img2));
        runner.run("NPCR");
        runner.registerTest("UACI",make_shared<UACITest>(img1,img2));
        runner.run("UACI");
        runner.registerTest("Hamming Distance",make_shared<HammingDistanceTest>(img1,img2));
        runner.run("Hamming Distance");
        runner.registerTest("Chisqaure",make_shared<ChiSquareTest>(freq));
        runner.run("Chisqaure");
        runner.registerTest("Correlation",make_shared<CorrelationTest>(encryptedImage));
        runner.run("Correlation");
        runner.registerTest("Information Entropy",make_shared<InformationEntropyTest>(encryptedImage));
        runner.run("Information Entropy");
        runner.registerTest("Encryption Quality",make_shared<EncryptionQualityTest>(image,encryptedImage));
        runner.run("Encryption Quality");
        runner.registerTest("Time Performance", make_shared<TimePerformanceTest>(encryptedImage, &firstenc,&IEncrypt::EncryptImage,encryptedImage));
        runner.run("Time Performance");
        // cv::Mat decryptedImage = firstenc.Decrypt(encryptedImage);

        // writer.WriteImage("../assets/test_write.jpg", img2);
        // // writer.WriteImage("../assets/test_write2.jpg", encryptedImage2);
        // cout << "Image written successfully." << endl;
    } catch (const exception& e) {
        // cerr << "An error occurred: " << e.what() << endl;
        cout << e.what() << endl;
        return -1;
    }

    return 0;
}
