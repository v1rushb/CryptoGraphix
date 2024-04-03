#ifndef LSB_HPP
#define LSB_HPP

#include "HidingStrategy.hpp"
#include <opencv2/opencv.hpp>
#include <vector>
#include <bitset>
#include <string>

using namespace std;

class LSB : public HidingStrategy {
public:
    void hideMessage(cv::Mat& img, const string& message) override {
        if (message.size() > img.cols * img.rows) {
            cerr << "Message too large for LSB." << endl;
            return;
        }

        string data;
        for (char ch : message) {
            bitset<8> bits(static_cast<unsigned long long>(ch));
            data += bits.to_string();
        }

        int bitIndex = 0;
        for (int o = 0; o < img.rows && bitIndex < data.size(); o++) {
            for (int i = 0; i < img.cols && bitIndex < data.size(); i++) {
                if (img.channels() == 3) {
                    cv::Vec3b& pixel = img.at<cv::Vec3b>(o, i);
                    uchar& blue = pixel[0];
                    blue = (blue & ~1) | (data[bitIndex] - '0');
                } else {
                    uchar& wb = img.at<uchar>(o, i);
                    wb = (wb & ~1) | (data[bitIndex] - '0');
                }
                ++bitIndex;
            }
        }
    }

    string extractMessage(const cv::Mat& img, int len) override {
        len *= 8;
        string data, msg;
        int bitIndex = 0;

        for (int o = 0; o < img.rows && bitIndex < len; o++) {
            for (int i = 0; i < img.cols && bitIndex < len; i++) {
                uchar bit = (img.channels() == 3) ? img.at<cv::Vec3b>(o, i)[0] & 1 : img.at<uchar>(o, i) & 1;
                data += to_string(bit);
                ++bitIndex;
            }
        }

        for (int o = 0; o < data.size(); o += 8) {
            bitset<8> bits(data.substr(o, 8));
            msg += static_cast<char>(bits.to_ulong());
        }
        return msg;
    }
};

#endif