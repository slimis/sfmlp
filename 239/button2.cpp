#include "button2.h"
using namespace sf;

//��������� ���������� �� ��������� ��� �������� ��������
Button2::Button2()
: idleColor(sf::Color::White), hoverColor(sf::Color::Blue){
    shape.setRadius(50);
}

//�������� �����������
Button2::Button2(float x, float y, float radius, sf::Color idleColor, sf::Color hoverColor)
    : idleColor(idleColor), hoverColor(hoverColor), isHovered(false){
    shape.setRadius(radius);
    shape.setPosition(x, y);
    shape.setFillColor(idleColor);
}

//������� �������� ���������
void Button2::update(const sf::Vector2f& mousePosition) {
    if (shape.getGlobalBounds().contains(mousePosition)) {
        isHovered = true;
        shape.setFillColor(hoverColor);
    }else {
        isHovered = false;
        shape.setFillColor(idleColor);
        }
}

//������� �������� �������
bool Button2::isClicked(const sf::Vector2f& mousePosition) {
    if (shape.getGlobalBounds().contains(mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        return true;
    }
    return false;
}

//unhover
void Button2::unhovered(){
    isHovered = false;
    shape.setFillColor(idleColor);
}

//����� �������
void Button2::render(sf::RenderWindow& window) {
        window.draw(shape);
}







