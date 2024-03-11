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

using namespace std;
using namespace CryptoPP;

#define send {ios_base::sync_with_stdio(false);}
#define help {cin.tie(NULL);}
#define pls  {cout.tie(0);}
#define ll long long int
#define all(v) v.begin(),v.end()
#define endl '\n'
#define debug(x)	cout<<'['<<#x<<" is "<<x<<"]"<<endl;
#define ull unsigned long long
#define frq(mp) {for(auto el : mp) cout << el.first << ' ' << el.second << endl;}
#define fe(d)	for(auto &oI : d) {cout << oI << " ";} cout << endl;

const string outputDirectory = "./resources/";
const string src = "./assets/";
const string beforeDir = outputDirectory + "before/";
const string afterDir = outputDirectory + "after/";

cv::Mat readImage(const string &imagePath) {
    cv::Mat image = cv::imread(imagePath,cv::IMREAD_COLOR);
    if(image.empty()) {
        cerr << "Cannot open the image with path: " << imagePath << endl;
    }
    return image;
}

void writeImage(const string &outputPath, const cv::Mat &image) {
    if (!filesystem::exists(outputDirectory)) {
        filesystem::create_directory(outputDirectory);
    }
    if(!filesystem::exists(beforeDir)) {
        filesystem::create_directory(beforeDir);
    }
    if(!filesystem::exists(afterDir)) {
        filesystem::create_directory(afterDir);
    }

    if(!cv::imwrite(outputPath,image)) {
        cerr << "Cannot write to file: " << outputPath << endl;
    }
    cout << "Written successfully, Path:" << outputPath << endl;
}

void modifyImage(cv::Mat &image) {
    unsigned char &val = (image.channels() != 3? image.at<uchar>(0,0) : image.at<cv::Vec3b>(0,0)[0]);
    val ^=1;
}


vector<unsigned char> encryptImage(const vector<unsigned char> &data, const SecByteBlock &key, const CryptoPP::byte iv[AES::BLOCKSIZE]) {
    string encrypted;
    try {
        CBC_Mode<AES>::Encryption encryptor;
        encryptor.SetKeyWithIV(key, key.size(), iv);
        ArraySource(reinterpret_cast<const CryptoPP::byte*>(data.data()), data.size(), true,
            new StreamTransformationFilter(encryptor,
                new StringSink(encrypted)
            )
        );
    } catch (const Exception &e) {
        cerr << e.what() << endl;
        exit(1);
    }
    return vector<unsigned char>(all(encrypted));
}

vector<unsigned char> vectorize(const cv::Mat &image) {
    vector<unsigned char> buffer;
    const string ext = ".png";
    if(!cv::imencode(ext,image,buffer)) {
        throw runtime_error("Failed to encode.");
    }
    return buffer;
}

cv::Mat matricize(const vector<unsigned char> &data, int height, int width) {
    // if (data.size() < static_cast<size_t>(width * height)) {
    //     throw runtime_error("Not enough data for the specified dimensions.");
    // }

    cv::Mat image = cv::Mat(height, width, CV_8UC3, const_cast<unsigned char*>(data.data()));

    if (image.empty()) {
        throw runtime_error("Failed to create MATRIX");
    }
    return image;
}

vector<char> decryptImage(const vector<unsigned char> &data, const SecByteBlock &key, const CryptoPP::byte iv[AES::BLOCKSIZE]) {
    string decrypted;
    try {
        CBC_Mode<AES>::Decryption decryptor;
        decryptor.SetKeyWithIV(key, key.size(), iv);
        ArraySource(reinterpret_cast<const CryptoPP::byte*>(data.data()), data.size(), true,
            new StreamTransformationFilter(decryptor,
                new StringSink(decrypted)
            )
        );
    } catch (const Exception &e) {
        cerr << e.what() << endl;
        exit(1);
    }
    return vector<char>(all(decrypted));
}


double NPCR(vector<unsigned char> &img1, vector<unsigned char> &img2) {
    if(img1.size() - img2.size())
    {
        throw runtime_error("SizeDifferenceException"); //do the exption.
    }
    
    ll diff(0);
    for(ll o = 0; o < img1.size();o++)
        diff+=img1[o]!=img2[o];
    return (diff / (double) img1.size()) * 100.0;
}

double UACI(const vector<unsigned char> &img1, const vector<unsigned char> &img2) {
    if(img1.size()-img2.size())
    {
        cerr << "SizeDifferenceException" << endl;
        exit(1);
    }
    double s(0);
    for(ll o = 0; o < img1.size();o++) {
        s+=abs(static_cast<unsigned char>(img1[o]) - static_cast<unsigned char>(img2[o]))/255.0;
    }
    return (s/img1.size())*100.0;
}

double hammingDistance(const vector<unsigned char> &img1, const vector<unsigned char> &img2) {
    if(img1.size()-img2.size()) 
    {
        cerr << "SizeDiffernceException" << endl;
        exit(1);
    }

    ll dist(0);
    for(int o = 0; o < img1.size();o++)
    {
        ll x = (static_cast<unsigned char>(img1[o])) ^ (static_cast<unsigned char>(img2[o]));
        for(int bit = 0; bit < 8;bit++) {
            dist += (x >> bit) &1;
        }
    }
    return (dist/ (double) (img1.size()*8)) * 100;
}

vector<ll> getFreq(const cv::Mat &img) {
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

// map<ll,ll> getFreq(const vector<char> &img) {
//     map<ll,ll> mp;
//     for(int o = 0; o < img.size();o++)
//         mp[static_cast<unsigned int>(static_cast<unsigned char>(img[o]))]++;
//     return mp;
// }

// vector<ll> freq(vector<char> &original, vector<char> &encrypted) {
//     vector<ll> ogFreq = getFreq(original),encFreq = getFreq(encrypted);
// }

bool chiSquare(const vector<ll> &freq) {
    const ll sum = accumulate(all(freq), 0);
    const double expectedFreq = (double) sum/256.0;
    double s(0);
    for(ll el : freq) {
        double x = el - expectedFreq;
        s+=((x*x)/expectedFreq);
    }
    const double criticalVal = 293.2478; 
    cout << s;
    return s < criticalVal;
}

// void hideMessage(cv::Mat &img, const string message) {
//     string str;
//     for(char ch : message) {
//         bitset<8> bits(static_cast<ull>(ch));
//         str+= bits.to_string();
//     }
// }

void hideMessage(cv::Mat &img, const string &message) {
    if(message.size() > img.cols * img.rows) {
        cerr << "Too large for LSB." << endl;
        return;
    }
    string data;
    for(char ch : message) {
        bitset<8> bits(static_cast<ull>(ch));
        data+=bits.to_string();
    }

    
    int bitIndex(0);
    for(int o = 0; o < img.rows && bitIndex < data.size(); o++) {
        for(int i = 0; i  < img.cols && bitIndex < data.size();i++) {

            if(img.channels() == 3) {
                cv::Vec3b &pixel = img.at<cv::Vec3b>(o,i);
                uchar &blue = pixel[0];
                if(data[bitIndex] =='1') {
                    blue |=1;
                } else {
                    blue &= ~1;
                }
            } else {
                uchar &wb = img.at<uchar>(o,i);
                if(data[bitIndex] =='1') {
                    wb |=1;
                } else {
                    wb &= ~1;
                }
            }
            ++bitIndex;
        }
    }
}

string extractMessage(const cv::Mat &img, int len) {
    string data;
    int bitIndex(0);
    for(int o = 0; o < img.rows && bitIndex < len; o++) {
        for(int i = 0; i  < img.cols && bitIndex < len;i++) {
            if(img.channels() == 3) {
            uchar blue = img.at<cv::Vec3b>(o,i)[0];
            data += to_string(blue&1);
            } else {
                uchar wb = img.at<uchar>(o,i);
                data+=to_string(wb&1);
            }
            ++bitIndex;             
        }
    }

    string msg;
    for(int o = 0; o < data.size();o+=8) {
        bitset<8> bits(data.substr(o,8));
        msg += static_cast<char>(bits.to_ulong());
    }
    return msg;
}

long double calculateHorizontalCorrelation(const cv::Mat &img, short channel) {
    long double sumX = 0,sumY = 0, sumXY =0, sumX2 = 0, sumY2 = 0.0;
    ll n(0);
    for(int o = 0; o < img.rows;o++) {
        for(int i = 0; i < img.cols;i++) {
            uchar xPixel = img.at<cv::Vec3b>(o,i)[channel];
            uchar yPixel = img.at<cv::Vec3b>(o,i+1)[channel];
            sumX +=xPixel;
            sumY +=yPixel;
            sumXY += xPixel * yPixel;
            sumX2 += pow(xPixel,2);
            sumY2 += pow(yPixel,2);
            ++n;
        }
    }
    long double xMean = sumX / n, yMean = sumY / n, numerator = n * sumXY - sumX * sumY;
    double denominator = sqrt((n * sumX2 - sumX * sumX) * (n*sumY2 - sumY * sumY));
    return numerator/denominator; 
}

long double calculateVerticalCorrelation(const cv::Mat &img, short channel) {
    long double sumX = 0,sumY = 0, sumXY =0, sumX2 = 0, sumY2 = 0.0;
    ll n(0);
    for(int o = 0; o < img.rows;o++) {
        for(int i = 0; i < img.cols;i++) {
            uchar xPixel = img.at<cv::Vec3b>(o,i)[channel];
            uchar yPixel = img.at<cv::Vec3b>(o+1,i)[channel];
            sumX +=xPixel;
            sumY +=yPixel;
            sumXY += xPixel * yPixel;
            sumX2 += pow(xPixel,2);
            sumY2 += pow(yPixel,2);
            ++n;
        }
    }
    long double xMean = sumX / n, yMean = sumY / n, numerator = n * sumXY - sumX * sumY;
    double denominator = sqrt((n * sumX2 - sumX * sumX) * (n*sumY2 - sumY * sumY));
    return numerator/denominator; 
}

long double calculateDiagonalCorrelation(const cv::Mat &img, short channel) {
    long double sumX = 0,sumY = 0, sumXY =0, sumX2 = 0, sumY2 = 0.0;
    ll n(0);
    for(int o = 0; o < img.rows;o++) {
        for(int i = 0; i < img.cols;i++) {
            uchar xPixel = img.at<cv::Vec3b>(o,i)[channel];
            uchar yPixel = img.at<cv::Vec3b>(o+1,i+1)[channel];
            sumX +=xPixel;
            sumY +=yPixel;
            sumXY += xPixel * yPixel;
            sumX2 += pow(xPixel,2);
            sumY2 += pow(yPixel,2);
            ++n;
        }
    }
    long double xMean = sumX / n, yMean = sumY / n, numerator = n * sumXY - sumX * sumY;
    double denominator = sqrt((n * sumX2 - sumX * sumX) * (n*sumY2 - sumY * sumY));
    return numerator/denominator; 
}


double getCorrelation(const cv::Mat &img) {
    vector<double> correlations;
    const short channels = img.channels();
    for(int o = 0; o < channels;o++) {
        correlations.push_back(calculateHorizontalCorrelation(img,o));
        correlations.push_back(calculateVerticalCorrelation(img,o));   
        correlations.push_back(calculateDiagonalCorrelation(img,o));
    }
    double sum = accumulate(all(correlations),0.0);
    return sum/ correlations.size();
}

vector<ll> getImgFreq(const cv::Mat &img) {
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

long double calculateInformationEntropy(const cv::Mat &img) {
    vector<ll> freq = getImgFreq(img);
    const short channels = img.channels();
    long double val = 0.0;
    const ll picSize = img.cols * img.rows* channels;
    for(int o = 0; o < 256;o++) {
        if(freq[o] > 0) {
            long double prob = (freq[o] / (picSize * 1.0));
            val -= prob * log2(prob);
        }
    }
    return val;
}

long double calculateEncryptionQuality(const cv::Mat &img1, const cv::Mat &img2) {
    long double ans(0.0);
    vector<ll> img1Freq = getImgFreq(img1);
    vector<ll> img2Freq = getImgFreq(img2);

    for(int o = 0; o < 256;o++) {
        ans+= abs(img1Freq[o]-img2Freq[o]);
    }
    return ans/256.0;
}

//Helper functions.

void printKey(const SecByteBlock &key) {
    string hexKey;
    HexEncoder encoder;

    encoder.Attach(new StringSink(hexKey));
    encoder.Put(key,key.size());
    encoder.MessageEnd();

    cout << hexKey << endl;
} 

string base64Encode(const vector<unsigned char>& data) {
    string encoded;
    ArraySource(data.data(), data.size(), true,
                new Base64Encoder(
                    new StringSink(encoded),
                    false
                ));
    return encoded;
}

vector<unsigned char> base64Decode(const string& encoded) {
    string decoded;
    StringSource(encoded, true,
                 new Base64Decoder(
                     new StringSink(decoded)
                 ));
    return vector<unsigned char>(all(decoded));
}
SecByteBlock getNewKey(const SecByteBlock key) {
    SecByteBlock newKey = key;
    if(!newKey.size()) {
        AutoSeededRandomPool prng;
        prng.GenerateBlock(newKey,newKey.size());
    }
    newKey[newKey.size()-1] ^= 1;
    return newKey;
}

void padVector(vector<unsigned char> &d, vector<unsigned char> &x) {
    ll diff(d.size() - x.size());
    bool ok = (diff <= 0);
    diff = ok ? diff*-1 : diff;
    if(ok) {
        for(int o = 0; o < diff;o++)
            d.push_back(0);
    } else {
        for(int o = 0; o < diff;o++)
            x.push_back(0);
    }
}

int32_t main() {
    send help pls;
    const string str = "neon.PNG";
    const string imagePath = src + str;
    const string encryptedPath = outputDirectory +"before/" + "encrypted_img.jpeg";
    const string decryptedPath = outputDirectory + "after/" +"decrypted_img.jpeg";
    const string modifiedDecryptedPath = outputDirectory + "after/" +"decrypted_img2.jpeg";
    cv::Mat colorImage = readImage(imagePath);
    if(colorImage.empty()) {
        cout << "Empty image" << endl;
        return -1;
    }
    cv::Mat modifiedColorImage = colorImage.clone();
    //Writing both images before encyrption on path: ./resources/before
    writeImage(encryptedPath,colorImage);
    const string modifiedEncryptedPath = outputDirectory + "before/encrypted_img2.jpeg";
    modifyImage(modifiedColorImage);
    writeImage(modifiedEncryptedPath,modifiedColorImage);

    vector<unsigned char> imageVector = vectorize(colorImage);
    cout << imageVector.size() << endl;
    // cout << colorImage.total() * colorImage.elemSize() << endl;
    vector<unsigned char> modifiedImageVector = vectorize(modifiedColorImage);
    cout << modifiedImageVector.size() << endl;
    // cout << modifiedColorImage.total() * modifiedColorImage.elemSize() << endl;

    // cv::Vec3b pixelValue = colorImage.at<cv::Vec3b>(1,1);
    // for(int o = 0; o < colorImage.rows;o++) {
    //     for(int i = 0; i < colorImage.cols;i++) {
    //         unsigned char &green = colorImage.at<cv::Vec3b>(o,i)[2];
    //         int val = green + 100;
    //         green = (unsigned char) min(max(val,0),255);
    //     }
    // }
    // cout << colorImage.at<cv::Vec3b>(0,0)[0] << endl;
    // cout << modifiedColorImage.at<cv::Vec3b>(0,0)[0] << endl;

    AutoSeededRandomPool prng;
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    prng.GenerateBlock(key, key.size());
    CryptoPP::byte iv[AES::BLOCKSIZE];
    prng.GenerateBlock(iv, sizeof(iv));

    vector<unsigned char> encryptedImage= encryptImage(imageVector,key,iv);
    vector<unsigned char> modifiedEncryptedImage = encryptImage(modifiedImageVector,key,iv);
    string encode = base64Encode(encryptedImage);
    vector<unsigned char> firstImage(all(encode));
    cv::Mat decryptedImage = matricize(firstImage,colorImage.rows,colorImage.cols); // change dims.
    string encode2 = base64Encode(modifiedEncryptedImage);
    vector<unsigned char> secondImage(all(encode2));
    cv::Mat decryptedImage2 = matricize(secondImage,modifiedColorImage.rows,modifiedColorImage.cols); //change dims;

    writeImage(decryptedPath,decryptedImage);
    writeImage(modifiedDecryptedPath,decryptedImage2);

    const string secret = "Bashar Herbawi 211111";
    hideMessage(colorImage,secret);
    cv::imwrite("./check.jpg",colorImage);
    string secret_message = extractMessage(colorImage,secret.size()*8);
    cout << secret_message << endl;

    padVector(imageVector,modifiedImageVector);

    cout << "<<<<< Plain text sensitivity test >>>>>"  << endl;
    cout << "NPCR: " << NPCR(imageVector,modifiedImageVector) << "%\n";
    cout << "UACI: " << UACI(imageVector,modifiedImageVector) << "%\n";
    cout << "Hammding Distance: " << hammingDistance(imageVector,modifiedImageVector) << "%\n";

    vector<ll> d = getFreq(matricize(encryptedImage,colorImage.rows,colorImage.cols));
    //frq(d);
    // fe(d);
    cout << "ChiSqaure: " << (chiSquare(d)? " Uniform\n" : " Not uniform\n");
    cout << "Correlation: " << getCorrelation(decryptedImage) << endl;
    cout << "Information Entropy: " << calculateInformationEntropy(decryptedImage) << endl;
    cout << "Encryption Quality: " << calculateEncryptionQuality(colorImage,decryptedImage) << endl;

    SecByteBlock key2 = getNewKey(key);
    cv::Mat colorImage2 = colorImage.clone();
    vector<unsigned char> image2Vector = vectorize(colorImage2);
    vector<unsigned char> encryptedImage2 = encryptImage(image2Vector,key2,iv);
    vector<unsigned char> temp(all(encryptedImage2));
    string encodeImage2 = base64Encode(temp);
    vector<unsigned char> secondImage2(all(encodeImage2));
    cv::Mat noisyEncryptedImage = matricize(secondImage2,colorImage2.cols,colorImage2.rows); //change dims;

    padVector(imageVector,image2Vector);

    // vector<ll> newTest = getFreq(decryptedImage2);
    // fe(newTest);

    cout << "\b<<<<< Key sensitivity >>>>>" << endl;
    cout << imageVector.size() << ' ' << image2Vector.size() << endl;
    cout << "NPCR: " << NPCR(imageVector, image2Vector) << "%\n";
    cout << "UACI: " << UACI(imageVector,image2Vector) << "%\n";
    cout << "Hamming Distance: " << hammingDistance(imageVector,image2Vector) << "%\n";
    vector<ll> newFreq = getFreq(matricize(encryptedImage2, colorImage2.rows,colorImage2.cols));
    // frq(newFreq);
    // fe(newFreq);
    cout << "Chisqaure: " << (chiSquare(newFreq) ? " Uniform" : " Not Uniform") << endl;
    cout << getCorrelation(noisyEncryptedImage) << endl;
    cout << "Information Entropy: " << calculateInformationEntropy(noisyEncryptedImage) << endl;



    return 0;
}