#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <locale>

using namespace std;

const int SIZE = 5;
int board[SIZE][SIZE] = {0}; // ������� �����. 0 - �����, 1 - �������, 2 - �����
int currentPlayer = 1; // �����, ������� ������ ������� ��� (1 - �������, 2 - �����)
int movesCount = 1; // ������� ���
const int WIN_LENGTH = 4; // ����� ������ ��� ������
int WIN_CELLS[WIN_LENGTH][2];

// ������� ��������� ������� �����
void drawBoard(sf::RenderWindow& window, sf::Font& font, int cellSize) {
    sf::RectangleShape line(sf::Vector2f(2, SIZE * cellSize));
    line.setFillColor(sf::Color::Black);

    // �������������� �����
    for (int i = 0; i <=SIZE; ++i) {
        line.setPosition(0, i * cellSize);
        line.setSize(sf::Vector2f(SIZE * cellSize, 30));
        window.draw(line);
    }

    // ������������ �����
    for (int i = 0; i <=SIZE; ++i) {
        line.setPosition(i * cellSize, 0);
        line.setSize(sf::Vector2f(30, SIZE * cellSize));
        window.draw(line);
    }

    // ����������� ��������� � ������� ��  �����
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(cellSize / 2); // �������� ������� ������ � ����������� �� ������� ������
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

// ��������� ����� ����
void handleClick(int x, int y, int cellSize) {
    if (board[x][y] == 0) {
        board[x][y] = currentPlayer;
        currentPlayer = 3 - currentPlayer; // ������������ ����� 1 � 2
    }
}

// ��������, ���� �� ����������
int checkWinner() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j <= SIZE - WIN_LENGTH; ++j) {

            // �������� �� �����������
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
            // �������� �� ���������
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

            // �������� �� ��������� (������ � ����)
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
            // �������� �� ��������� (����� � ����)
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

// ��������, ��������� �� �����
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
    //  ������� ����
    setlocale(LC_ALL, "Russian");

    // ������ ����
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "��������-������",sf::Style::Close);
    window.setFramerateLimit(144);

    // �������� ������ �����������
    sf::Image icon;
    if (icon.loadFromFile("icon.jpg")) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    // ���������� ������
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "������ �������� ������!" << std::endl;
        return EXIT_FAILURE;
    }

    // ������ ������ � ����������� �� ������ ����
    int cellSize = window.getSize().y / SIZE;

    //�������� ������� ����
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            // �������� ����
            if (event.type == sf::Event::Closed)
                window.close();

            // �������� �����
            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x / cellSize; // ��������� ������� � ���������� ������
                int y = event.mouseButton.y / cellSize; // ��������� ������� � ���������� ������
                // �������� �� ��,��� ������ ���,� �� ������ ����;
                if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] == 0) {
                handleClick(x, y, cellSize);
                movesCount++;
                }
            }

            // �������� �����������
        }

        // ������� ������ ����� ������
        window.clear(sf::Color::White);

        // ��������� �����
        drawBoard(window, font, cellSize);

        // ��������� �������� ����� � ��������� �������� ������
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Black);

        std::ostringstream playerTurn;
        playerTurn << "���: " << movesCount;
        text.setString(playerTurn.str());
        text.setPosition(window.getSize().x - 250, 50);
        window.draw(text);

        std::ostringstream playerType;
        playerType << "�����: " << (currentPlayer == 1 ? "�������" : "�����");
        text.setString(playerType.str());
        text.setPosition(window.getSize().x - 250, 100);
        window.draw(text);

        window.display();

        //�������� �� ������
        int winner = checkWinner();
        if (winner != 0) {
            std::ostringstream message;
            if(winner==1){
                message << "�������� ��������!";

                // ����� ������� ������ ������
                for(int i=0;i<WIN_LENGTH;i++){
                    board[WIN_CELLS[i][1]][WIN_CELLS[i][2]]=0;
                    sf::Text text;
                    text.setFont(font);
                    text.setCharacterSize(cellSize / 2); // �������� ������� ������ � ����������� �� ������� ������
                    text.setFillColor(sf::Color::Red);
                    text.setString("X");
                    text.setPosition(WIN_CELLS[i][1] * cellSize + cellSize / 4 + 20, WIN_CELLS[i][2] * cellSize + cellSize / 4 - 25);
                    window.draw(text);
                }
            }else{
                message << "������ ��������!";

                // ����� ������� ������ ������
                for(int i=0;i<WIN_LENGTH;i++){
                    board[WIN_CELLS[i][1]][WIN_CELLS[i][2]]=0;
                    sf::Text text;
                    text.setFont(font);
                    text.setCharacterSize(cellSize / 2); // �������� ������� ������ � ����������� �� ������� ������
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
            // ��������� �����
            drawBoard(window, font, cellSize);
            window.display();
            sf::sleep(sf::seconds(3)); // ��������� 3 �������
            break;
        }

        //�������� �����
        if (isBoardFull()) {
            sf::Text drawText;
            drawText.setFont(font);
            drawText.setCharacterSize(50);
            drawText.setFillColor(sf::Color::Black);
            drawText.setString("�����!");
            drawText.setPosition(1450,950);
            window.draw(drawText);
            // ��������� �����
            drawBoard(window, font, cellSize);
            window.display();
            sf::sleep(sf::seconds(3)); // ��������� 3 �������
            break;
        }
    }

    return 0;
}









