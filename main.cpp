#include"Base.h"
#include<iostream>
#include<stdlib.h>
#include<thread>
#include<chrono>
#include<SFML/Graphics.hpp>

const int HEIGHT = 50;
const int WIDTH = 50;
class snake {
	public:
	segment* head;
	segment* tail;
	direction cache;
	//Add a segment to the snake
	void append(segment *x){
		switch(tail->_cache){
			case UP: 
			x->posx = tail->posx;
			x->posy = tail->posy + 1;
			break;
		
			case DOWN:
			x->posx = tail->posx;
			x->posy = tail->posy - 1;
			break;

			case RIGHT:
			x->posx = tail->posx - 1;
			x->posy = tail->posy;
			break;

			case LEFT:
			x->posx = tail->posx + 1;
			x->posy = tail->posy;
			break;
		}
		x->previous = tail;
		tail->next = x;
		tail = x;
	}
	//Get the array of points for the current frame
	void getMap(point map[WIDTH*HEIGHT]){
		head->_cache = cache;
		segment* x = head;
		do{
		if(x->_cache == LEFT){
		if(x->posx>0){
				map[x->posx + x->posy*WIDTH]._color = WHITE;
				--x->posx;
				if(x->isHead){
					map[x->posx + x->posy*WIDTH]._color = RED;
				}
				else{
					map[x->posx + x->posy*WIDTH]._color = BLACK;
				}
		}
		else{
				map[x->posx + x->posy*WIDTH]._color = WHITE;
				x->posx = WIDTH - 1;
				if(x->isHead){
					map[x->posx + x->posy*WIDTH]._color = RED;
				}
				else{
					map[x->posx + x->posy*WIDTH]._color = BLACK;
				}
		}
		}
		else if(x->_cache == RIGHT){
		if(x->posx<WIDTH){
				map[x->posx + x->posy*WIDTH]._color = WHITE;
				++x->posx;
				if(x->isHead){
					map[x->posx + x->posy*WIDTH]._color = RED;
				}
				else{
					map[x->posx + x->posy*WIDTH]._color = BLACK;
				}
		}
	else{
				map[x->posx + x->posy*WIDTH]._color = WHITE;
				x->posx = 1;
				if(x->isHead){
					map[x->posx + x->posy*WIDTH]._color = RED;
				}
				else{
					map[x->posx + x->posy*WIDTH]._color = BLACK;
				}
		}
		}

		else if(x->_cache == UP){
		if(x->posy>0){
				map[x->posx + x->posy*WIDTH]._color = WHITE;
				--x->posy;
				if(x->isHead){
					map[x->posx + x->posy*WIDTH]._color = RED;
				}
				else{
					map[x->posx + x->posy*WIDTH]._color = BLACK;
				}
		}
	else{
				map[x->posx + x->posy*WIDTH]._color = WHITE;
				x->posy = HEIGHT - 1;
				if(x->isHead){
					map[x->posx + x->posy*WIDTH]._color = RED;
				}
				else{
					map[x->posx + x->posy*WIDTH]._color = BLACK;
				}
		}
		}

		else if(x->_cache == DOWN){
		if(x->posy<HEIGHT){
				map[x->posx + x->posy*WIDTH]._color = WHITE;
				++x->posy;
				if(x->isHead){
					map[x->posx + x->posy*WIDTH]._color = RED;
				}
				else{
					map[x->posx + x->posy*WIDTH]._color = BLACK;
				}
		}
		else{
				map[x->posx + x->posy*WIDTH]._color = WHITE;
				x->posy = 1;
				if(x->isHead){
					map[x->posx + x->posy*WIDTH]._color = RED;
				}
				else{
					map[x->posx + x->posy*WIDTH]._color = BLACK;
				}
		}
		}

	//	For debugging
	//	std::cout<<"("<<x->posx<<","<<x->posy<<")";
		if(x->next == NULL){
			break;
		}
		x = x->next;
		}
		while(true);

		x = tail;

		while(x->previous != NULL){
			x->_cache = x->previous->_cache;
			x = x->previous;
		}
	}

	~snake(){
		segment *x = head->next,*y = head->next;
		while(x != NULL){
			y = y->next;
			delete x;
			x = y;
		}
	}

	snake(segment* hd){
		head = hd;
		tail = hd;
		cache = UP;
		tail->_cache = head->_cache = cache;
	}
};

//Build Vertex array for each point in the map
void maketheQuads(sf::Vertex vertices[4], const point &map, const int &i){
	int posx = i%WIDTH;
	int posy = i/HEIGHT;
	vertices[0].position = sf::Vector2f(0 + posx*16,0 + posy*16);
	vertices[1].position = sf::Vector2f(16 + posx*16,0 + posy*16);
	vertices[2].position = sf::Vector2f(16 + posx*16,16 + posy*16);
	vertices[3].position = sf::Vector2f(0 + posx*16,16 + posy*16);
	if(map._color == WHITE){
	for(int i=0;i<4;i++){
		vertices[i].color = sf::Color::White;
		}
	}
	if(map._color == BLACK){
		for(int i=0;i<4;i++){
			vertices[i].color = sf::Color::Black;
		}
	}
	else if(map._color == RED){
		for(int i=0;i<4;i++){
			vertices[i].color = sf::Color::Red;
		}
	}
}

void initQuads(sf::Vertex vertices[WIDTH*HEIGHT][4]){
	for(int i=0;i<WIDTH*HEIGHT;i++){
		int posx = i%WIDTH;
		int posy = i/HEIGHT;
		vertices[i][0].position = sf::Vector2f(0 + posx*16,0 + posy*16);
		vertices[i][1].position = sf::Vector2f(16 + posx*16,0 + posy*16);
		vertices[i][2].position = sf::Vector2f(16 + posx*16,16 + posy*16);
		vertices[i][3].position = sf::Vector2f(0 + posx*16,16 + posy*16);
		for(int j=0;j<4;j++){
			vertices[i][j].color = sf::Color::White;
		}
	}
}

int main(){
	//For random food positions
	srand(time(NULL));

 	point map[10000];
	segment head(25,25,true,NULL,NULL,UP);
	snake _snake(&head);
	sf::Vertex vertices[WIDTH*HEIGHT][4]; 
	initQuads(vertices);
 
	//Game window
	sf::RenderWindow window(sf::VideoMode(800,800),"Game");

	//Game loop
	while(window.isOpen()){
		sf::Event event;
		std::this_thread::sleep_for(std::chrono::milliseconds(20));

		//Keyboard events
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && _snake.cache != RIGHT){
			_snake.cache = LEFT;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && _snake.cache != LEFT){
			_snake.cache = RIGHT;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && _snake.cache != DOWN){
			_snake.cache = UP;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && _snake.cache != UP){
			_snake.cache = DOWN;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
			_snake.cache = NONE;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
			segment* x = new segment(25,25,false,NULL,NULL,UP);
			_snake.append(x);
			while(true){
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
					break;
				}
			while(window.pollEvent(event)){
				if(event.type == sf::Event::Closed)
					window.close();
				}
			}
		}
	
		//map building and rendering
		_snake.getMap(map);
		for(int i=0;i<HEIGHT*WIDTH;i++){
			maketheQuads(vertices[i], map[i],i);
		        window.draw(vertices[i],4,sf::Quads);
		}

		//window events
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed)
				window.close();
		}
		window.display();
	}
	return EXIT_SUCCESS;
}
