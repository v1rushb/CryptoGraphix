#ifndef FILELISTER_CPP
#define FILELISTER_CPP

#include <filesystem>
#include <vector>
#include <algorithm>

using namespace std;
namespace fs = filesystem;

class FileLister {
public:
    static vector<string> listFilesInDirectory(const string &path) {
        vector<string> files;
        if (fs::exists(path) && fs::is_directory(path)) {
            for (const auto &entry : fs::directory_iterator(path)) {
                auto filename = entry.path().filename().string();
                string filename_lower = filename;
                transform(filename_lower.begin(), filename_lower.end(), filename_lower.begin(),
                               [](unsigned char c){ return tolower(c); });

                if (!(ends_with(filename_lower, ".jpg") || ends_with(filename_lower, ".jpeg"))) {
                    files.push_back(filename);
                }
            }
        }
        return files;
    }

private:
    static bool ends_with(const string& value, const string& ending) {
        if (ending.size() > value.size()) return false;
        return equal(ending.rbegin(), ending.rend(), value.rbegin());
    }
};

#endif