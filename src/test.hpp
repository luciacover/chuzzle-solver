#ifndef TEST_HPP_
#define TEST_HPP_

#include <string>
#include <format>
#include <vector>
#include <functional>

typedef std::function<int()> testfn_t;

constexpr double PASSED_LIMIT = 0.9;
constexpr double OKAY_LIMIT   = 0.6;

class Test {
  protected:
    const std::string test_name;
    const int test_count;
    int successful = 0;
  public:
    Test(const std::string &n, const int &c) : test_name(n), test_count(c) {};
    virtual void run() = 0;
    std::string results() {
      const double correct_ratio = this->successful / (double)this->test_count;
      return std::format("[{}{}\e[0m]: {} of {} test(s) passed.", (correct_ratio >= PASSED_LIMIT) ? "\e[1;92m" :
                                                                  (correct_ratio >= OKAY_LIMIT)   ? "\e[1;93m" : "\e[1;91m",
                                                                  this->test_name, this->successful, this->test_count);
    }
};

class RepeatTest : public Test {
  private:
    const testfn_t test_eval;
  public:
    RepeatTest(const std::string &n, const int &c, const testfn_t &e) : Test(n, c), test_eval(e) {};
    
    void run() override {
      for (int i = 0; i < this->test_count; i++) {
        this->successful += this->test_eval();
      }
    }
};

class MultiTest : public Test {
  private:
    const std::vector<testfn_t> test_evals;
  public:
    MultiTest(const std::string &n, const std::vector<testfn_t> &e) : Test(n, e.size()), test_evals(e) {};

    void run() override {
      for (const auto &test_eval : this->test_evals) {
        this->successful += test_eval();
      }
    }
};

void zobrist_test();
void slide_test();

#endif
