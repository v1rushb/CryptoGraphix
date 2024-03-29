#include "ImageReader.h"
#include <opencv2/opencv.hpp>
#include <stdexcept>

cv::Mat ImageReader::ReadImage(const string imagePath) const {
    cv::Mat image = cv::imread(imagePath,cv::IMREAD_COLOR);
    if(image.empty()) {
        throw runtime_error("Can not open the image with the path:" + imagePath);
    }
    return image;
};