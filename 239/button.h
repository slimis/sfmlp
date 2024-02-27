#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

// Класс кнопки
class Button {
public:
    // Конструктор по умолчанию
    Button();

    // Конструктор
    Button(float x, float y, float width, float height, sf::Color idleColor, sf::Color hoverColor);

    // проверка на наведение мыши
    void update(const sf::Vector2f& mousePosition);

    //проверка на нажатие
    bool isClicked(const sf::Vector2f& mousePosition);

    //unhover
    void unhovered();

    // Отрисовка кнопки
    void render(sf::RenderWindow& window);

private:
    // Графический объект для кнопки
    sf::RectangleShape shape;

    // Цвет в нормальном состоянии (без наведения)
    sf::Color idleColor;

    // Цвет при наведении
    sf::Color hoverColor;

    // Флаг, указывающий, наведена ли мышь на кнопку
    bool isHovered;
};







