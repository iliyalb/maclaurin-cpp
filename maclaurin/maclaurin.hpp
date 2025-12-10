#pragma once
#include <vector>

class MaclaurinCalculator {
public:
    explicit MaclaurinCalculator(int loops = 10);

    void setLoops(int loops) noexcept;
    [[nodiscard]] int getLoops() const noexcept;

    void displayMenu() const;

    [[nodiscard]] long double sinX(long double x);
    [[nodiscard]] long double cosX(long double x);
    [[nodiscard]] long double expX(long double x);
    [[nodiscard]] long double atanX(long double x);
    [[nodiscard]] long double tanX(long double x);
    [[nodiscard]] long double ln1pX(long double x);
    [[nodiscard]] long double sinhX(long double x);
    [[nodiscard]] long double coshX(long double x);

    void runInteractive();

private:
    int numberOfLoops_;
    std::vector<long double> factorialCache_;

    void ensureFactorials(std::size_t n);
    [[nodiscard]] long double factorial(std::size_t n);
};
