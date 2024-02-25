#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

// ����� ������
class Button2 {
public:
    // ����������� �� ���������
    Button2();

    // �����������
    Button2(float x, float y, float radius, sf::Color idleColor, sf::Color hoverColor);

    // ���������� ��������� ������ (��������� ����)
    void update(const sf::Vector2f& mousePosition);

    //�������� �� �������
    bool isClicked(const sf::Vector2f& mousePosition);

    //unhover
    void unhovered();

    // ��������� ������
    void render(sf::RenderWindow& window);

private:
    // ����������� ������ ��� ������
    sf::CircleShape shape;

    // ���� � ���������� ��������� (��� ���������)
    sf::Color idleColor;

    // ���� ��� ���������
    sf::Color hoverColor;

    // ����, �����������, �������� �� ���� �� ������
    bool isHovered;
};







