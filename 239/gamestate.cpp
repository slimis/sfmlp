#include <SFML/Graphics.hpp>
#include <iostream>

// Базовый класс для всех состояний игры
class GameState {
public:
    virtual ~GameState() = default;

    // Метод обновления состояния
    virtual void update() = 0;

    // Метод отрисовки состояния
    virtual void render(sf::RenderWindow& window) = 0;
};

// Класс состояния "Меню"
class MenuState : public GameState {
public:

    void update() override {
        // Логика обновления для состояния меню
    }

    void render(sf::RenderWindow& window) override {
        // Отрисовка элементов меню
        window.clear(sf::Color::Green);
        // ... отрисовка кнопок, текста и т.д.
        window.display();
    }
};

// Класс состояния "Другое состояние"
class OtherState : public GameState {
public:

    void update() override {
        // Логика обновления для другого состояния
    }

    void render(sf::RenderWindow& window) override {
        // Отрисовка элементов другого состояния
        window.clear(sf::Color::Blue);
        // ... отрисовка других элементов, фона и т.д.
        window.display();
    }
};

