#include "ImageWriter.h"
#include <opencv2/imgcodecs.hpp>
#include <filesystem>

using namespace std;

void ImageWriter::WriteImage(const string& writePath, const cv::Mat& img) const {
    filesystem::path outputPath(writePath);
    auto parent = outputPath.parent_path();
    if(!filesystem::exists(parent)) {
        filesystem::create_directories(parent);
    }

    if(!cv::imwrite(writePath,img)) {
        throw runtime_error("Failed to write the image on path: " + writePath);
    }
}