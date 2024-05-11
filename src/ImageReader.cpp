#include "ImageReader.h"
#include <opencv2/opencv.hpp>
#include <stdexcept>
#include "ErrorHandler.cpp"
#include "Utils.hpp"

cv::Mat ImageReader::ReadImage(const string imagePath, const bool colored) const {
    cv::Mat image;
    // string newImagePath = Utils::removeEncryptionTags(imagePath);
    image = cv::imread(imagePath,(colored ? cv::IMREAD_COLOR : cv::IMREAD_GRAYSCALE));
    if(image.empty()) {
        throw CustomException("Can not open the image with the path:" + imagePath);
    }
    return image;
};