#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>

using namespace std;
using namespace CryptoPP;

#define ll long long int

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
    return vector<char>(encrypted.begin(), encrypted.end());
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
    return vector<char>(decrypted.begin(), decrypted.end());
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
        s+=abs(img1[o]-'0' - img2[o]-'0')/255.0;
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
        ll x = (img1[o] - '0') ^ (img2[o]-'0');
        for(int bit = 0; bit < 8;bit++) {
            dist += (x >> bit) &1;
        }
    }
    return (dist/ (double) (img1.size()*8)) * 100;
}

int main() {
    string imagePath = "./Sasha.jpg";
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

    return 0;
}
