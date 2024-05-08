#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

class ImageWriter {
    public:
        void WriteImage(const string& writePath, const cv::Mat& img, const bool &encrypted = 1) const;
};