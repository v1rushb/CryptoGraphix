#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

class ImageWriter {
    public:
        void WriteImage(const std::string& writePath, const cv::Mat& img) const;
};