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


using namespace std;
using namespace CryptoPP;

#define all(v) v.begin(),v.end();


int main() {
    try {
        ImageReader reader;
        ImageWriter writer;
        cv::Mat image = reader.ReadImage("../assets/besho.jpg");
        cv::Mat image2 = reader.ReadImage("../assets/neon.PNG");
        IEncrypt firstenc(make_unique<AES256Encryption>());
        cv::Mat encryptedImage = firstenc.Encrypt(image);
        cv::Mat encryptedImage2 = firstenc.Encrypt(image2);


        cv::Mat decryptedImage = firstenc.Decrypt(image);
        cv::Mat decryptedImage2 = firstenc.Decrypt(image2);

        writer.WriteImage("../assets/test_write.jpg", encryptedImage);
        writer.WriteImage("../assets/test_write2.jpg", encryptedImage2);
        cout << "Image written successfully." << endl;
    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return -1;
    }

    return 0;
}
