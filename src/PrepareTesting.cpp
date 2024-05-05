#ifndef PREPARETESTING_CPP
#define PREPARETESTING_CPP

#include <vector>
#include "Utils.hpp"
#include "IEncrypt.hpp"

// void InitializeAndRunTests(const cv::Mat &image, const cv::Mat &encryptedImage, IEncrypt &iEncrypt) {
//         TestRunner runner;
//         UnitTest us;
        
//         vector<int> img1 = Utils::Vectorize(image);
//         vector<int> img2 = Utils::Vectorize(encryptedImage);
//         vector<ll> freq = Utils::getFreq(encryptedImage);

//         us.addTest("NPCR",make_shared<NPCRTest>(img1, img2));
//         us.addTest("UACI",make_shared<UACITest>(img1,img2));
//         us.addTest("Hamming Distance",make_shared<HammingDistanceTest>(img1,img2));
//         us.addTest("Chisqaure",make_shared<ChiSquareTest>(freq));
//         us.addTest("Correlation",make_shared<CorrelationTest>(encryptedImage));
//         us.addTest("Information Entropy",make_shared<InformationEntropyTest>(encryptedImage));
//         us.addTest("Encryption Quality",make_shared<EncryptionQualityTest>(image,encryptedImage));
//         us.addTest("Time Performance",make_shared<TimePerformanceTest>(encryptedImage, &iEncrypt,&IEncrypt::EncryptImage,encryptedImage));
//         us.runAllTests(runner);
// }

class PrepareTesting { // normal image!
        private:
                UnitTest us;
                TestRunner runner;
                const cv::Mat &image1;
                const cv::Mat &image2;
                IEncrypt &iEncrypt;
                map<string,bool> selected;
                vector<string> tests = {"NPCR","UACI", "Hamming Distance", "Correlation","Information Entropy", "Encryption Qaulity", "Time Performance"};
        public:
                PrepareTesting(const cv::Mat &img1,const cv::Mat &img2, IEncrypt &encryptor)
                        : image1(img1), image2(img2), iEncrypt(encryptor) {}

                void InitializeMap(const vector<bool> &d) {
                        for(int o = 0; o < tests.size();o++) {
                                selected[tests[o]] = d[o];
                        }
                }
                bool validateTests(const vector<bool> &selectedTests) {
                        InitializeMap(selectedTests);
                        for(auto &el : selected) {
                                if(el.second) {
                                        if(find(tests.begin(),tests.end(), el.first) == tests.end()) {
                                                return false;
                                        }
                                }
                        }
                        return true;
                }
                void InitalizeTests(const vector<bool> &selectedTests) {
                        
                        if(!validateTests(selectedTests)) {
                                throw runtime_error("Invalid tests name\n");
                        }

                        vector<int> img1 = Utils::Vectorize(image1);
                        vector<int> img2 = Utils::Vectorize(image2);
                        vector<ll> freq = Utils::getFreq(image2);
                        if(selected["NPCR"]) {
                                us.addTest("NPCR",make_shared<NPCRTest>(img1, img2));
                        }
                        if(selected["UACI"]) {
                                us.addTest("UACI",make_shared<UACITest>(img1,img2));
                        }
                        if(selected["Hamming Distance"]) {
                                us.addTest("Hamming Distance",make_shared<HammingDistanceTest>(img1,img2));
                        }
                        if(selected["Chisqaure"]) {
                                us.addTest("Chisqaure",make_shared<ChiSquareTest>(freq));

                        }
                        if(selected["Correlation"]) {
                                us.addTest("Correlation",make_shared<CorrelationTest>(image2));
                        }
                        if(selected["Information Entropy"]) {

                                us.addTest("Information Entropy",make_shared<InformationEntropyTest>(image2));
                        }
                        if(selected["Encryption Quality"]) {
                                us.addTest("Encryption Quality",make_shared<EncryptionQualityTest>(image1,image2));
                        }
                        if(selected["Time Performance"]) {
                                us.addTest("Time Performance",make_shared<TimePerformanceTest>(image2, &iEncrypt,&IEncrypt::EncryptImage,image2));
                        }
                        
                }
                
                void RunSelectedTests() {
                        us.runAllTests(runner);
                }


};

#endif 