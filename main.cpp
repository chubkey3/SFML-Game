//simple game created using SFML
//learn more at https://github.com/chubkey3/SFML-Game


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

class Ball {
    public:
        Ball(int rad, int x, int y, int r, int g, int b);
        CircleShape C;
        void move(float x, float y);
        void update();
    private:

};

int main(){
    Ball ball(50, 100, 30, 0, 0, 250);
    
    Event event;
    
    RenderWindow window(VideoMode(800, 600), "SFML Test");
    while (window.isOpen()){
        while(window.pollEvent(event)){
            
        }
    }

	return 0;
}
