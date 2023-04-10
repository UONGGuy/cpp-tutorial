/*  Fruit.cpp
 *
 *  Program to practice inheritance.
 *
 */

#include <iostream>
#include <string>
#include <string_view>

class Fruit
{
private:
    std::string m_name{};
    std::string m_color{};

public:
    Fruit() = default;
    Fruit(std::string_view name, std::string_view color)
        : m_name{ name }, m_color{ color }
    {}

    const std::string& getName() const { return m_name; }
    const std::string& getColor() const { return m_color; }
};

class Apple: public Fruit
{
private:
    double m_fiber{};

public:
    Apple(std::string_view name, std::string_view color, double fiber)
        : Fruit(name, color), m_fiber{ fiber }
    {}

    friend std::ostream& operator<<(std::ostream& out, const Apple& apple)
    {
        out << "Apple(" << apple.getName() << ", " << apple.getColor() << ", " << apple.m_fiber << ")";

        return out;
    }
};

class Bannana: public Fruit
{
public:
    Bannana(std::string_view name, std::string_view color)
        : Fruit(name, color)
    {}

    friend std::ostream& operator<<(std::ostream& out, const Bannana& bannana)
    {
        out << "Apple(" << bannana.getName() << ", " << bannana.getColor() << ")";

        return out;
    }
};
        
class GrannySmith: public Apple
{
public:
    GrannySmith() : Apple("granny smith", "green", 0.0)
    {}
};

int main()
{
    const Apple a{ "Red delicious", "red", 4.2 };
    std::cout << a << '\n';

    const Bannana b{ "Cavendish", "yellow" };
    std::cout << b << '\n';

    GrannySmith c;
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

    return 0;
}
