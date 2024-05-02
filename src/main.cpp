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
#include "AES256Encryption.h"
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
#include <string>
#include "UnitTest.hpp"
#include "PrepareTesting.cpp"
// #include "LogMacros.h"

using namespace std;
// using namespace CryptoPP;

void WelcomeUser() {
    cout << "Hi" << endl;
}

// int main() {
//     send help pls;
//     try {
//         cout << shared << endl;
//         ImageWriter writer;
//         ImageReader reader;
//         cv::Mat image = reader.ReadImage("../assets/BaboonRGB.bmp");
//         // cv::Mat image = Utils::GenerateRandomImage(460,500);
//         // cv::Mat image2 = reader.ReadImage("../assets/neon.PNG");
//         // cv::Mat image2 = Utils::GenerateRandomImage(4096,2160,3);
//         IEncrypt firstenc(make_unique<AES256Encryption>());

//         cv::Mat encryptedImage = firstenc.EncryptImage(image);
//         cv::Mat decryptedImage = firstenc.DecryptImage(encryptedImage);

//         vector<int> img1 = Utils::Vectorize(image);
//         vector<int> img2 = Utils::Vectorize(encryptedImage);

//         TestRunner runner;
//         UnitTest us;
//         shared_ptr<ITest> NPCR = make_shared<NPCRTest>(img1, img2);

//         us.addTest("NPCR",NPCR);
//         us.runAllTests(runner);

//         // string secretmsg = "Hi bruv";
//         // vector<uint8_t> messageData(secretmsg.begin(),secretmsg.end());
//         // LSB lsbsteg;
// // 
//         // cv::Mat stegoImage = lsbsteg.hideData(image,messageData);
// // 
//         // int originalMessageSize = secretmsg.length();
//         // vector<uint8_t> extractData = lsbsteg.retrieveData(stegoImage,originalMessageSize);
//         // string extractedMessage(extractData.begin(), extractData.end());
//         // cout << extractedMessage << endl;

//         // hideMessage(image,msg);
//         // cout << "Hi" << endl;
//         // auto lsb = make_shared<LSB>();
//         // auto aesenc = make_shared<AES256Encryption>();
//         // IHide service(lsb);
//         // const string msg = "God Bless Gaza";
//         // service.embedMessage(image,msg);
//         // cout << service.retrieveMessage(image,msg.length()) << endl;
//         // // cv::Mat encryptedImage = firstenc.Encrypt(image);
//         // // cout << extractMessage(encryptedImage,msg.length()) << endl;
//         // // cv::Mat encryptedImage2 = firstenc.Encrypt(image2);

//         // vector<ll> freq = Utils::getFreq(encryptedImage);
//         // // for(auto &el : freq)
//         // //     cout << el << ' ';
//         // // cout << endl;
//         // vector<int> img1 = Utils::Vectorize(image);
//         // vector<int> img2 = Utils::Vectorize(encryptedImage);
//         // TestRunner runner;
//         // runner.registerTest("NPCR",make_shared<NPCRTest>(img1, img2));
//         // runner.run("NPCR");
//         // runner.registerTest("UACI",make_shared<UACITest>(img1,img2));
//         // runner.run("UACI");
//         // runner.registerTest("Hamming Distance",make_shared<HammingDistanceTest>(img1,img2));
//         // runner.run("Hamming Distance");
//         // runner.registerTest("Chisqaure",make_shared<ChiSquareTest>(freq));
//         // runner.run("Chisqaure");
//         // runner.registerTest("Correlation",make_shared<CorrelationTest>(encryptedImage));
//         // runner.run("Correlation");
//         // runner.registerTest("Information Entropy",make_shared<InformationEntropyTest>(encryptedImage));
//         // runner.run("Information Entropy");
//         // runner.registerTest("Encryption Quality",make_shared<EncryptionQualityTest>(image,encryptedImage));
//         // runner.run("Encryption Quality");
//         // runner.registerTest("Time Performance", make_shared<TimePerformanceTest>(encryptedImage, &firstenc,&IEncrypt::EncryptImage,encryptedImage));
//         // runner.run("Time Performance");
//         // cv::Mat decryptedImage = firstenc.Decrypt(encryptedImage);

//         // writer.WriteImage("../assets/test_write.jpg", img2);
//         // // writer.WriteImage("../assets/test_write2.jpg", encryptedImage2);
//         // cout << "Image written successfully." << endl;
//     } catch (const exception& e) {
//         // cerr << "An error occurred: " << e.what() << endl;
//         cout << e.what() << endl;
//         return -1;
//     }

//     return 0;
// }

// void generateKey() {

// }

signed main() {
    // send help pls;
    WelcomeUser();
    short choice;
    cout << "Kindly, enter the path of target image.\n";

    string path;
    getline(cin, path);
    ImageReader reader;
    ImageWriter writer;
    cv::Mat image = reader.ReadImage("../assets/BaboonRGB.bmp"); // add image generation.
    string key;

    IEncrypt iEncrypt(make_unique<AES256Encryption>()); // as we're just interested in the AES encryption.
    cout << IEncrypt::checkIsInstantiated() << endl;
    system("clear");
    while (true) {
        cout << "Choose an option:\n";
        cout << "1. Encrypt image\n";
        cout << "2. Decrypt image\n";
        cout << "3. Test my image :fire:\n";
        cout << "4. Exit\n";
        cin >> choice;
        system("clear");
        switch(choice) {
            case 1: {
                cout << "1. Enter an existing key.\n";
                cout << "2. Generate a new key \n";
                cin >> choice;
                system("clear");
                if(choice == 1) {
                    cout << "Kindly, input your key.\n";
                    // LOG_WARNING("Kindly, input your key.");
                    cin >> key;
                }
                else if(choice == 2) {
                    // generateKey(key);
                    // LOG_INFO("Key has been generated");
                    cout << "Key has been generated\n";
                }
                else {
                    // generateKey(key);
                    // LOG_ERROR("Invalid option. A key has been generated.");
                    cout <<"Invalid option. A key has been generated." << endl;
                }
                cv::Mat img = iEncrypt.EncryptImage(image);
                writer.WriteImage("../assets/EncryptedImage.bmp",img);
                break;
            }
            case 2: {
                cout << "1. Enter an existing key.\n";
                cout << "2. Decrypt using cached keys. \n";
                cout << "\t |==+=+==> Works only upon saved sessions, else you need to save the key used.\n"; 
                cin >> choice;
                system("clear");
                if(choice == 1) {
                    dist:
                        cout << "Kindly, input your key.\n";
                        // LOG_WARNING("Kindly, input your key.");
                        cin >> key;
                        iEncrypt.changeKey(key);
                }
                else if(choice == 2) {
                    // generateKey(key);
                    // LOG_INFO("Key has been generated");
                    if(IEncrypt::checkIsInstantiated()) {
                        if(iEncrypt.isNotCached()) {
                            cout << "No work has been cached. Please enter a key.\n";
                            goto dist;
                        }
                    }
                    cout << "Key has been generated\n";
                }
                else {
                    // generateKey(key);
                    // LOG_ERROR("Invalid option. A key has been generated.");
                    cout <<"Invalid option. A key has been generated." << endl;
                }
                cv::Mat img = reader.ReadImage("../assets/EncryptedImage.bmp"); 
                cv::Mat decryptedImg = iEncrypt.DecryptImage(img);
                writer.WriteImage("../assets/DecryptedImage.jpg",decryptedImg);
                break;
            }
            case 3: {
                // cout <<"Testing.." << endl;
                cv::Mat img = reader.ReadImage("../assets/BaboonRGB.bmp"); 
                cv::Mat encryptedImage = reader.ReadImage("../assets/EncryptedImage.bmp");
                cout << "Kindly, provide us with the paths of these respectively:\n - Non-Encrypted Image \n - Encrypted Version of the same Image.\n";
                string path1,path2; cin >> path1 >> path2;
                InitializeAndRunTests(img,encryptedImage,iEncrypt);
                break;
            }
            case 4: {
                // LOG_INFO("Exiting Program.");
                cout << "Exiting Program\n";
                return 0;
            }
            default: {
                // LOG_ERROR("Invalid Option.");
                cout << "Invalid Option\n";
                return 0;
            }
        }
    }

}