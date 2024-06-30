// @author: oz.atar@msmail.ariel.ac.il

#include "Complex.hpp"


Complex& Complex::operator=(const Complex& other)
{
    this->real = other.real;
    this->img = other.img;
    return *this;
}

Complex Complex::operator+(const Complex& other) const
{
    return Complex(this->real + other.real, this->img + other.img);
}

Complex Complex::operator-(const Complex& other) const
{
    return Complex(this->real - other.real, this->img - other.img);
}

Complex Complex::operator*(const Complex& other) const
{
    return Complex(this->real * other.real - this->img * other.img, this->real * other.img + this->img * other.real);
}

Complex Complex::operator/(const Complex& other) const
{
    int denominator = other.real * other.real + other.img * other.img;
    if(denominator == 0)
        throw std::invalid_argument("Division by zero!");
    return Complex((this->real * other.real + this->img * other.img) / denominator, (this->img * other.real - this->real * other.img) / denominator);
}

bool Complex::operator==(const Complex& other) const
{
    return this->real == other.real && this->img == other.img;
}

bool Complex::operator!=(const Complex& other) const
{
    return !(*this == other);
}

bool Complex::operator<(const Complex& other) const
{
    return this->real < other.real || (this->real == other.real && this->img < other.img);
}

bool Complex::operator>(const Complex& other) const
{
    return this->real > other.real || (this->real == other.real && this->img > other.img);
}

bool Complex::operator<=(const Complex& other) const
{
    return *this < other || *this == other;
}

bool Complex::operator>=(const Complex& other) const
{
    return *this > other || *this == other;
}

std::ostream& operator<<(std::ostream& os, const Complex& complex)
{
    os << complex.real << " + " << complex.img << "i";
    return os;
}