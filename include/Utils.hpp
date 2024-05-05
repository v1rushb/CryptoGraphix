#ifndef UTILS_HPP
#define UTILS_HPP

#include <opencv2/opencv.hpp>
#include <vector>
#include <random>
#include <chrono>
#include <functional>
#include <random>
#include <thread>
#include "../src/ErrorHandler.cpp"
#include <cryptopp/base64.h>
#include <cryptopp/secblock.h>

using namespace std;

#define ll long long int

class Utils {
    public:

        static vector<int> Vectorize(const cv::Mat &img) {
            vector<int> buffer;
            cout << "DEBUGGING: " << img.channels() << endl;
            buffer.reserve(img.total() * img.channels());
            if (img.channels() == 1) {
                for (int o = 0; o < img.rows; o++) {
                    for (int i = 0; i < img.cols; i++) {
                        uchar pixel = img.at<uchar>(o,i);
                        buffer.push_back(pixel);
                    }
                }
            } else if (img.channels() == 3) {
                for (int o = 0; o < img.rows; o++) {
                    for (int i = 0; i < img.cols; i++) {
                        cv::Vec3b pixel = img.at<cv::Vec3b>(o, i);
                        for (int k = 0; k < 3; k++) {
                            buffer.push_back(pixel[k]);
                        }
                    }
                }
            } else {
                throw std::runtime_error("Unsupported number of channels.");
            }
            return buffer;
        }

        static vector<CryptoPP::byte> IntVectorToByte(const vector<int> &data) {
            vector<CryptoPP::byte> result;
            result.reserve(data.size());
            for(int el : data) {
                result.push_back(static_cast<CryptoPP::byte>(el));
            }
            return result;
        }

        static string IntVectorToString(const vector<int> &data) {
            string result;
            for(int el : data) {
                if (el < 0 || el > 255) {
                    throw runtime_error("Something went wrong.");
                }
                result+= static_cast<char>(el);
            }
            return result;
        }

        static cv::Mat Matricize(long int rows, long int cols, int channels,const vector<CryptoPP::byte> &data) {
            return cv::Mat(rows,cols,(channels == 1? CV_8UC1 : (channels == 3? CV_8UC3 : throw CustomException("Unsupported Number of channels."))),(void*)data.data()).clone();
        }

        static cv::Mat GenerateRandomImage(long int rows, long int cols, int channels = 1) {
            cv::Mat image(rows, cols, CV_8UC(channels));
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distr(0, 255);

            if (channels == 1) {
                for (long int o = 0; o < rows; o++) {
                    for (long int i = 0; i < cols; i++) {
                        image.at<uchar>(o, i) = static_cast<uchar>(distr(gen));
                    }
                }
            } else if (channels == 3) {
                for (long int o = 0; o < rows; o++) {
                    for (long int i = 0; i < cols; i++) {
                        cv::Vec3b& pixel = image.at<cv::Vec3b>(o, i);
                        for (int x = 0; x < 3; x++) {
                            pixel[x] = static_cast<uchar>(distr(gen));
                        }
                    }
                }
            } else {
                throw std::runtime_error("Unsupported number of channels.");
            }
            return image;
        }

        static vector<ll> getFreq(const cv::Mat &img) {
            vector<ll> freq(256,0);
            const bool channels = (img.channels() != 1);
            for(int o = 0; o < img.rows;o++) {
                for(int i = 0; i < img.cols;i++) {
                    if(channels) {
                        cv::Vec3b pixel = img.at<cv::Vec3b>(o,i);
                        for(int x = 0; x < img.channels();x++) {
                            freq[pixel[x]]++;
                        }
                    } else {
                        uchar val = img.at<uchar>(o,i);
                        freq[val]++;
                    }
                }
            }
            return freq;
        }

        static vector<ll> getImgFreq(const cv::Mat &img) {
            vector<ll> freq(256,0);
            const short channels = img.channels();
            for(int o = 0; o < img.rows;o++) {
                for(int i = 0; i < img.cols;i++) {
                    if(channels == 1) {
                        freq[img.at<uchar>(o,i)]++;
                    } else {
                        const cv::Vec3b pixel = img.at<cv::Vec3b>(o,i);
                        for(int x = 0; x < channels;x++)
                            freq[pixel[x]]++;
                    }
                }
            }
            return freq;
        }

        static vector<CryptoPP::byte> StringToByteVector(const string &str) {
            return vector<CryptoPP::byte>(str.begin(),str.end());
        }

        static string ByteVectorToString(const vector<CryptoPP::byte> &data) {
            return string(data.begin(),data.end());
        }

        template<typename Function, typename... Args>
        static double getExecutionTime(Function function, Args&&... args) {
            auto start = chrono::high_resolution_clock::now();
            invoke(function, forward<Args>(args)...);
            auto finish = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsedTime = finish -  start;
            return elapsedTime.count();
        }

        static void StringIntoSecByteBlock(CryptoPP::SecByteBlock &secretKey, string &secretKeyString) {
            string tempKey = secretKeyString;
            secretKey.CleanNew(tempKey.size());
            memcpy(secretKey.data(), tempKey.data(), tempKey.size());
        }

        static int GenerateARandomInteger() {
            mt19937 gen(static_cast<unsigned int>(time(nullptr))); 
            uniform_int_distribution<> distr(1, 550);
            return distr(gen);
        }

        static CryptoPP::SecByteBlock ModifyKey(CryptoPP::SecByteBlock key) {
            CryptoPP::SecByteBlock newKey = key;
            if(!key.size())
                return newKey;
            newKey[Utils::GenerateARandomInteger()%key.size()]^=1;
            return newKey;
        }

        static void ModifyImage(cv::Mat &img) {
                const ll cols = Utils::GenerateARandomInteger()%img.cols;
                const ll rows = Utils::GenerateARandomInteger()%img.rows;
                const short idx = Utils::GenerateARandomInteger()%3;
                unsigned char &val = (img.channels() != 3? img.at<uchar>(rows,cols) : img.at<cv::Vec3b>(rows,cols)[idx]);
                val ^=1;
        }

        static void DelaySeconds(ll sec) {
            this_thread::sleep_for(chrono::seconds(sec));
        }
        static void Clear() {
            system("clear");
        }
        // static string SecByteBlockIntoString(CryptoPP::SecByteBlock blk) {
        //     string ansHex;
        //     CryptoPP::HexEncoder encoder;
        //     encoder.Attach(new CryptoPP::StringSink(ansHex));
        //     encoder.Put(blk, blk.size());
        //     encoder.MessageEnd();
        //     return ansHex;
        // }
        
        // static std::string SecByteBlockToBase64String(const CryptoPP::SecByteBlock& block) {
        //     std::string base64;
        //     CryptoPP::Base64Encoder encoder(new CryptoPP::StringSink(base64), /* newline= */ false);
        //     encoder.Put(block, block.size());
        //     encoder.MessageEnd();
        //     return base64;
        // }

        // static vector<pair<char,bool>> SecByteBlockIntoCharVector(const CryptoPP::SecByteBlock & block) {
        //     vector<pair<char,bool>> og;
        //     for(auto el : block) {
        //         if(el - 129 < 0) {
        //             og.push_back({(char)el,false});
        //         } else {
        //             og.push_back({(char) (el-129),true});
        //         }
        //     }
        //     return og;
        // }
        // static string SecByteBlockIntoString(const CryptoPP::SecByteBlock &key) {
        //     vector<pair<char,bool>> og = SecByteBlockIntoCharVector(key);
        //     string ans ="";
        //     for(auto el : og) {
        //         ans+=el.first;
        //     }
        //     return ans;
        // }
};


#endif