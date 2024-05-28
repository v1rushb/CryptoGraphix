#ifndef TIMEPERFORMANCETEST_HPP
#define TIMEPERFORMANCETEST_HPP

#include "ITest.hpp"
#include "TestRunner.hpp"
#include <vector>
#include <stdexcept>
#include <functional>
#include "Utils.hpp"
#include <opencv2/opencv.hpp>

using namespace std;

class TimePerformanceTest : public ITest {
    private:
        cv::Mat img;
        function<void()> func;
    
    public:
        template<typename Obj, typename Method, typename... Args>
        TimePerformanceTest(const cv::Mat &image, Obj&& obj, Method method, Args&&... args)
            : img(image), func([=]() mutable {
                (obj->*method)(forward<Args>(args)...);
            }) {}
        
        double CalculateExecutionTime() const {
            return Utils::getExecutionTime(func);
        }

        void runTest() const override {
            try {
                double result = CalculateExecutionTime();
                Utils::print("Time Performance Test Result: " + to_string(result) + " Seconds","Yellow");
            } catch(const exception &ex) {
                Utils::print("An error occurred during UACI Test: " + string(ex.what()),"Red");
            }
        }
};

#endif