#include "button.h"
using namespace sf;

//��������� ���������� �� ��������� ��� �������� ��������
Button::Button()
: idleColor(sf::Color::White), hoverColor(sf::Color::Blue){
    shape.setSize(sf::Vector2f(100, 50));
}

//�������� �����������
Button::Button(float x, float y, float width, float height, sf::Color idleColor, sf::Color hoverColor)
    : idleColor(idleColor), hoverColor(hoverColor), isHovered(false){

    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(idleColor);
}

//������� �������� ���������
void Button::update(const sf::Vector2f& mousePosition) {
    if (shape.getGlobalBounds().contains(mousePosition)) {
        isHovered = true;
        shape.setFillColor(hoverColor);
    }else {
        isHovered = false;
        shape.setFillColor(idleColor);
        }
}

//unhover
void Button::unhovered(){
    isHovered = false;
    shape.setFillColor(idleColor);
}

//������� �������� �������
bool Button::isClicked(const sf::Vector2f& mousePosition) {
    if (shape.getGlobalBounds().contains(mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        return true;
    }
    return false;
}

void Button::render(sf::RenderWindow& window) {
        window.draw(shape);
}








