#ifndef CORRELATIONTEST_HPP
#define CORRELATIONTEST_HPP

#include "ITest.hpp"
#include "TestRunner.hpp"
#include <vector>
#include <stdexcept>
#include <opencv2/opencv.hpp>

using namespace std;

#define ll long long int

class CorrelationTest : public ITest {
    private:
        cv::Mat img;
    
    public:

        CorrelationTest(const cv::Mat &image)
            : img(image) {}
        
        long double CalculateHorizontalCorrelation(const cv::Mat &img, short channel) const {
            long double sumX = 0,sumY = 0, sumXY =0, sumX2 = 0, sumY2 = 0.0;
            ll n(0);
            for(int o = 0; o < img.rows;o++) {
                for(int i = 0; i < img.cols;i++) {
                    uchar xPixel = img.at<cv::Vec3b>(o,i)[channel];
                    uchar yPixel = img.at<cv::Vec3b>(o,i+1)[channel];
                    sumX +=xPixel;
                    sumY +=yPixel;
                    sumXY += xPixel * yPixel;
                    sumX2 += pow(xPixel,2);
                    sumY2 += pow(yPixel,2);
                    ++n;
                }
            }
            long double xMean = sumX / n, yMean = sumY / n, numerator = n * sumXY - sumX * sumY;
            double denominator = sqrt((n * sumX2 - sumX * sumX) * (n*sumY2 - sumY * sumY));
            return numerator/denominator; 
        }

        long double CalculateVerticalCorrelation(const cv::Mat &img, short channel) const {
            long double sumX = 0,sumY = 0, sumXY =0, sumX2 = 0, sumY2 = 0.0;
            ll n(0);
            for(int o = 0; o < img.rows;o++) {
                for(int i = 0; i < img.cols;i++) {
                    uchar xPixel = img.at<cv::Vec3b>(o,i)[channel];
                    uchar yPixel = img.at<cv::Vec3b>(o+1,i)[channel];
                    sumX +=xPixel;
                    sumY +=yPixel;
                    sumXY += xPixel * yPixel;
                    sumX2 += pow(xPixel,2);
                    sumY2 += pow(yPixel,2);
                    ++n;
                }
            }
            long double xMean = sumX / n, yMean = sumY / n, numerator = n * sumXY - sumX * sumY;
            double denominator = sqrt((n * sumX2 - sumX * sumX) * (n*sumY2 - sumY * sumY));
            return numerator/denominator; 
        }

        long double CalculateDiagonalCorrelation(const cv::Mat &img, short channel) const {
            long double sumX = 0,sumY = 0, sumXY =0, sumX2 = 0, sumY2 = 0.0;
            ll n(0);
            for(int o = 0; o < img.rows;o++) {
                for(int i = 0; i < img.cols;i++) {
                    uchar xPixel = img.at<cv::Vec3b>(o,i)[channel];
                    uchar yPixel = img.at<cv::Vec3b>(o+1,i+1)[channel];
                    sumX +=xPixel;
                    sumY +=yPixel;
                    sumXY += xPixel * yPixel;
                    sumX2 += pow(xPixel,2);
                    sumY2 += pow(yPixel,2);
                    ++n;
                }
            }
            long double xMean = sumX / n, yMean = sumY / n, numerator = n * sumXY - sumX * sumY;
            double denominator = sqrt((n * sumX2 - sumX * sumX) * (n*sumY2 - sumY * sumY));
            return numerator/denominator; 
        }

        double CalculateCorrelation(const cv::Mat &img) const {
            vector<double> correlations;
            const short channels = img.channels();
            for(int o = 0; o < channels;o++) {
                correlations.push_back(CalculateHorizontalCorrelation(img,o));
                correlations.push_back(CalculateVerticalCorrelation(img,o));   
                correlations.push_back(CalculateDiagonalCorrelation(img,o));
            }
            double sum = accumulate(correlations.begin(),correlations.end(),0.0);
            return sum / correlations.size();
        }


        void runTest() const override {
            try {
                double result = CalculateCorrelation(img);
                cout << "Correlation Test Result: " << result << endl;
            } catch(const exception &ex) {
                cout << "An error occurred during Correlation Test: " << ex.what() << endl;
            }
        }
};

#endif