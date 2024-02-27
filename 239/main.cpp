#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <locale>
#include<unistd.h>
#include "button.h"
#include "button2.h"

using namespace sf;
using namespace std;



int const SIZE=5;//размер доски
int board[SIZE][SIZE]={0}; // Игровая доска. 0 - пусто, 1 - крестик, 2 - нолик
int currentPlayer=1; // Игрок, который делает текущий ход (1 - крестик, 2 - нолик)
int movesCount=1; // Текущий ход
int const WIN_LENGTH=4; // Длина строки для победы
int WIN_CELLS[WIN_LENGTH][2];//Массив выйгрышных клеток
Button buttons[SIZE][SIZE];//масив кнопок(клеток)
Button2 buttons2[SIZE-1][SIZE-1];//масив кнопок(круглых)
int y;//вспомогательная переменная для перевооротов
int csena=1;//флаг для сцен
Button menug(810,450, 300,180,sf::Color::Green ,sf::Color::Blue);//главная кнопка меню
Button2 ex(1600,550, 100,sf::Color::Green ,sf::Color::Blue);//кнопка выхода из игры

//отрисовка 1 сцены(меню)
void drawBoard1(sf::RenderWindow& window, sf::Font& font, int cellSize) {
    //кнопка play
    menug.update(sf::Vector2f(sf::Mouse::getPosition(window)));
    menug.render(window);
    window.display();
}

//отрисовка 2 сцены
void drawBoard2(sf::RenderWindow& window, sf::Font& font, int cellSize) {

    //кнопка выход
    ex.update(sf::Vector2f(sf::Mouse::getPosition(window)));
    ex.render(window);

    //отрисовка клеток
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
                buttons[i][j].render(window);
                if(board[i][j]==0){
                buttons[i][j].update(sf::Vector2f(sf::Mouse::getPosition(window)));
            }
        }
    }

    //отрисовка кругов
    for (int i = 0; i < SIZE-1; ++i) {
        for (int j = 0; j < SIZE-1; ++j) {
            buttons2[i][j].render(window);
            buttons2[i][j].update(sf::Vector2f(sf::Mouse::getPosition(window)));
        }
    }

    // Отображение крестиков и ноликов на  доске
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(cellSize / 2);
    text.setFillColor(sf::Color::Black);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 1) {
                text.setString("X");
                text.setPosition(107+i * 200,70+j * 200);
                window.draw(text);
            } else if (board[i][j] == 2) {
                text.setString("O");
                text.setPosition(107+i * 200,70+j * 200);
                window.draw(text);
            }
        }
    }

    // Отрисовка счетчика ходов и индикации текущего игрока
        sf::Text text2;
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
    int cellSize = window.getSize().y / SIZE-20;

    // Инициализация клеток
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++   ) {
            buttons[i][j] = Button(50+i * 200,50+j * 200, 170,170,sf::Color::Green ,sf::Color::Blue);
        }
    }
    // Инициализация кругов
    for (int i = 0; i < SIZE-1; i++) {
        for (int j = 0; j < SIZE-1; j++   ) {
            buttons2[i][j] = Button2(220+i * 200,220+j * 200, 15,sf::Color::Green ,sf::Color::Blue);
        }
    }

    //основной игровой цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

        // закрытие окна
        if (event.type == sf::Event::Closed)
            window.close();

        //отрисовка нужного окна
        if(csena==1){
            drawBoard1(window, font, cellSize);
            window.clear(sf::Color::White);
        }
        if(csena==2){
            drawBoard2(window, font, cellSize);
            window.clear(sf::Color::White);
        }
        if(csena==3){
            drawBoard2(window, font, cellSize);
            window.clear(sf::Color::White);
        }

        if(csena==1){
            if(menug.isClicked(sf::Vector2f(sf::Mouse::getPosition(window)))){
                csena=2;
                board[SIZE][SIZE]={0};
                movesCount=1;
                currentPlayer=1;
                WIN_CELLS[WIN_LENGTH][2]={0};
                usleep(500000);
                window.clear(sf::Color::White);
            }
        }
        if(csena==2){
            if(ex.isClicked(sf::Vector2f(sf::Mouse::getPosition(window)))){
                csena=1;
                board[SIZE][SIZE]={0};
                movesCount=1;
                currentPlayer=1;
                WIN_CELLS[WIN_LENGTH][2]={0};
                usleep(500000);
                window.clear(sf::Color::White);
            }
        }

        if(csena==2){
        if((movesCount%8==7)or(movesCount%8==0)){

                //проверка кругов на нажатие
                for (int i = 0; i < SIZE-1;i++){
                    for (int j = 0; j < SIZE-1;j++){
                        if(buttons2[i][j].isClicked(sf::Vector2f(sf::Mouse::getPosition(window)))){
                        currentPlayer = 3 - currentPlayer; // Переключение между 1 и 2
                        y=board[i][j];
                        board[i][j]=board[i+1][j];
                        board[i+1][j]=board[i+1][j+1];
                        board[i+1][j+1]=board[i][j+1];
                        board[i][j+1]=y;
                        movesCount++;
                        usleep(500000);
                        }
                    }
                }

            //проверка кругов на нажатие для 2 игрока
            for (int i = 0; i < SIZE-1;i++){
                for (int j = 0; j < SIZE-1;j++){
                    if(buttons2[i][j].isClicked(sf::Vector2f(sf::Mouse::getPosition(window)))){
                        y=board[i][j];
                        board[i][j]=board[i+1][j];
                        board[i+1][j]=board[i+1][j+1];
                        board[i+1][j+1]=board[i][j+1];
                        board[i][j+1]=y;
                        currentPlayer = 3 - currentPlayer; // Переключение между 1 и 2
                        movesCount++;
                        usleep(500000);
                    }
                }
            }
        }else{

        //проверка кнопок на нажатие
            for (int i = 0; i < SIZE;i++){
                for (int j = 0; j < SIZE;j++){
                    if(buttons[i][j].isClicked(sf::Vector2f(sf::Mouse::getPosition(window)))&&board[i][j]==0){
                        board[i][j] = currentPlayer;
                        buttons[i][j].unhovered();
                        currentPlayer = 3 - currentPlayer; // Переключение между 1 и 2
                        movesCount++;
                    }
                }
            }
        }
        }

        if(csena==2){
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
                        text.setPosition(WIN_CELLS[i][1]*200+107,WIN_CELLS[i][2]*200+70);
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
                        text.setPosition(WIN_CELLS[i][1]*200+107,WIN_CELLS[i][2]*200+70);
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
                window.display();
                // Очистка экрана белым цветом
                window.clear(sf::Color::White);
                // Отрисовка доски
                drawBoard2(window, font, cellSize);
                sf::sleep(sf::seconds(3)); // Подождать 3 секунды
                csena=1;
                board[SIZE][SIZE]={0};
                movesCount=1;
                currentPlayer=1;
                WIN_CELLS[WIN_LENGTH][2]={0};
            }
        }

        if(csena==2){
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
                drawBoard2(window, font, cellSize);
                window.display();
                sf::sleep(sf::seconds(3)); // Подождать 3 секунды
                csena=1;
                board[SIZE][SIZE]={0};
                movesCount=1;
                currentPlayer=1;
                WIN_CELLS[WIN_LENGTH][2]={0};
            }
        }

    }
    }
    return 0;
}







