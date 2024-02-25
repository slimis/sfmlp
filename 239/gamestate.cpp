#include <SFML/Graphics.hpp>
#include <iostream>

// ������� ����� ��� ���� ��������� ����
class GameState {
public:
    virtual ~GameState() = default;

    // ����� ���������� ���������
    virtual void update() = 0;

    // ����� ��������� ���������
    virtual void render(sf::RenderWindow& window) = 0;
};

// ����� ��������� "����"
class MenuState : public GameState {
public:

    void update() override {
        // ������ ���������� ��� ��������� ����
    }

    void render(sf::RenderWindow& window) override {
        // ��������� ��������� ����
        window.clear(sf::Color::Green);
        // ... ��������� ������, ������ � �.�.
        window.display();
    }
};

// ����� ��������� "������ ���������"
class OtherState : public GameState {
public:

    void update() override {
        // ������ ���������� ��� ������� ���������
    }

    void render(sf::RenderWindow& window) override {
        // ��������� ��������� ������� ���������
        window.clear(sf::Color::Blue);
        // ... ��������� ������ ���������, ���� � �.�.
        window.display();
    }
};

