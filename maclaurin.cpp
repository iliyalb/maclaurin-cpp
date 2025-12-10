#include <iostream>
#include <cmath>
#include <iomanip>

// https://mathworld.wolfram.com/MaclaurinSeries.html

int numberOfLoops = 10;

void displayMenu()
{
    std::cout << "\nPlease choose an option (Maclaurin):\n"
              << "0. Exit\n"
              << "1. Change number of loops (current: " << numberOfLoops << ")\n"
              << "2. Sin(x)\n"
              << "3. Cos(x)\n"
              << "4. e^x\n"
              << "5. Arc Tan(x)\n"
              << "6. Tan(x)\n"
              << "7. Ln(1+x) (lnx does not exist, ln 0 is undefined)\n"
              << "8. Sinh(x)\n"
              << "9. Cosh(x)\n";
}

void changeNumberOfLoops()
{
        std::cout << "Please Enter How Many Number Of Loops You Want: \n";
        std::cin >> numberOfLoops;
}

double factorial(unsigned int n)
{
    long double result = 1.0;
    for (unsigned int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

long double sinX(long double x)
{
    
    long double sum = 0.0;
    for (int i = 0; i < numberOfLoops; i++)
    {
        long double step = std::pow(-1,i) *
                ( std::pow(x,(2*i+1)) /
                 factorial((2*i+1)) );
        sum += step;
    }
    std::cout << "Output of maclaurin sin: " << std::setprecision(15) << sum << std::endl;
    return sum;
}

long double cosX(long double x)
{
    
    long double sum = 0.0;
    for (int i = 0; i < numberOfLoops; i++)
    {
        long double step = std::pow(-1,i) *
                ( std::pow(x,(2*i)) /
                factorial((2*i)) );
        sum += step;
    }
    std::cout << "Output of maclaurin cos: " << std::setprecision(15) << sum << std::endl;
    return sum;
}

void ePowX()
{
    long double x = 0.0;
    long double sum = 0.0;
    std::cout << "Please Enter A Number: (x)\n";
    std::cin >> x;

    for (int i = 0; i < numberOfLoops; i++)
    {
        long double step = std::pow(x,i)/factorial(i);
        sum += step;
    }
    std::cout << "Output of maclaurin e^x: " << std::setprecision(15) << sum << std::endl;
}

void arcTanX()
{
    long double x = 0.0;
    long double sum = 0.0;
    std::cout << "Please Enter A Number: (x)\n";
    std::cin >> x;

    for (int i = 0; i < numberOfLoops; i++)
    {
        double sign = (i % 2 == 0) ? 1.0 : -1.0;
        long double denom = 2*i+1;
        long double step = sign *
                           std::pow(x, 2*i+1)/
                           denom;
        sum += step;
    }
    std::cout << "Output of maclaurin ArcTan: " << std::setprecision(15) << sum << std::endl;
}

void tanX()
{
    long double x = 0.0;
    long double sum = 0.0;
    std::cout << "Please Enter A Number: (x)\n";
    std::cin >> x;
    
    sum = sinX(x)/cosX(x);
    std::cout << "Output of maclaurin Tan: " << std::setprecision(15) << sum << std::endl;
}

void lnx()
{
    long double x = 0.0;
    long double sum = 0.0;
    std::cout << "Please Enter A Number: (x)\n";
    std::cin >> x;

    for (int i = 1; i < numberOfLoops; i++)
    {
        long double step = std::pow(-1, i+1) * std::pow(x, i) / i;
        sum += step;
    }
    std::cout << "Output of maclaurin Ln(1+x): " << std::setprecision(15) << sum << std::endl;
}

void sinh()
{
    long double x = 0.0;
    long double sum = 0.0;
    std::cout << "Please Enter A Number: (x)\n";
    std::cin >> x;

    for (int i = 0; i < numberOfLoops; i++)
    {
        long double step = std::pow(x, 2*i+1) / factorial(2*i+1);
        sum += step;
    }
    std::cout << "Output of maclaurin Sinh: " << std::setprecision(15) << sum << std::endl;
}

void cosh()
{
    long double x = 0.0;
    long double sum = 0.0;
    std::cout << "Please Enter A Number: (x)\n";
    std::cin >> x;

    for (int i = 0; i < numberOfLoops; i++)
    {
        long double step = std::pow(x, 2*i) / factorial(2*i);
        sum += step;
    }
    std::cout << "Output of maclaurin Cosh: " << std::setprecision(15) << sum << std::endl;
}

int main()
{
    

    bool inLoop = true;
    int userInput;
    
    while(inLoop)
    {
        displayMenu();
        std::cin >> userInput;
        switch (userInput)
        {
        case 0:
            inLoop = false;
            break;

        case 1:
            changeNumberOfLoops();
            break;
        
        case 2:{
            long double x = 0.0;
            std::cout << "Please Enter A Number: (x)\n";
            std::cin >> x;
            sinX(x);
            break;
        }

        case 3:{
            long double n = 0.0;
            std::cout << "Please Enter A Number: (x)\n";
            std::cin >> n;
            cosX(n);
            break;
        }
        
        case 4:
            ePowX();
            break;

        case 5:
            arcTanX();
            break;

        case 6:
            tanX();
            break;
        
        case 7:
            lnx();
            break;

        case 8:
            sinh();
            break;

        case 9:
            cosh();
            break;

        default:
            std::cout<<"Unknown Input\n";
            break;
        }
    }
    std::cin.get();
    return 0;
} //AmirMahan Koshki