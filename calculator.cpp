
/*Kira Brown Johnson
 Due Date: 8/8/2025
 Final Project: Calculator
 Description: A simple OOP calculator using polymorphism/classes in C++
*/

#include <iostream>
#include <memory>
#include <stdexcept>

//Base Class: Operator
class Operator {
public:
    virtual double execute(double a, double b) const = 0;
    virtual ~Operator() {} 
};

//Addition Class
class Addition : public Operator {
public:
    double execute(double a, double b) const { 
        return a + b;
    }
};

//Subtraction Class
class Subtraction : public Operator {
public:
    double execute(double a, double b) const {
        return a - b;
    }
};

//Multiplication Class
class Multiplication : public Operator {
public:
    double execute(double a, double b) const {
        return a * b;
    }
};

//Division Class
class Division : public Operator {
public:
    double execute(double a, double b) const {
        if (b == 0) {
            throw std::runtime_error("Error: Cannot divide by 0!");
        }
        return a / b;
    }
};

//Calculator Class
class Calculator {
public:
    double calculate(double a, double b, const Operator& op) const {
        return op.execute(a, b);
    }
};


int main() {
    Calculator calc;
    double num_1, num_2;
    char choice;
    char again = 'y';

        std::string user_input;
    do {
        std::cout << "\nWelcome to my simple calculator\n";
        std::cout << "Enter the first number: ";
        std::cin >> num_1;

        std::cout << "Enter the second number: ";
        std::cin >> num_2;

        std::cout << "Choose an operation (+, -, *, /): ";
        std::cin >> choice;

        try {
            std::unique_ptr<Operator> op;

            switch (choice) {
                case '+': op.reset(new Addition()); break;
                case '-': op.reset(new Subtraction()); break;
                case '*': op.reset(new Multiplication()); break;
                case '/': op.reset(new Division()); break;
                default:
                    throw std::invalid_argument("Invalid Operator.");
            }

            double result = calc.calculate(num_1, num_2, *op);
            std::cout << "Result: " << result << "\n";
        } 
        //catches errors
        catch (const std::exception& e) {
            std::cerr << e.what() << "\n";
        }

        std::cout << "Do you want to calculate again? (y/n): ";
        std::cin >> user_input;
        if (user_input.empty()) user_input = "n"; // default to quit if no input

    } while (user_input[0] == 'y' || user_input[0] == 'Y');

    std::cout << "Have a great day!\n";
}
