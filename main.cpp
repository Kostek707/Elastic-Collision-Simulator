#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <math.h>

const int WIDTH = 2400;
const int HEIGHT = 1300;
const int numberOfBalls = 15;
const double speed = 0.125;
sf::CircleShape ball[numberOfBalls];
int collision[numberOfBalls][numberOfBalls];
bool move;
int moveValue = -1;
int radius[numberOfBalls];
double mass[numberOfBalls];

double sqr(double x){
  return x*x;
}

double massCount(int radius){
  return sqr(radius)*M_PI;
}

int main(){
  srand(time(NULL));
  sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"Collisions",sf::Style::Titlebar | sf::Style::Close);
  for(int i = 0; i < numberOfBalls; i++){
    radius[i]=rand()%80+20;
    mass[i]=massCount(radius[i]);
    ball[i].setRadius(radius[i]);
    ball[i].setFillColor(sf::Color(rand()%255+1,rand()%255+1,rand()%255+1,255));
    ball[i].setPosition((rand()%(WIDTH-2*radius[i])),(rand()%(HEIGHT-2*radius[i])));
    for(int j = 0; j<numberOfBalls; j++){
      if(i!=j){
        sf::Vector2f ballCenter1(ball[i].getPosition().x+radius[i],ball[i].getPosition().y+radius[i]);
        sf::Vector2f ballCenter2(ball[j].getPosition().x+radius[j],ball[j].getPosition().y+radius[j]);
        if(sqr(ballCenter1.x-ballCenter2.x)+sqr(ballCenter1.y-ballCenter2.y)<=sqr(radius[i]+radius[j])){
          ball[i].setPosition((rand()%(WIDTH-2*radius[i])),(rand()%(HEIGHT-2*radius[i])));
          j=0;
        }
      }
    }
  }
  window.setFramerateLimit(100);
  sf::Clock clock;
  sf::Vector2f v1[numberOfBalls];
  sf::Vector2i pre;

  for(int i = 0; i<numberOfBalls; i++){
    v1[i].x=0.0f;
    v1[i].y=0.0f;
  }

  while(window.isOpen()){
    sf::Time time = clock.restart();
    int sec = time.asMilliseconds();
    sf::Event evnt;
    while (window.pollEvent(evnt))
    {
        switch (evnt.type) {
          case sf::Event::Closed:
            window.close();
            break;
        }
    }
    sf::Vector2i mv = sf::Mouse::getPosition(window);
    bool pressed = false;
    for(int i=0; i<numberOfBalls; i++){
      sf::Vector2f v = ball[i].getPosition();
      if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        pressed=true;
      }
      if(moveValue==-1||moveValue==i){
        if(pressed&&!move){;
          if(mv.x>=v.x&&mv.x<=v.x+radius[i]*2&&mv.y>=v.y&&mv.y<=v.y+radius[i]*2){
            move = true;
            moveValue=i;
          }
        }

        if(move&&pressed){;
          v1[i].x=mv.x-pre.x;
          v1[i].y=mv.y-pre.y;

        }
        if(!pressed&&move){
          if(move==true){
            v1[i].y*=0.8f;
            v1[i].x*=0.8f;
            move=false;
            moveValue=-1;
          }
        }
      }
      if(v.x+v1[i].x>WIDTH-2*radius[i]){
        v1[i].x*=-1*0.9;
      }
      if(v.y+v1[i].y>HEIGHT-2*radius[i]){
        v1[i].y*=-1*0.9;
      }
      if(v.x+v1[i].x<0){
        v1[i].x*=-1*0.9;
      }
      if(v.y+v1[i].y<0){
        v1[i].y*=-1*0.9;
      }
      for(int j = 0; j<numberOfBalls; j++){
        if(j!=i&&collision[i][j]==0){
          sf::Vector2f ballCenter1(v.x+radius[i],v.y+radius[i]);
          sf::Vector2f ballCenter2(ball[j].getPosition().x+radius[j],ball[j].getPosition().y+radius[j]);
          if(sqr(ballCenter1.x-ballCenter2.x)+sqr(ballCenter1.y-ballCenter2.y)<=sqr(radius[i]+radius[j])){
            collision[i][j]=8;
            collision[j][i]=8;
            sf::Vector2f ob1 (v1[i]);
            sf::Vector2f ob2 (v1[j]);
            v1[i].x = (ob1.x * (mass[i]-mass[j]) + (2 * mass[j] * ob2.x)) / (mass[i] + mass[j]);
            v1[i].y = (ob1.y * (mass[i]-mass[j]) + (2 * mass[j] * ob2.y)) / (mass[i] + mass[j]);
            v1[j].x = (ob2.x * (mass[j]-mass[i]) + (2 * mass[i] * ob1.x)) / (mass[i] + mass[j]);
            v1[j].y = (ob2.y* (mass[j]-mass[i]) + (2 * mass[i] * ob1.y)) / (mass[i] + mass[j]);
          }
        }

      }
    }
    for(int i = 0; i<numberOfBalls; i++){
      for(int j = 0; j<numberOfBalls; j++){
        if(collision[i][j]>0){
          collision[i][j]--;
        }
      }
    }

    pre = mv;
    window.clear();
    for(int i = 0; i < numberOfBalls; i++){
      window.draw(ball[i]);
      if(move&&moveValue==1){
        ball[i].move(v1[i]);
      }
      else{
        ball[i].move(v1[i].x*sec*speed,v1[i].y*speed*sec);
      }

      }

    window.display();
  }

}
