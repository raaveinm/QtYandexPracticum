//
// Created by Kirill "Raaveinm" on 9/12/25.
//

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <string>
#include <cmath>

using Number = double;

class Calculator {
public:
    static bool RunCalculatorCycle();
    void Add(Number right);
    void Set(Number number);
    void Sub(Number right);
    void Mul(Number right);
    void Div(Number right);
    void Pow(Number right);
    void Save();
    void Load();
    [[nodiscard]] bool HasMem() const;
    [[nodiscard]] std::string GetNumberRepr() const;
    [[nodiscard]] Number GetNumber() const;

private:
    bool is_saved_ = false;
    bool is_init_ = false;
    Number current_res_ = 0.0;
    Number saved_number_ = 0.0;

    static bool ReadNumber(Number &result);
};


#endif //CALCULATOR_H