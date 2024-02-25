#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <locale>

using namespace std;

const int SIZE = 5;
int board[SIZE][SIZE] = {0}; // Игровая доска. 0 - пусто, 1 - крестик, 2 - нолик
int currentPlayer = 1; // Игрок, который делает текущий ход (1 - крестик, 2 - нолик)
int movesCount = 1; // Текущий ход
const int WIN_LENGTH = 4; // Длина строки для победы
int WIN_CELLS[WIN_LENGTH][2];

// Функция отрисовки игровой доски
void drawBoard(sf::RenderWindow& window, sf::Font& font, int cellSize) {
    sf::RectangleShape line(sf::Vector2f(2, SIZE * cellSize));
    line.setFillColor(sf::Color::Black);

    // Горизонтальные линии
    for (int i = 0; i <=SIZE; ++i) {
        line.setPosition(0, i * cellSize);
        line.setSize(sf::Vector2f(SIZE * cellSize, 30));
        window.draw(line);
    }

    // Вертикальные линии
    for (int i = 0; i <=SIZE; ++i) {
        line.setPosition(i * cellSize, 0);
        line.setSize(sf::Vector2f(30, SIZE * cellSize));
        window.draw(line);
    }

    // Отображение крестиков и ноликов на  доске
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(cellSize / 2); // Изменено размера шрифта в зависимости от размера клетки
    text.setFillColor(sf::Color::Black);

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 1) {
                text.setString("X");
                text.setPosition(i * cellSize + cellSize / 4 + 20, j * cellSize + cellSize / 4 - 25);
                window.draw(text);
            } else if (board[i][j] == 2) {
                text.setString("O");
                text.setPosition(i * cellSize + cellSize / 4 + 20, j * cellSize + cellSize / 4 - 25);
                window.draw(text);
            }
        }
    }
}

// Обработка клика мыши
void handleClick(int x, int y, int cellSize) {
    if (board[x][y] == 0) {
        board[x][y] = currentPlayer;
        currentPlayer = 3 - currentPlayer; // Переключение между 1 и 2
    }
}

// Проверка, есть ли победитель
int checkWinner() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j <= SIZE - WIN_LENGTH; ++j) {

            // Проверка по горизонтали
            int countX = 0;
            int countO = 0;
            for (int k = 0; k < WIN_LENGTH; ++k) {
                if (board[i][j + k] == 1) {
                    countX++;
                } else if (board[i][j + k] == 2) {
                    countO++;
                }
            }
            if (countX == WIN_LENGTH){
                for(int h=0;h<WIN_LENGTH;h++){
                     WIN_CELLS[h][1]=i;
                     WIN_CELLS[h][2]=j+h;
                }
                return 1;
            }
            if (countO == WIN_LENGTH){
                for(int h=0;h<WIN_LENGTH;h++){
                    WIN_CELLS[h][1]=i;
                    WIN_CELLS[h][2]=j+h;
                }
            return 2;
            }
            // Проверка по вертикали
            countX = 0;
            countO = 0;
            for (int k = 0; k < WIN_LENGTH; ++k) {
                if (board[j + k][i] == 1) {
                    countX++;
                } else if (board[j + k][i] == 2) {
                    countO++;
                }
            }
            if (countX == WIN_LENGTH){
                for(int h=0;h<WIN_LENGTH;h++){
                    WIN_CELLS[h][1]=j+h;
                    WIN_CELLS[h][2]=i;
                }
            return 1;
            }
            if (countO == WIN_LENGTH){
                for(int h=0;h<WIN_LENGTH;h++){
                    WIN_CELLS[h][1]=j+h;
                    WIN_CELLS[h][2]=i;
                }
                return 2;
            }
        }
    }

    for (int i = 0; i <= SIZE - WIN_LENGTH; ++i) {
        for (int j = 0; j <= SIZE - WIN_LENGTH; ++j) {

            // Проверка по диагонали (вправо и вниз)
            int countX = 0;
            int countO = 0;
            for (int k = 0; k < WIN_LENGTH; ++k) {
                if (board[i + k][j + k] == 1) {
                    countX++;
                } else if (board[i + k][j + k] == 2) {
                    countO++;
                }
            }
            if (countX == WIN_LENGTH){
                for(int h=0;h<WIN_LENGTH;h++){
                    WIN_CELLS[h][1]=j+h;
                    WIN_CELLS[h][2]=i+h;
                }
                return 1;
            }
            if (countO == WIN_LENGTH){
                for(int h=0;h<WIN_LENGTH;h++){
                    WIN_CELLS[h][1]=j+h;
                    WIN_CELLS[h][2]=i+h;
                }
                return 2;
            }
            // Проверка по диагонали (влево и вниз)
            countX = 0;
            countO = 0;
            for (int k = 0; k < WIN_LENGTH; ++k) {
                if (board[i + k][j + WIN_LENGTH - 1 - k] == 1) {
                    countX++;
                } else if (board[i + k][j + WIN_LENGTH - 1 - k] == 2) {
                    countO++;
                }
            }
            if (countX == WIN_LENGTH){
                for(int h=0;h<WIN_LENGTH;h++){
                    WIN_CELLS[h][1]=i+h;
                    WIN_CELLS[h][2]=j + WIN_LENGTH - 1 - h;
                }
                return 1;
            }
            if (countO == WIN_LENGTH) {
                for(int h=0;h<WIN_LENGTH;h++){
                    WIN_CELLS[h][1]=i+h;
                    WIN_CELLS[h][2]=j + WIN_LENGTH - 1 - h;
                }
                return 2;
            }
        }
    }

    return 0;
}

// Проверка, заполнена ли доска
bool isBoardFull() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0)
                return false;
        }
    }
    return true;
}

int main() {
    //  Русский язык
    setlocale(LC_ALL, "Russian");

    // Рендер окна
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Крестики-нолики",sf::Style::Close);
    window.setFramerateLimit(144);

    // Загрузка иконки изображения
    sf::Image icon;
    if (icon.loadFromFile("icon.jpg")) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    // Объявление шрифта
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Ошибка загрузки шрифта!" << std::endl;
        return EXIT_FAILURE;
    }

    // Размер клетки в зависимости от высоты окна
    int cellSize = window.getSize().y / SIZE;

    //основной игровой цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            // закрытие окна
            if (event.type == sf::Event::Closed)
                window.close();

            // действия мышью
            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x / cellSize; // Переводим пиксели в координаты клетки
                int y = event.mouseButton.y / cellSize; // Переводим пиксели в координаты клетки
                // Проверка на то,что сделан ход,а не просто клик;
                if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] == 0) {
                handleClick(x, y, cellSize);
                movesCount++;
                }
            }

            // действия клавиатурой
        }

        // Очистка экрана белым цветом
        window.clear(sf::Color::White);

        // Отрисовка доски
        drawBoard(window, font, cellSize);

        // Отрисовка счетчика ходов и индикации текущего игрока
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Black);

        std::ostringstream playerTurn;
        playerTurn << "Ход: " << movesCount;
        text.setString(playerTurn.str());
        text.setPosition(window.getSize().x - 250, 50);
        window.draw(text);

        std::ostringstream playerType;
        playerType << "Игрок: " << (currentPlayer == 1 ? "Крестик" : "Нолик");
        text.setString(playerType.str());
        text.setPosition(window.getSize().x - 250, 100);
        window.draw(text);

        window.display();

        //проверка на победу
        int winner = checkWinner();
        if (winner != 0) {
            std::ostringstream message;
            if(winner==1){
                message << "крестики победили!";

                // вывод красных знаков поверх
                for(int i=0;i<WIN_LENGTH;i++){
                    board[WIN_CELLS[i][1]][WIN_CELLS[i][2]]=0;
                    sf::Text text;
                    text.setFont(font);
                    text.setCharacterSize(cellSize / 2); // Изменено размера шрифта в зависимости от размера клетки
                    text.setFillColor(sf::Color::Red);
                    text.setString("X");
                    text.setPosition(WIN_CELLS[i][1] * cellSize + cellSize / 4 + 20, WIN_CELLS[i][2] * cellSize + cellSize / 4 - 25);
                    window.draw(text);
                }
            }else{
                message << "нолики победили!";

                // вывод красных знаков поверх
                for(int i=0;i<WIN_LENGTH;i++){
                    board[WIN_CELLS[i][1]][WIN_CELLS[i][2]]=0;
                    sf::Text text;
                    text.setFont(font);
                    text.setCharacterSize(cellSize / 2); // Изменено размера шрифта в зависимости от размера клетки
                    text.setFillColor(sf::Color::Red);
                    text.setString("O");
                    text.setPosition(WIN_CELLS[i][1] * cellSize + cellSize / 4 + 20, WIN_CELLS[i][2] * cellSize + cellSize / 4 - 25);
                    window.draw(text);
                }
            }
            sf::Text winText;
            winText.setFont(font);
            winText.setCharacterSize(50);
            winText.setFillColor(sf::Color::Black);
            winText.setString(message.str());
            winText.setPosition(1450,950);
            window.draw(winText);
            // Отрисовка доски
            drawBoard(window, font, cellSize);
            window.display();
            sf::sleep(sf::seconds(3)); // Подождать 3 секунды
            break;
        }

        //проверка ньчьи
        if (isBoardFull()) {
            sf::Text drawText;
            drawText.setFont(font);
            drawText.setCharacterSize(50);
            drawText.setFillColor(sf::Color::Black);
            drawText.setString("Ничья!");
            drawText.setPosition(1450,950);
            window.draw(drawText);
            // Отрисовка доски
            drawBoard(window, font, cellSize);
            window.display();
            sf::sleep(sf::seconds(3)); // Подождать 3 секунды
            break;
        }
    }

    return 0;
}









