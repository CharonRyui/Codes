#include <iostream>
#include <string_view>

class Ball 
{
    std::string_view m_color;
    double m_radius;

public:
    Ball(std::string_view color, double radius)
    : m_color{color}
    , m_radius{radius} {
    }
    
    const std::string_view& getColor() const {return m_color;}
    void setColor(std::string_view& color) {m_color = color;}
    const double getRadius() const {return m_radius;}
    void setRadius(double radius) {m_radius = radius;}
};

void print(Ball& ball) {
    std::cout << "Ball(" << ball.getColor() << ", " << ball.getRadius() << ")" << std::endl;
}

int main() {
    Ball blue = Ball("blue", 10.0);
    print(blue);
    Ball red = Ball("red", 15.4);
    print(red);
    return 0;
} 