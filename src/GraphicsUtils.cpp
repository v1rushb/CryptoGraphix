#include "GraphicsUtils.hpp"
#include <random>
#include "Utils.hpp"
#include <vector>

vector<int> GraphicsUtils::p = []{
    vector<int> p(256);
    iota(p.begin(), p.end(), 0);
    mt19937 access(Utils::GenerateARandomInteger());
    shuffle(p.begin(), p.end(), access);
    p.insert(p.end(), p.begin(), p.end());
    return p;
}();

float GraphicsUtils::fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float GraphicsUtils::lerp(float t, float a, float b) {
    return a + t * (b - a);
}

float GraphicsUtils::grad(int hash, float x, float y) {
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : (h == 12 || h == 14 ? x : 0);
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float GraphicsUtils::PerlinNoise(float x, float y) {
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    x -= floor(x);
    y -= floor(y);
    float u = fade(x);
    float v = fade(y);
    int A = p[X] + Y;
    int B = p[X + 1] + Y;
    return lerp(v, lerp(u, grad(p[A], x, y), grad(p[B], x - 1, y)),
                   lerp(u, grad(p[A + 1], x, y - 1), grad(p[B + 1], x - 1, y - 1)));
}

cv::Mat GraphicsUtils::GeneratePerlinNoiseImage(long int rows, long int cols, int channels) {
    cv::Mat image(rows, cols, CV_8UC(channels));
    for (long int o = 0; o < rows; o++) {
        for (long int i = 0; i < cols; i++) {
            float value = PerlinNoise(o * 0.1f, i * 0.1f) * 255;
            if (channels == 1) {
                image.at<uchar>(o, i) = static_cast<uchar>(value);
            } else if (channels == 3) {
                cv::Vec3b& pixel = image.at<cv::Vec3b>(o, i);
                pixel[0] = static_cast<uchar>(value);
                pixel[1] = static_cast<uchar>(value);
                pixel[2] = static_cast<uchar>(value);
            }
        }
    }
    return image;
}
