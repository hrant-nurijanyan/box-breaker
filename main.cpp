#include <iostream>

#include <entt/entt.hpp>

struct A
{
    virtual void f() const = 0;

    virtual ~A() = default;
};

struct B : A
{
    void f() const final
    {
        std::cout << "B::f()" << std::endl;
    }

};

struct C : A
{
    void f() const final
    {
        std::cout << "C::f()" << std::endl;
    }

};

int main()
{

}
