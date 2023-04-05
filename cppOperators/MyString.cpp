/*  MyString.cpp
 *
 *  Program to practice overloading operator().
 *
 */

#include <cassert>
#include <iostream>
#include <string>
#include <string_view>

class MyString
{
private:
    std::string m_string{};

public:
    MyString(const std::string& string={}) : m_string{ string }
    {}

    friend std::ostream& operator<<(std::ostream& out, const MyString& str);
    MyString operator()(int start_ind, int length);
    std::string_view substr(int start_ind, int length);
};

std::ostream& operator<<(std::ostream& out, const MyString& str)
{
    out << str.m_string;

    return out;
}

MyString MyString::operator()(int start_ind, int length)
{
    assert(start_ind >= 0 && "MyString::operator(int, int): Negative starting index.");
    assert(start_ind + length <= static_cast<int>(m_string.length()) && "MyString::operator(int, int): Substring length out of range.");

    return m_string.substr(start_ind, length);
}

std::string_view MyString::substr(int start_ind, int length)
{
    assert(start_ind >= 0 && "MyString::substr(int, int): Negative starting index.");
    assert(start_ind + length <= static_cast<int>(m_string.length()) && "MyString::substr(int, int): Substring length out of range.");

    return std::string_view{ m_string }.substr(start_ind, length);
} 

int main()
{
    MyString s{ "Hello, world!" };
    std::cout << s(7, 5) << '\n';

    return 0;
}
