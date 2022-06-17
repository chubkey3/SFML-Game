#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Ball {

    public:

		Ball(int rad, int x, int y, int r, int g, int b);
		//sf::CircleShape C;	//must be public so we can draw it	
        int xpos;
        int ypos;
        uint width;
        uint height;
		void move(float x, float y);
		void update(int w, int h);
        sf::Sprite sprite;
        
    
    private:
        sf::Texture texture;
        
	
};

int main()
{
    
    Ball ball(50, 100, 30, 250, 0, 0);

	sf::Event event;
    sf::RenderWindow window(sf::VideoMode(), "SFML Window", sf::Style::Fullscreen);
    //sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    sf::Vector2u size = window.getSize();
    
    int width = size.x;
    int height = size.y;
    
    std::cout << size.x << " " << size.y << std::endl;
    
    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                window.close();
                break;

                default:
                break;
            }

        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
        
        ball.update(width, height);
        window.clear(sf::Color::Black);
        window.draw(ball.sprite);
        window.display();
    }
    return 0;

}


Ball::Ball(int rad, int x, int y, int r, int g, int b)
{
    /*
    C.setRadius(rad);
    C.setFillColor(sf::Color(r,g,b));
    C.setPosition(x,y);
    */
    xpos = x;
    ypos = y;
    
    
    
    texture.loadFromFile("ufo.png");
    sprite.setTexture(texture);
    
    width = 50; //change
    height = 50; //change
}


void Ball::move(float x, float y)
{
	sprite.move(x,y);
}

void Ball::update(int w, int h){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
        if (xpos == 0-width){
            xpos = w;
            sprite.setPosition(w, ypos);
        } else {
            sprite.move(-1,0);
            xpos -= 1;
        }
        
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
        if (xpos == w+width){
            xpos = 0;
            sprite.setPosition(0, ypos);
        } else {
            sprite.move(1,0);
            xpos += 1;
        }
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
        if (ypos == h+height){
            ypos = 0;
            sprite.setPosition(xpos, 0);
        } else {
            sprite.move(0,1);
            ypos += 1;
        }
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
        if (ypos == 0-width){
            ypos = h;
            sprite.setPosition(xpos, h);
        } else {
            sprite.move(0,-1);
            ypos -= 1;
        }
	}
}
