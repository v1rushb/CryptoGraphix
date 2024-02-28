#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

using namespace std;

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


int main() {
    string imagePath = "./Sasha.jpg";
    string encryptedPath = outputDirectory + "encrypted_img.jpeg";
    string decryptedPath = outputDirectory + "decrypted_img.jpeg";

    if (!filesystem::exists(outputDirectory)) {
        filesystem::create_directory(outputDirectory);
    }

    vector<char> imageData = readImage(imagePath);
    if (imageData.empty()) {
        cout << "Failed to read image." << endl;
        return 1;
    }
    if (writeImage(decryptedPath, imageData)) {
        cout << "Decrypted image written to: " << decryptedPath << endl;
    } else {
        return 1;
    }

    return 0;
}
