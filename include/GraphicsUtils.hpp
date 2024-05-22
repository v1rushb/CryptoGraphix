#ifndef GRAPHICSUTILS_HPP
#define GRAPHICSUTILS_HPP

#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>

class GraphicsUtils {
private:
    static std::vector<int> p;

    static float fade(float t);
    static float lerp(float t, float a, float b);
    static float grad(int hash, float x, float y);

public:
    static float PerlinNoise(float x, float y);
    static cv::Mat GeneratePerlinNoiseImage(long int rows, long int cols, int channels = 1);
};

#endif // GRAPHICSUTILS_HPP
