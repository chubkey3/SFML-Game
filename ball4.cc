#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>

using namespace sf;

int randint(float min, float max){

    return int(min+(max * rand()/(RAND_MAX+1.0)));
}

class Ball {

    public:

		Ball(const RenderWindow& W, int rad, int x, int y, int r, int g, int b);
		void move(float x, float y);
		void update();
        Vector2f pos;		   
		float rad;
		Sprite sprite; //must be public so we can draw it	
	
	private:
		RenderWindow* W;
		
		float winwidth; //assigned in ctor method below
		float winheight ;
		//float winwidth( window.getSize().x); //fails as no window object in Ball class
		//float winheight( window.getSize().y);
		Texture texture; //static so we don't have a texture for each instance
		//bool collided;
		
		
};

class Meteor {
    
    public:
        Meteor(const RenderWindow& W, float min, float max);
        void update();
        void collide();
        Vector2f pos; //initially private
        float rad = 50; //initially private
        Sprite sprite;
        bool collision = false;
    private:
        float vx;
        float vy;
        		   
		
		float winwidth; //assigned in ctor method below
		float winheight ;
        Texture texture;
        

};


void collisiondetect(std::vector<Meteor*> &m, Ball &b, RenderWindow& w, std::clock_t &c){
    for (uint i = 0; i<m.size(); i++){
        //meteor & meteor collision
        for (uint k = 0; k<m.size(); k++){
            if (i != k){
                
                if (pow(pow(m[i]->pos.x - m[k]->pos.x, 2) + pow(m[i]->pos.y - m[k]->pos.y, 2), 0.5) < (m[i]->rad + m[k]->rad)){
                    //m[i]->collision = true;
                    //m[k]->collision = true;
                    //m[i]->collide();
                    //m[k]->collide();
                    
                }
                
            }
        }
        
        if (pow(pow(m[i]->pos.x - b.pos.x, 2) + pow(m[i]->pos.y - b.pos.y, 2), 0.5) < (m[i]->rad + b.rad) && !m[i]->collision){
        
            //if (m[i]-> collision == true || lose){
            
            m[i]->collision = true;
            
            
            bool lose = true;
            
            for (uint i = 0; i<m.size(); i++){
                if (!m[i]->collision){
                    lose = false;
                }
            }
            
            if (lose){
                std::cout << "You Lose!" << std::endl;
                /*
                double duration;
                duration = ( std::clock() - c )
                duration = duration / (double)CLOCKS_PER_SEC;

                std::cout << "Time: " << duration << std::endl;
                */
                w.close();
            }
        }
    }
    
}

int main()
{
    //Ball ball(50, 100, 30, 250, 0, 0);

	Event event;
    RenderWindow window(VideoMode(800,600), "SFML Test");
//    RenderWindow window(VideoMode(), "Meteor Game", Style::Fullscreen);
    Ball ball(window, 50, 100, 30, 250, 0, 0);
    
    std::vector<Meteor*> meteors;
    
    uint meteorcount = 5;
    
    Meteor* temp;
    
    std::clock_t start = std::clock();
    
    for (uint i = 0; i<meteorcount; i++){
        temp = new Meteor(window, 8.0, 16.0);
        meteors.push_back(temp);
    }
    
    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case Event::Closed:
                for (uint i = 0; i<meteorcount; i++){
                    delete meteors[i];
                }

                window.close();
                break;

                default:
                break;
            }

        }

        ball.update();
        collisiondetect(meteors, ball, window, start);
        for (uint i = 0; i<meteorcount; i++){
            if (!meteors[i]->collision){
                meteors[i]->update();
            }
        }
        
		window.setFramerateLimit(60);
        window.clear(Color::White);
        window.draw(ball.sprite);
        for (uint i = 0; i<meteorcount; i++){
            if (!meteors[i]->collision){
                window.draw(meteors[i]->sprite);
            }
        }
        window.display();
    }
    return 0;

}




Ball::Ball(const RenderWindow& W, int rad, int x, int y, int r, int g, int b)
{
	//W.setTitle("aoiresntoiaen"); //fails cause W is passed as const ref
	//W.setSize(Vector2u(500.,500.));
	winheight= W.getSize().y;
	winwidth= W.getSize().x;
    //texture.loadFromFile("meteor-small.png");
    texture.loadFromFile("ufo.png");
    Vector2u v= texture.getSize();
    float xs= 100./v.x; //make sprite 100 pixels wide and high
    float ys= 100./v.y;
    sprite.setTexture(texture);
    sprite.setOrigin(v.x/2,v.y/2); 
    // must setOrigin to center *before* scaling 
    sprite.setScale(xs,ys);
	sprite.setPosition(x,y);
    rad = rad;
	//collided = false;
    
    
}

Meteor::Meteor(const RenderWindow &W, float min, float max) {
    vx = randint(min, max);
    vy = randint(min, max);
    
    winheight= W.getSize().y;
	winwidth= W.getSize().x;
    
    texture.loadFromFile("meteor3.png");
    Vector2u v= texture.getSize();
    float xs= 100./v.x; //make sprite 100 pixels wide and high
    float ys= 100./v.y;
    sprite.setTexture(texture);
    sprite.setOrigin(v.x/2,v.y/2); 
    // must setOrigin to center *before* scaling 
    sprite.setScale(xs,ys);
	sprite.setPosition(randint(0, winwidth), randint(0, winheight));
	//collided = false;
}


void Ball::move(float x, float y)
{
	sprite.move(x,y);
}

void Ball::update(){
	
	if(Keyboard::isKeyPressed(Keyboard::Left))
	{
		sprite.move(-10,0.);
	}
	if(Keyboard::isKeyPressed(Keyboard::Right))
	{
		sprite.move(10,0);
	}
	if(Keyboard::isKeyPressed(Keyboard::Down))
	{
		sprite.move(0,10);
	}
	if(Keyboard::isKeyPressed(Keyboard::Up))
	{
		sprite.move(0,-10);
	}
	
	pos = sprite.getPosition();
	float rad = 50.;
		
	if ( pos.x - rad > winwidth) //beyond right side
    {   
        pos.x = 0;
    }   
    if ( pos.y - rad > winheight) //beyond bottom
    {   
        pos.y = 0;
    }   
    
    if( pos.x + rad < 0) //beyond left side
    {   
        pos.x = winwidth;
    }   
    if( pos.y + rad < 0) //beyond top
    {   
        pos.y = winheight;
    }   
	sprite.setPosition(pos.x, pos.y);
}

void Meteor::collide(){
    vx = -vx;
    vy = -vy;
}

void Meteor::update(){
    
    pos = sprite.getPosition();
    
    
    if ( pos.x > winwidth) //beyond right side
    {   
        //pos.x = 0;
        vx = -vx;
    }   
    if ( pos.y > winheight) //beyond bottom
    {   
        //pos.y = 0;
        vy = -vy;
    }   
    
    if( pos.x < 0) //beyond left side
    {   
        //pos.x = winwidth;
        vx = -vx;
    }   
    if( pos.y < 0) //beyond top
    {   
        //pos.y = winheight;
        vy = -vy;
    }   
	
    sprite.setPosition(pos.x+vx, pos.y+vy);
	sprite.rotate(6);
}
