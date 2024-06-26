#include "ImageWriter.h"
#include <opencv2/imgcodecs.hpp>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include "Utils.hpp"

using namespace std;

const string _WRITE_PATH = "../assets/";

bool isDuplicated(string &writePath, const vector<string> &files)
{
    return find(files.begin(), files.end(), writePath) != files.end();
}

string appendSuffix(string writePath, const bool &encrypted)
{
    auto currentFileName = Utils::SplitStringIntoPair(writePath, '.');
    if (encrypted)
    {
        currentFileName.first.insert(currentFileName.first.size(), " (ENCRYPTED)");
    }
    else
    {
        currentFileName.first.insert(currentFileName.first.size(), " (DECRYPTED)");
    }
    return _WRITE_PATH + currentFileName.first + "." + currentFileName.second;
}

string getValidated(string writePath, const vector<string> &files, const bool &encrypted)
{ // const bool &isSpecial  add later for steganography.
    string outputFile = Utils::SplitAndReturnLastPart(writePath);
    outputFile = Utils::removeEncryptionTags(outputFile);
    auto slicedOutputFile = Utils::SplitStringIntoPair(outputFile, '.');
    slicedOutputFile.first = Utils::splitNameAndNumber(slicedOutputFile.first);
    outputFile = slicedOutputFile.first + '.' + slicedOutputFile.second;
    unordered_map<string, int> mp;
    for (auto &el : files)
    {
        auto currentFileName = Utils::SplitStringIntoPair(el, '.');
        currentFileName.first = Utils::splitNameAndNumber(currentFileName.first);
        mp[currentFileName.first + "." + currentFileName.second]++;
    }
    if (isDuplicated(outputFile, files))
    {
        int version(0);
        for (auto &el : mp)
        {
            if (el.first == outputFile)
            {
                version = ++el.second;
                ll idx(outputFile.size() - 1);
                for (ll o = outputFile.size() - 1; o >= 0; o--)
                {
                    if (outputFile[o] == '.')
                    {
                        idx = o;
                        break;
                    }
                }
                outputFile.insert(idx, to_string(version));
            }
        }
    }
    return appendSuffix(outputFile, encrypted);
}

void ImageWriter::WriteImage(const string &writePath, const cv::Mat &img, const bool &encrypted) const
{
    string updatedWritePath = writePath;
    if (Utils::SplitAndReturnLastPart(writePath).size() <= 1)
    {
        updatedWritePath = _WRITE_PATH + "GeneratedImage.bmp";
    }
    filesystem::path outputPath(updatedWritePath);
    auto parent = outputPath.parent_path();
    if (!filesystem::exists(parent))
    {
        filesystem::create_directories(parent);
    }

    const vector<string> files = Utils::getDirectoryFiles("../assets/");
    string newWritePath = getValidated(updatedWritePath, files, encrypted);

    if (!cv::imwrite(newWritePath, img))
    {
        throw runtime_error("Failed to write the image on path: " + newWritePath);
    }
    Utils::print(newWritePath, "Yellow");
}