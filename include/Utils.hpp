#ifndef UTILS_HPP
#define UTILS_HPP

#include <opencv2/opencv.hpp>
#include <vector>
#include <random>

using namespace std;

#define ll long long int

class Utils {
    public:

        static vector<int> Vectorize(const cv::Mat &img) {
            vector<int> buffer;
            buffer.reserve(img.total() * img.channels());
            if (img.channels() == 1) {
                for (int i = 0; i < img.rows; i++) {
                    for (int j = 0; j < img.cols; j++) {
                        uchar val = img.at<uchar>(i, j);
                        buffer.push_back(val);
                    }
                }
            } else if (img.channels() == 3) {
                for (int i = 0; i < img.rows; i++) {
                    for (int j = 0; j < img.cols; j++) {
                        cv::Vec3b pixel = img.at<cv::Vec3b>(i, j);
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
            return cv::Mat(rows,cols,(channels == 1? CV_8UC1 : (channels == 3? CV_8UC3 : throw runtime_error("Unsupported Number of channels."))),(void*)data.data()).clone();
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
};


#endif