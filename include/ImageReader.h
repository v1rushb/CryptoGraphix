#ifndef IMAGEREADER_H
#define IMAGEREADER_H

#include <opencv2/opencv.hpp>
#include <string>
using namespace std;

class ImageReader {
    public:
        cv::Mat ReadImage(const string imagePath, const bool colored = true) const;
};

#endif