#ifndef UTILS_HPP
#define UTILS_HPP

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <functional>
#include <random>
#include <thread>
#include <cmath>
#include "../src/ErrorHandler.cpp"
#include <cryptopp/base64.h>
#include <cryptopp/secblock.h>
#include <unordered_map>
#include <cryptopp/sha.h>
#include "../src/ErrorHandler.cpp"
#include "../src/FileLister.cpp"
#include "GraphicsUtils.hpp"

using namespace std;

#define ll long long int

class Utils {
    private:

    public:
        static vector<int> Vectorize(const cv::Mat &img) {
            vector<int> buffer;
            // cout << "DEBUGGING: " << img.channels() << endl;
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
                throw runtime_error("Unsupported number of channels.");
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

        static vector<int> ByteVectorIntoInt(const vector<CryptoPP::byte> &data) {
            return vector<int>(data.begin(),data.end());
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
                throw runtime_error("Unsupported number of channels.");
            }
            return image;
        }

        static cv::Mat GenerateGradientImage(long int rows, long int cols, int channels = 1) {
            cv::Mat image(rows, cols, CV_8UC(channels));
            for (long int o = 0; o < rows; o++) {
                for (long int i = 0; i < cols; i++) {
                    if (channels == 1) {
                        image.at<uchar>(o, i) = static_cast<uchar>((o + i) % 256);
                    } else if (channels == 3) {
                        cv::Vec3b& pixel = image.at<cv::Vec3b>(o, i);
                        pixel[0] = static_cast<uchar>((o + i) % 256);
                        pixel[1] = static_cast<uchar>((o + 2 * i) % 256);
                        pixel[2] = static_cast<uchar>((2 * o + i) % 256);
                    }
                }
            }
            return image;
        }

        static cv::Mat GenerateShapeImage(long int rows, long int cols, int channels = 1) {
            cv::Mat image(rows, cols, CV_8UC(channels), cv::Scalar(255, 255, 255));
            cv::Scalar color = (channels == 1) ? cv::Scalar(0) : cv::Scalar(0, 0, 255);
            
            cv::circle(image, cv::Point(cols / 2, rows / 2), 50, color, -1);
            cv::rectangle(image, cv::Point(cols / 4, rows / 4), cv::Point(3 * cols / 4, 3 * rows / 4), color, 5);
            
            return image;
        }

        static cv::Mat GenerateNoisePatternImage(long int rows, long int cols, int channels = 1) {
            cv::Mat image(rows, cols, CV_8UC(channels));
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distr(0, 255);

            for (long int o = 0; o < rows; o++) {
                for (long int i = 0; i < cols; i++) {
                    if (channels == 1) {
                        image.at<uchar>(o, i) = static_cast<uchar>(distr(gen));
                    } else if (channels == 3) {
                        cv::Vec3b& pixel = image.at<cv::Vec3b>(o, i);
                        pixel[0] = static_cast<uchar>(distr(gen));
                        pixel[1] = static_cast<uchar>(distr(gen));
                        pixel[2] = static_cast<uchar>(distr(gen));
                    }
                }
            }

            cv::Scalar color = (channels == 1) ? cv::Scalar(0) : cv::Scalar(255, 255, 255);
            cv::line(image, cv::Point(0, 0), cv::Point(cols - 1, rows - 1), color, 2);
            
            return image;
        }

        static cv::Mat GeneratePerlinNoiseImage(long int rows, long int cols, int channels = 1) {
            cv::Mat image(rows, cols, CV_8UC(channels));
            for (long int o = 0; o < rows; o++) {
                for (long int i = 0; i < cols; i++) {
                    float value = GraphicsUtils::PerlinNoise(o * 0.1, i * 0.1) * 255;
                    if (channels == 1) {
                        image.at<uchar>(o, i) = static_cast<uchar>(value);
                    } else if (channels == 3) {
                        cv::Vec3b& pixel = image.at<cv::Vec3b>(o, i);
                        pixel[0] = static_cast<uchar>(value);
                        pixel[1] = static_cast<uchar>(value);
                        pixel[2] = static_cast<uchar>(value);
                    }
                }
            }
            return image;
        }


        static cv::Mat GenerateMandelbrotImage(long int rows, long int cols, int channels = 3) {
            cv::Mat image(rows, cols, CV_8UC3);
            for (long int y = 0; y < rows; y++) {
                for (long int x = 0; x < cols; x++) {
                    double real = (x - cols / 2.0) * 4.0 / cols;
                    double imag = (y - rows / 2.0) * 4.0 / rows;
                    complex<double> c(real, imag);
                    complex<double> z = c;
                    int iterations = 0;
                    const int max_iterations = 1000;
                    while (abs(z) < 2.0 && iterations < max_iterations) {
                        z = z * z + c;
                        iterations++;
                    }
                    uchar color = static_cast<uchar>(255 * iterations / max_iterations);
                    if (channels == 1) {
                        image.at<uchar>(y, x) = color;
                    } else if (channels == 3) {
                        cv::Vec3b& pixel = image.at<cv::Vec3b>(y, x);
                        pixel[0] = color;
                        pixel[1] = color;
                        pixel[2] = color;
                    }
                }
            }
            return image;
        }

        static cv::Mat GenerateMarbleTextureImage(long int rows, long int cols, int channels = 3) {
            cv::Mat image(rows, cols, CV_8UC3);
            for (long int y = 0; y < rows; y++) {
                for (long int x = 0; x < cols; x++) {
                    float xyValue = x * 0.05 + y * 0.05 + 10 * GraphicsUtils::PerlinNoise(x * 0.1, y * 0.1);
                    float sineValue = 128.0f * abs(sin(xyValue));
                    uchar color = static_cast<uchar>(sineValue);
                    if (channels == 1) {
                        image.at<uchar>(y, x) = color;
                    } else if (channels == 3) {
                        cv::Vec3b& pixel = image.at<cv::Vec3b>(y, x);
                        pixel[0] = color;
                        pixel[1] = color;
                        pixel[2] = color;
                    }
                }
            }
            return image;
        }

        static cv::Mat GenerateCombinedPatternImage(long int rows, long int cols, int channels = 3) {
            cv::Mat image(rows, cols, CV_8UC(channels));
            cv::Mat mandelbrotImage = GenerateMandelbrotImage(rows, cols, 1);

            for (long int y = 0; y < rows; y++) {
                for (long int x = 0; x < cols; x++) {
                    float perlinValue = GraphicsUtils::PerlinNoise(x * 0.1, y * 0.1) * 255;
                    float mandelbrotValue = (mandelbrotImage.at<uchar>(y, x) / 255.0) * 255;
                    uchar color = static_cast<uchar>((perlinValue + mandelbrotValue) / 2);
                    if (channels == 1) {
                        image.at<uchar>(y, x) = color;
                    } else if (channels == 3) {
                        cv::Vec3b& pixel = image.at<cv::Vec3b>(y, x);
                        pixel[0] = color;
                        pixel[1] = color;
                        pixel[2] = color;
                    }
                }
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

        static CryptoPP::SecByteBlock StringToSecByteBlock(const string& str) {
            CryptoPP::SHA256 hash;
            CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];

            hash.CalculateDigest(digest, reinterpret_cast<const CryptoPP::byte*>(str.data()), str.size());

            return CryptoPP::SecByteBlock(digest, CryptoPP::SHA256::DIGESTSIZE);
        }

        static int GenerateARandomInteger(const int limit = 550) {
            mt19937 gen(static_cast<unsigned int>(time(nullptr))); 
            uniform_int_distribution<> distr(1, limit);
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
        
        static void print(const string &prompt, const string chosenColor = "White",const bool &special = false) {
            unordered_map<string,string> color = {
                {"Black", "\033[30m"},
                {"Red", "\033[31m"},
                {"Green", "\033[32m"},
                {"Yellow", "\033[33m"},
                {"Blue", "\033[34m"},
                {"Magenta", "\033[35m"},
                {"Cyan", "\033[36m"},
                {"White", "\033[37m"}
            };
            if(special) {
                vector<string> colorKeys;
                for(auto &el : color) {
                    colorKeys.push_back(el.first); 
                }
                for(auto &el : prompt) {
                    cout << color[colorKeys[Utils::GenerateARandomInteger()%8]] << el;
                }
                return void(cout<<"\033[0m" <<endl);
            } 
            cout << color[chosenColor] << prompt;
            cout << "\033[0m" << endl; 
        }

        static string SplitAndReturnLastPart(const string &str) {
            size_t pos = str.find_last_of("/");
            return str.substr(pos+1);
        }

        static pair<string, string> SplitStringIntoPair(const string &str, char opt) {
            size_t pos = str.find(opt);
            if (pos != string::npos) {
                return {str.substr(0, pos), str.substr(pos + 1)};
            }
            return {str, ""};
        }

        static ll getValidChoice(int upperBound) {
            ll choice;
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw CustomException("Invalid input. Please enter an integer.");
            }

            if (choice > upperBound || choice <= 0) {
                throw CustomException("Please use a valid number within the allowed range.");
            }

            return choice;
        }

        static vector<string> getDirectoryFiles(const string &_PATH) {
            vector<string> files = FileLister::listFilesInDirectory(_PATH);
            for(auto &el : files) {
                el = Utils::removeEncryptionTags(el);
            }
            return files;
        }

        static string removeEncryptionTags(string str) {
            const string decryptedTag = " (DECRYPTED)";
            const string encryptedTag = " (ENCRYPTED)";

            size_t pos = str.find(decryptedTag);
            while (pos != string::npos) {
                str.erase(pos, decryptedTag.length());
                pos = str.find(decryptedTag, pos);
            }

            pos = str.find(encryptedTag);
            while (pos != string::npos) {
                str.erase(pos, encryptedTag.length());
                pos = str.find(encryptedTag, pos);
            }
            return str;
        }
        static string splitNameAndNumber(const string& input) {
            string num,name;
            ll idx = input.length() - 1;
            while (idx >= 0 && isdigit(input[idx])) {
                idx--;
            }

            name = input.substr(0, idx + 1);
            if (idx + 1 < input.length()) {
                num = input.substr(idx + 1);
            }
            return name;
        }
};

#endif