#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

// Класс кнопки
class Button2 {
public:
    // Конструктор по умолчанию
    Button2();

    // Конструктор
    Button2(float x, float y, float radius, sf::Color idleColor, sf::Color hoverColor);

    // Обновление состояния кнопки (наведение мыши)
    void update(const sf::Vector2f& mousePosition);

    //проверка на нажатие
    bool isClicked(const sf::Vector2f& mousePosition);

    //unhover
    void unhovered();

    // Отрисовка кнопки
    void render(sf::RenderWindow& window);

private:
    // Графический объект для кнопки
    sf::CircleShape shape;

    // Цвет в нормальном состоянии (без наведения)
    sf::Color idleColor;

    // Цвет при наведении
    sf::Color hoverColor;

    // Флаг, указывающий, наведена ли мышь на кнопку
    bool isHovered;
};







