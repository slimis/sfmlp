#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

// ����� ������
class Button {
public:
    // ����������� �� ���������
    Button();

    // �����������
    Button(float x, float y, float width, float height, sf::Color idleColor, sf::Color hoverColor);

    // �������� �� ��������� ����
    void update(const sf::Vector2f& mousePosition);

    //�������� �� �������
    bool isClicked(const sf::Vector2f& mousePosition);

    //unhover
    void unhovered();

    // ��������� ������
    void render(sf::RenderWindow& window);

private:
    // ����������� ������ ��� ������
    sf::RectangleShape shape;

    // ���� � ���������� ��������� (��� ���������)
    sf::Color idleColor;

    // ���� ��� ���������
    sf::Color hoverColor;

    // ����, �����������, �������� �� ���� �� ������
    bool isHovered;
};







