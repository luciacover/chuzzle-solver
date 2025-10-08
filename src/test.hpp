#ifndef TEST_HPP_
#define TEST_HPP_

#include <functional>
#include <string>
#include <vector>

typedef std::function<int()> testfn_t;

constexpr double PASSED_LIMIT = 0.9;
constexpr double OKAY_LIMIT = 0.6;

class Test {
protected:
  const std::string test_name;
  const int test_count;
  int successful = 0;

public:
  Test(const std::string &n, const int &c);
  virtual void run() = 0;
  std::string results();
};

class RepeatTest : public Test {
private:
  const testfn_t test_eval;

public:
  RepeatTest(const std::string &n, const int &c, const testfn_t &e);

  void run() override;
};

class MultiTest : public Test {
private:
  const std::vector<testfn_t> test_evals;

public:
  MultiTest(const std::string &n, const std::vector<testfn_t> &e);
  void run();
};

void run_tests();

#endif
