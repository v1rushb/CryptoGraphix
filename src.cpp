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

using namespace std;
using namespace CryptoPP;

#define ll long long int
#define all(v) v.begin(),v.end()
#define endl '\n'

string outputDirectory = "./resources/";

vector<char> readImage(const string &imagePath) {
    ifstream file(imagePath, ios::binary);
    if (!file) {
        cout << "Cannot open the image with path: " << imagePath << endl;
        return {};
    }
    file.seekg(0, ios::end);
    streamsize size = file.tellg();
    file.seekg(0, ios::beg);

    vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        cout << "Cannot read the image with path: " << imagePath << endl;
        return {};
    }
    return buffer;
}

bool writeImage(const string &distPath, const vector<char> &imageData) {
    ofstream file(distPath, ios::binary | ios::out);
    if (!file) {
        cout << "Cannot open the file for writing: " << distPath << endl;
        return false;
    }

    if (!file.write(imageData.data(), imageData.size())) {
        cout << "Cannot write to file: " << distPath << endl;
        return false;
    }
    return true;
}

vector<char> encryptImage(const vector<char> &data, const SecByteBlock &key, const CryptoPP::byte iv[AES::BLOCKSIZE]) {
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
    return vector<char>(all(encrypted));
}

vector<char> decryptImage(const vector<char> &data, const SecByteBlock &key, const CryptoPP::byte iv[AES::BLOCKSIZE]) {
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

double NPCR(const vector<char> &img1, const vector<char> &img2) {
    if(img1.size() - img2.size())
    {
        cerr << "SizeDifferenceException" << endl;
        exit(1);
    }
    
    ll diff(0);
    for(ll o = 0; o < img1.size();o++)
        diff+=img1[o]!=img2[o];
    return (diff / (double) img1.size()) * 100.0;
}

double UACI(const vector<char> &img1, const vector<char> &img2) {
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

double hammingDistance(const vector<char> &img1, const vector<char> &img2) {
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

vector<ll> getFreq(const vector<char> &img) {
    vector<ll> freq(256,0);
    for(int o = 0; o < img.size();o++)
        freq[static_cast<unsigned int>(static_cast<unsigned char>(img[o]))]++;
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

bool chiSqaure(const vector<ll> &freq) {
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

//Helper functions.

void printKey(const SecByteBlock &key) {
    string hexKey;
    HexEncoder encoder;

    encoder.Attach(new StringSink(hexKey));
    encoder.Put(key,key.size());
    encoder.MessageEnd();

    cout << hexKey << endl;
} 

int main() {
    string imagePath = "./neon.jpg";
    string encryptedPath = outputDirectory + "encrypted_img.jpeg";
    string decryptedPath = outputDirectory + "decrypted_img.jpeg";

    if (!filesystem::exists(outputDirectory)) {
        filesystem::create_directory(outputDirectory);
    }

    vector<char> imageData = readImage(imagePath);
    vector<char> modifiedImageData = imageData;
    modifiedImageData[0] ^= 1;
    if (imageData.empty()) {
        cout << "Failed to read image." << endl;
        return 1;
    }

    AutoSeededRandomPool prng;
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    prng.GenerateBlock(key, key.size());
    CryptoPP::byte iv[AES::BLOCKSIZE];
    prng.GenerateBlock(iv, sizeof(iv));

    vector<char> encryptedImg = encryptImage(imageData, key, iv);
    vector<char> encryptedModifiedImg = encryptImage(modifiedImageData,key,iv);
    if (writeImage(encryptedPath, encryptedImg)) {
        cout << "Encrypted image written to: " << encryptedPath << endl;
    } else {
        return 1;
    }

    vector<char> decryptedImg = decryptImage(encryptedImg, key, iv);
    if (writeImage(decryptedPath, decryptedImg)) {
        cout << "Decrypted image written to: " << decryptedPath << endl;
    } else {
        return 1;
    }

    cout << "NPCR: " << NPCR(encryptedImg,encryptedModifiedImg) << '%' << endl;
    cout << "UACI: " << UACI(encryptedImg,encryptedModifiedImg) << '%' << endl;
    cout << "HD: " << hammingDistance(encryptedImg,encryptedModifiedImg) << '%' << endl;

    vector<ll> d = getFreq(encryptedImg);
    cout << "ChiSqaure: " << (chiSqaure(d)? " Uniform" : " Not uniform") << endl;

    return 0;
}
