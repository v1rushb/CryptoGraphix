#ifndef ITEST_HPP
#define ITEST_HPP
class ITest {
public:
    virtual ~ITest() {}
    virtual void runTest() const = 0;
};

#endif