// @author: oz.atar@msmail.ariel.ac.il

#pragma once

#include <iostream>
#include <stdexcept>

class Complex
{
    private:
        int real;
        int img;

    public:

        Complex(int real, int img) : real(real), img(img) {};
        Complex(const Complex& other) : real(other.real), img(other.img) {};
        Complex() : real(0), img(0) {};
        Complex(int real) : real(real), img(0) {};

        Complex& operator=(const Complex& other);

        int get_real() const { return real; }
        int get_img() const { return img; }

        Complex operator+(const Complex& other) const;
        Complex operator-(const Complex& other) const;
        Complex operator*(const Complex& other) const;
        Complex operator/(const Complex& other) const;

        bool operator==(const Complex& other) const;
        bool operator!=(const Complex& other) const;
        bool operator<(const Complex& other) const;
        bool operator>(const Complex& other) const;
        bool operator<=(const Complex& other) const;
        bool operator>=(const Complex& other) const;

        friend std::ostream& operator<<(std::ostream& os, const Complex& complex);
};