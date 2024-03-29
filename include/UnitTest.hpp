#ifndef UNITTEST_HPP
#define UNITTEST_HPP

#include "AES256Encryption.hpp"
#include "Utils.hpp"
#include "NPCRTest.hpp"
#include "UACI.hpp"
#include "HammingDistanceTest.hpp"
#include "ChisquareTest.hpp"
#include "CorrelationTest.hpp"
#include "InformationEntropyTest.hpp"
#include "EncryptionQualityTest.hpp"

using namespace std;

class UnitTest {
    private:
        vector<pair<string, shared_ptr<ITest>>> tests;
public:
    void addTest(const string& testName, shared_ptr<ITest> test) {
        tests.emplace_back(testName, test);
    }

    void runAllTests(TestRunner& runner) {
        for (const auto& test : tests) {
            const auto& testName = test.first;
            const auto& testPtr = test.second;
            runner.registerTest(testName, testPtr);
            runner.run(testName);
        }
    }
};

#endif