#include "IEncrypt.hpp"
#include "Utils.hpp"
#include <vector>
#include <iostream>

using namespace std;
using namespace CryptoPP;


// vector<uchar> IEncrypt::Vectorize(const cv::Mat &image) {
//     // vector<uchar> buffer;
//     // if (img.channels() == 1) {
//     //     buffer.assign(img.begin<uchar>(), img.end<uchar>());
//     // } else {
//     //     if (img.isContinuous()) {
//     //         buffer.assign(img.data, img.data + img.total() * img.elemSize());
//     //     } else {
//     //         for (int o = 0; o < img.rows; o++) {
//     //             auto rowBegin = img.ptr<uchar>(o);
//     //             auto rowEnd = rowBegin + img.cols * img.elemSize();
//     //             buffer.insert(buffer.end(), rowBegin, rowEnd);
//     //         }
//     //     }
//     // }
//     cv::Mat flat = image.reshape(1, image.total()*image.channels());
//     std::vector<uchar> buffer = image.isContinuous()? flat : flat.clone();

//     return buffer;
// }

vector<int> IEncrypt::Vectorize(const cv::Mat &newImg) {
    cv::Mat img = newImg.clone();
    vector<int> buffer;
    buffer.reserve(img.rows * img.cols * img.channels());
    for(int o = 0; o < img.rows;o++) {
        for(int i = 0; i < img.cols;i++) {
            const cv::Vec3b &pixel = img.at<cv::Vec3b>(o,i);
            for(int x = 0; x < img.channels();x++) {
                buffer.push_back(pixel[x]);
            }
        }
    }
    return buffer;
}

// cv::Mat IEncrypt::Matricize(vector<uchar> & data,Metadata size) {
//     cout << size.height << ' ' << size.width << endl;
//     cv::Mat img = cv::Mat(size.height, size.width, size.channels == 3 ? CV_8UC3 : CV_8UC1, data.data()).clone();
//     return img;
// }

cv::Mat IEncrypt::makeMatrix(long int rows, long int cols) {
    cv::Scalar defaultColor = (0,0,0);
    cv::Mat coloredMat(rows,cols,CV_8UC3,defaultColor);
    return coloredMat;
}

cv::Mat IEncrypt::setMatrix(const vector<CryptoPP::byte> &data, long int rows, long int cols) {
    cout << cols << ' ' << rows << endl;
    cv::Mat img(rows, cols, CV_8UC3);
    vector<int> conv;
    conv.reserve(rows * cols * 3);
    for(auto el : data)
        conv.push_back(static_cast<int>(el));
    int ctr(0);
    long int expectedSize = img.total() * img.elemSize();
    for (int o = 0; o < img.rows; o++) {
        for (int i = 0; i < img.cols; i++) {
            if (ctr + 2 < expectedSize) {
                cv::Vec3b &pixel = img.at<cv::Vec3b>(o, i);
                pixel[0] = conv[ctr++];
                pixel[1] = conv[ctr++];
                pixel[2] = conv[ctr++];
            }
        }
    }
    return img;
}


cv::Mat IEncrypt::Encrypt(const cv::Mat &img) {
    // vector<int> vectorizedImage = Vectorize(img);
    vector<int> vectorizedImage = Utils::Vectorize(img);
    // vector<CryptoPP::byte> output;
    // output.reserve(vectorizedImage.size());

    // for(int value : vectorizedImage) {
    //     output.push_back(static_cast<CryptoPP::byte>(value));
    // }
    vector<CryptoPP::byte> output = Utils::IntVectorToByte(vectorizedImage);
    vector<CryptoPP::byte> encryptedData = strategy->Encrypt(output);

    Metadata metadata = {
        img.rows,
        img.cols,
        img.channels(),
        encryptedData,
    };

    // cout << encryptedData.size() << endl;
    // cv::Mat image(img.rows, img.cols, CV_8UC1, (void*)output.data());
    cv::Mat image = Utils::Matricize(img.rows,img.cols,img.channels(),output);
    // cout << "CHANNELS: "<<img.channels() << endl;

    // vector<int> newVectorizedImage = Vectorize(image);
    vector<int> newVectorizedImage = Utils::Vectorize(image);
    // cout << "Size: " << encryptedData.size() << endl;

    // vector<CryptoPP::byte> output2;
    // output2.reserve(newVectorizedImage.size());

    // for(int value : newVectorizedImage) {
    //     output2.push_back(static_cast<CryptoPP::byte>(value));
    // }
    vector<CryptoPP::byte> output2 = Utils::IntVectorToByte(newVectorizedImage);

    // string res;
    // for(int el : newVectorizedImage) {
    //     if (el < 0 || el > 255) {
    //         throw std::runtime_error("Value out of ASCII range.");
    //     }
    //     res+= static_cast<char>(el);
    // }
    string res = Utils::IntVectorToString(newVectorizedImage);
    for(int o = 0; o < 10;o++)
        cout << newVectorizedImage[o] << ' ';
    cout << endl;

    metadataManager.storeMetadata(metadata,res);
    cout << "Encryption" << endl;
    // cout << newVectorizedImage.size() << endl;
    // for(int o = 0; o < 20;o++)
    //     cout << res[o] << ' ';
    // cout << endl;
    // for(int o = 0; o < 10;o++)
    //     cout << (int) encryptedData[o] << ' ';
    // cout << endl;
    // // // cout << encryptedData.size() << endl;
    // return encryptedImage;
    return image.clone();
}

cv::Mat IEncrypt::Decrypt(const cv::Mat &encryptedImg) {
    // using namespace Utils; // do later - refactoring
    // vector<int> encryptedData = Vectorize(encryptedImg);
    vector<int> encryptedData = Utils::Vectorize(encryptedImg);
    cout << "Size: " << encryptedData.size() << endl;
    for(int o =0; o < 10;o++)
        cout << encryptedData[o] << ' ';
    cout << endl;
    // vector<CryptoPP::byte> output;
    // output.reserve(encryptedData.size());

    // for(int value : encryptedData) {
    //     output.push_back(static_cast<CryptoPP::byte>(value));
    // }
    vector<CryptoPP::byte> output = Utils::IntVectorToByte(encryptedData);

    // string res;
    // for(int el : encryptedData) {
    //     if (el < 0 || el > 255) {
    //         throw std::runtime_error("Value out of ASCII range.");
    //     }
    //     res+= static_cast<char>(el);
    // }
    string res = Utils::IntVectorToString(encryptedData);

    // cout << "Decryption" << endl;
    // cout << encryptedData.size() << endl;
    // for(int o = 0; o < 15;o++)
    //     cout << res[o] << ' ';
    // cout << endl;
    Metadata metadata = metadataManager.getMetadata(res);
    // cout << metadata.height << endl;
    vector<CryptoPP::byte> decryptedData = strategy->Decrypt(output,metadata);
    // return setMatrix(decryptedData,metadata.width,metadata.height);
    // cv::Mat image(metadata.width, metadata.height, CV_8UC3, (void*)output.data());
    cv::Mat image = Utils::Matricize(metadata.width,metadata.height,metadata.channels,output);
    // return cv::Mat();
    return image;
}
