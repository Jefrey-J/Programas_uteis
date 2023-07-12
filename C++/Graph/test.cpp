/*
* Teste de interface gráfica com C++
* Comando: g++ -std=c++20 test.cpp -lsfml-graphics -lsfml-window -lsfml-system
*
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <random>
#include <list>

using namespace std; 

float randa(int xmax) {
	float r = rand();
	float x = (r/RAND_MAX)*((float) xmax);
	return x;
}


class Player {
public: 
	float x; 
	float y; 
	float vx;
	float vy; 
	float t; 
	sf::RectangleShape rectangle;
	Player(){}
	Player(float x, float y, float vx, float vy, float t, int color) {
		this->x = x; 
		this->y = y; 
		this->vx = vx; 
		this->vy = vy; 
		this->t = t; 
		sf::RectangleShape rectangle(sf::Vector2f(t, t));
		this->rectangle = rectangle; 
		rectangle.setPosition(sf::Vector2f(x, y));
		this->rectangle.setFillColor(sf::Color::Red);
		this->rectangle.setOutlineThickness(2);
    		this->rectangle.setOutlineColor(sf::Color::Black);
	}
	void setPosition(float xd, float yd) {
		x = xd;
		y = yd;
		this->rectangle.setPosition(sf::Vector2f(xd, yd));
	}
	void renderRectangle(sf::RenderWindow &window) {
		window.draw(rectangle);
	}
};

class Circle{
public: 
	float x; 
	float y;
	float vx;
	float vy;
	float r;
	float re; 
	sf::CircleShape circle;
	//sf::CircleShape edge;
	Circle(float x, float y, float vx, float vy, float r, int color) {
		this->x = x; 
		this->y = y; 
		this->vx = vx; 
		this->vy = vy; 
		this->r = r; 
		this->re = r + 2;
    		sf::CircleShape circle(r);
    		//sf::CircleShape edge(re);
    		this->circle = circle;
    		//this->edge = edge; 
		setColor(color);
	} 
	void setColor(int color) {
		switch(color) {
			case 1: 
				circle.setFillColor(sf::Color::Red);
				break;
			case 2: 
				circle.setFillColor(sf::Color::Blue);
				break;
			case 3: 
				circle.setFillColor(sf::Color::Green);
				break;
			default:
				circle.setFillColor(sf::Color::Black);
				break;
		}
		//edge.setFillColor(sf::Color::Black);
	}
	void setPosition(float x, float y) {
		this->x = x; 
		this->y = y;
		circle.setPosition(x, y);
		//edge.setPosition(x - (re-r), y - (re - r));
	}
	float getPositionX() const {
		return this->x + this->r; 
	}
	
	float getPositionY() const {
		return this->y + this->r; 
	}
	
	float getRaio() const {
		return this->r; 
	}
	
	void renderCircle(sf::RenderWindow &window) {
		x = x + vx; 
    		y = y + vy; 
    		if( x >= 520 || x <= 210) {
    			vx = -vx;
    		}
 		if( y >= 400 || y <= 0) {
    			vy = -vy;
    		}
    		setPosition(x, y);
    		//window.draw(edge);
		window.draw(circle);
	}
}; 

class Sensor {
public: 
	float ang; 
	float dist;
	float px; 
	float py; 
	sf::VertexArray line; 
	Sensor(float ang, float px, float py) {
		this->ang = ang; 
		this->px = px;
		this->py = py;
		this->dist = 1; 
		line = sf::VertexArray(sf::Lines, 2);
    		line[0].position = sf::Vector2f(this->px, this->py);
    		line[1].position = sf::Vector2f(this->px + this->dist*cos(this->ang), this->py + this->dist*sin(this->ang));

		line[0].color = sf::Color::Red;
    		line[1].color = sf::Color::Red;
	}
	void run(const sf::Image &image, const std::list<Circle> Obstacles) {
	
		sf::Color color = image.getPixel(px + dist*cos(ang), py + dist*sin(ang));
		
		line[1].position = sf::Vector2f(px + dist*cos(ang), py + dist*sin(ang));
		bool tagAux = false; 
		for(auto Obstacle = Obstacles.begin(); Obstacle != Obstacles.end(); Obstacle++) {
			float dx = Obstacle->getPositionX() - px + dist*cos(ang); 
			float dy = Obstacle->getPositionY() - py + dist*sin(ang); 
			float r = Obstacle->getRaio(); 
			float dist_ = sqrt((dx)*(dx) + (dy)*(dy)); 
			
			if(dist_ > r+10.0) {
			std::cout << "Dist:: "<< dist_ << "\n";
				tagAux = true; 
			}
		}
		
		if(!tagAux || color.r > 10 && color.g > 10 && color.b > 10) {
			dist++;
		} else {
			dist = 0;
		}
	}
	void renderLine(sf::RenderWindow &window, const sf::Image &image, const std::list<Circle> Obstacles) {
		//window.display();
		run(image, Obstacles);
 		window.draw(line);
	}
};

void Commands(Player &player, const sf::Image &image) {
	float x = player.x;
	float y = player.y; 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            sf::Color color1 = image.getPixel(x-1, y);
            sf::Color color2 = image.getPixel(x-1, y + player.t);
            if(color1.r <= 10 && color1.g <= 10 && color1.b <= 10 || color2.r <= 10 && color2.g <= 10 && color2.b <= 10) {
            } else {
            	x -= player.vx;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            sf::Color color1 = image.getPixel(x+player.t+1, y);
            sf::Color color2 = image.getPixel(x+player.t+1, y + player.t);
            if(color1.r <= 10 && color1.g <= 10 && color1.b <= 10 || color2.r <= 10 && color2.g <= 10 && color2.b <= 10) {
            } else {
            	x += player.vx;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            sf::Color color1 = image.getPixel(x, y-1);
            sf::Color color2 = image.getPixel(x + player.t, y-1);
            if(color1.r <= 10 && color1.g <= 10 && color1.b <= 10 || color2.r <= 10 && color2.g <= 10 && color2.b <= 10) {
            } else {
            	y -= player.vy;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            sf::Color color1 = image.getPixel(x, y+player.t+1);
            sf::Color color2 = image.getPixel(x + player.t, y+player.t+1);
            if(color1.r <= 10 && color1.g <= 10 && color1.b <= 10 || color2.r <= 10 && color2.g <= 10 && color2.b <= 10) {
            } else {
            	y += player.vy;
            }
        }
        player.setPosition(x, y);
}

int main()
{
    // Cria uma janela com tamanho 800x600 pixels
    const int px = 750; 
    const int py = 400;  
    int N = 20;
    std::list<Circle> C; 

    Circle c1 = Circle(210, 175, 0.5f, 0.f, 10.f, 2);
    Circle c2 = Circle(210, 240, 0.5f, 0.f, 10.f, 2);
    Circle c4 = Circle(520, 140, -0.5f, 0.f, 10.f, 2);
    Circle c3 = Circle(520, 208, -0.5f, 0.f, 10.f, 2);
    
    C.push_back(c1); 
    C.push_back(c2); 
    C.push_back(c3); 
    C.push_back(c4); 
 
    Player player = Player(100, 150, 0.4, 0.4, 20, 1);
    
    
    ////
    Sensor s1(0.78f, 210.f, 175.f); 
    ////
    sf::RenderWindow window(sf::VideoMode(px, py), "Exemplo de Grafico");
    sf::Texture texture; 
    if(!texture.loadFromFile("Fundo/fundo.png")) {
    	return -1; 
    }
    sf::Sprite sprite(texture); 
    
    sprite.setPosition(0.f, 0.f); 
    
    int pontos = 0;
    
    //............................................. 
        // cria uma fonte
    sf::Font font;
    font.loadFromFile("Fonte/arial.ttf");

    // cria um objeto Text
    sf::Text text;
    text.setFont(font);
    text.setString("Pontuacao: " + to_string(pontos));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(10,10);
    
    //............................................
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        Commands(player, texture.copyToImage());
        window.clear(sf::Color::White);
	window.draw(sprite); 
	
	auto itc = C.begin(); 
	while(itc != C.end()) {
		itc->renderCircle(window);
		itc++;
	}
	player.renderRectangle(window); 
	
	window.draw(text);
	s1.renderLine(window, texture.copyToImage(), C);
        window.display();
        
        if(player.x >= 570) {
        	pontos++;
        	text.setString("Pontuacao: " + to_string(pontos));
        	player = Player(100, 150, 0.4, 0.4, 20, 1);
        }
    }

    return 0;
}

