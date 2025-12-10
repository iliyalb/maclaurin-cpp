#include "maclaurin.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>

MaclaurinCalculator::MaclaurinCalculator(int loops)
    : numberOfLoops_{loops}
{
    ensureFactorials(loops * 2 + 2);
}

void MaclaurinCalculator::setLoops(int loops) noexcept {
    numberOfLoops_ = std::max(1, loops);
    ensureFactorials(numberOfLoops_ * 2 + 2);
}

int MaclaurinCalculator::getLoops() const noexcept {
    return numberOfLoops_;
}

void MaclaurinCalculator::ensureFactorials(std::size_t n) {
    if (factorialCache_.size() > n) return;

    std::size_t oldSize = factorialCache_.size();
    if (oldSize == 0) {
        factorialCache_.push_back(1.0L);
        oldSize = 1;
    }
    factorialCache_.reserve(n + 1);

    for (std::size_t i = oldSize; i <= n; ++i) {
        factorialCache_.push_back(factorialCache_.back() * static_cast<long double>(i));
    }
}

long double MaclaurinCalculator::factorial(std::size_t n) {
    ensureFactorials(n);
    return factorialCache_[n];
}

void MaclaurinCalculator::displayMenu() const {
    std::cout <<
        "\nPlease choose an option (Maclaurin):\n"
        "0. Exit\n"
        "1. Change number of loops (current: " << numberOfLoops_ << ")\n"
        "2. Sin(x)\n"
        "3. Cos(x)\n"
        "4. e^x\n"
        "5. Arc Tan(x)\n"
        "6. Tan(x)\n"
        "7. Ln(1+x)\n"
        "8. Sinh(x)\n"
        "9. Cosh(x)\n";
}

long double MaclaurinCalculator::sinX(long double x) {
    long double sum = 0.0L;
    for (int i = 0; i < numberOfLoops_; ++i) {
        long double step = ( (i % 2 == 0) ? 1.0L : -1.0L )
                         * std::pow(x, 2*i + 1)
                         / factorial(2*i + 1);
        sum += step;
    }
    return sum;
}

long double MaclaurinCalculator::cosX(long double x) {
    long double sum = 0.0L;
    for (int i = 0; i < numberOfLoops_; ++i) {
        long double step = ( (i % 2 == 0) ? 1.0L : -1.0L )
                         * std::pow(x, 2*i)
                         / factorial(2*i);
        sum += step;
    }
    return sum;
}

long double MaclaurinCalculator::expX(long double x) {
    long double sum = 0.0L;
    for (int i = 0; i < numberOfLoops_; ++i) {
        sum += std::pow(x, i) / factorial(i);
    }
    return sum;
}

long double MaclaurinCalculator::atanX(long double x) {
    long double sum = 0.0L;
    for (int i = 0; i < numberOfLoops_; ++i) {
        long double step = ( (i % 2 == 0) ? 1.0L : -1.0L ) *
                            std::pow(x, 2*i + 1) / (2*i + 1);
        sum += step;
    }
    return sum;
}

long double MaclaurinCalculator::tanX(long double x) {
    return sinX(x) / cosX(x);
}

long double MaclaurinCalculator::ln1pX(long double x) {
    long double sum = 0.0L;
    for (int i = 1; i < numberOfLoops_; ++i) {
        long double step = ( (i % 2 == 1) ? 1.0L : -1.0L )
                         * std::pow(x, i) / i;
        sum += step;
    }
    return sum;
}

long double MaclaurinCalculator::sinhX(long double x) {
    long double sum = 0.0L;
    for (int i = 0; i < numberOfLoops_; ++i) {
        sum += std::pow(x, 2*i + 1) / factorial(2*i + 1);
    }
    return sum;
}

long double MaclaurinCalculator::coshX(long double x) {
    long double sum = 0.0L;
    for (int i = 0; i < numberOfLoops_; ++i) {
        sum += std::pow(x, 2*i) / factorial(2*i);
    }
    return sum;
}

void MaclaurinCalculator::runInteractive() {
    using Fn = std::function<long double(MaclaurinCalculator&, long double)>;

    const std::vector<std::pair<std::string, Fn>> actions = {
        { "Sin(x)",   &MaclaurinCalculator::sinX   },
        { "Cos(x)",   &MaclaurinCalculator::cosX   },
        { "e^x",      &MaclaurinCalculator::expX   },
        { "ArcTan(x)",&MaclaurinCalculator::atanX  },
        { "Tan(x)",   &MaclaurinCalculator::tanX   },
        { "Ln(1+x)",  &MaclaurinCalculator::ln1pX  },
        { "Sinh(x)",  &MaclaurinCalculator::sinhX  },
        { "Cosh(x)",  &MaclaurinCalculator::coshX  }
    };

    while (true) {
        displayMenu();
        int choice{};
        std::cin >> choice;

        if (!std::cin) return;
        if (choice == 0) return;

        if (choice == 1) {
            int loops{};
            std::cout << "Enter new loop count: ";
            std::cin >> loops;
            setLoops(loops);
            continue;
        }

        if (choice >= 2 && choice <= 9) {
            auto index = choice - 2;
            long double x{};
            std::cout << "Enter x: ";
            std::cin >> x;

            long double result = actions[index].second(*this, x);
            std::cout << "Result (" << actions[index].first
                      << "): " << std::setprecision(15)
                      << result << "\n";
            continue;
        }

        std::cout << "Unknown option.\n";
    }
}
