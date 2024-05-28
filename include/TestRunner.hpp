#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include "ITest.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <string>

using namespace std;

class TestRunner {
private:
    map<string, shared_ptr<ITest>> tests;

public:
    void registerTest(const string& testName, shared_ptr<ITest> test) {
        tests[testName] = test;
    }

    void run(const string& testName) const {
        auto it = tests.find(testName);
        if (it != tests.end()) {
            Utils::print("Running test: " + testName, "Yellow");
            it->second->runTest();
        } else {
              Utils::print("Test '" + testName + "' not found.","Red");
        }
    }
};

#endif