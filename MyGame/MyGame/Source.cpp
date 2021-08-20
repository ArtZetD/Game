#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace sf;

int sum; 
const int size = 3;				// ������ �������� ����
int field[size][size];			// ������� ����


// ����� �������� ��� ������
// 0 - ������
// 1 - �������
int cross_zero = 1;


// ��������� ����
// 1 - ���� ������������
// 0 - ���� ��������
bool game_over = 1;


/* field-cords = [x][y]*/
bool tie();
void  clear();
bool check();

int main() {
	
	RenderWindow window(VideoMode(500, 500), "Tic-Tac-Toe");

	// �������� ��� �������
	Texture texture;
	texture.loadFromFile("Tic-Tac-Toe_textures.png");

	// ������
	Sprite sprite(texture);


	// ��������� ���������� �������� ����
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			field[i][j] = 0;


	// �����
	Font font;
	font.loadFromFile("arial.ttf");

	// �����
	Text text;
	text.setString("GAME OVER");
	text.setFont(font);
	text.setCharacterSize(40);
	text.setFillColor(Color::Black);
	text.setPosition(70, 400);

	Text Tiee;
	Tiee.setString("Tie");
	Tiee.setFont(font);
	Tiee.setCharacterSize(40);
	Tiee.setFillColor(Color::Black);
	Tiee.setPosition(70, 400);
	 

	// ������� ����
	while (window.isOpen()) {
		window.setTitle("TikTacToe: turn "+std::to_string(sum));
		Event event;
		window.clear(Color::White);			// �������� ������ ����


		// ���������� ��������� ����
		Vector2i pos = Mouse::getPosition(window);
		int x = pos.x / 128;
		int y = pos.y / 128;


		// ���������� �������
		while (window.pollEvent(event)) {

			// �������� ����
			if (event.type == Event::Closed) window.close();

			// ��������� ������� ����
			if (event.type == Event::MouseButtonPressed && game_over && !field[x][y]) {

				if (event.key.code == Mouse::Left) {
					if (cross_zero) {
						field[x][y] = 1;
						cross_zero = 0;
					}
					else {
						field[x][y] = 2;
						cross_zero = 1;
					}
				}

			}
			if (event.type == Event::KeyPressed) { // ������� ���� ��� ������� �� ������ 
				if (event.key.code == Keyboard::Space) clear();
			}
		}

		
		// ����������� �������� ����
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				sprite.setTextureRect(IntRect(field[i][j] * 128, 0, 128, 128)); // ����� ������� ��� �� ����� �������, �� ��� ���� 
				sprite.setPosition(i * 128, j * 128);
				window.draw(sprite);
			}
		}

		if (check()) { // ���������� � ��������� 
			window.draw(text);
			game_over = 0;
		}

		if (tie() && !check()) {
			window.draw(Tiee);
			game_over = 0;
		}
		window.display();
		
	}
}

bool check() { // ������� �������� �� ������ 
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			

			 if (field[0][0] == field[0][1] && field[0][0] == field[0][2] && field[0][0] != 0) return true;
			else if (field[1][0] == field[1][1] && field[1][0] == field[1][2] && field[1][0] != 0) return true;
			else if (field[2][0] == field[2][1] && field[2][0] == field[2][2] && field[2][0] != 0) return true;
			else if (field[0][0] == field[1][0] && field[0][0] == field[2][0] && field[0][0] != 0) return true;
			else if (field[0][1] == field[1][1] && field[0][1] == field[2][1] && field[0][1] != 0) return true;
			else if (field[0][2] == field[1][2] && field[0][2] == field[2][2] && field[0][2] != 0) return true;
			else if (field[0][0] == field[1][1] && field[0][0] == field[2][2] && field[0][0] != 0) return true;
			else if (field[0][2] == field[1][1] && field[0][2] == field[2][0] && field[0][2] != 0) return true;
			return false;
		
		}
	
	}
	 
}

bool tie() { // �������� �� ����� 
	sum = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (field[i][j] >= 1 && field[i][j]<= 2)  sum++;	
			}
		}

		if (sum == 9) {
			std::cout << sum;
			return true;
		}
		else
		{
			std::cout << sum;
			return false;
		}
}
 
void  clear() {
	// ������� ���� 
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			field[i][j] = 0;
	game_over = 1;
}
