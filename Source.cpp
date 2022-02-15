//SFML C++ Bullet Hell
// Created by Dr. Mo Jan 2022
//dynamicsofanasteroid.com

#include<iostream>
#include<vector>
#include "SFML/Graphics.hpp"
#include "globals.h" 
#include "missiles.cpp"
#include "bullet.h"
#include "stars.h"

using namespace std;

enum DIRECTIONS {LEFT, RIGHT, UP, DOWN}; //left is 0, right is 1, up is 2, down is 3
enum SHOOTIN{SPACE};
int direction = 0;

int main() {
    //game set up (you'll need these lines in every game)
    sf::RenderWindow screen(sf::VideoMode(SCREEN_H, SCREEN_W), "Bullet Hell"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    screen.setFramerateLimit(FPS); //set FPS



    //player setup------------------------------------------------
    sf::Texture ship;
    ship.loadFromFile("ship.png");
    sf::IntRect playerImg(0, 0, 30, 30); //select portion of image to draw (our ship is 30x30)
    sf::Sprite player(ship, playerImg);
    // player.setTexture(ship); //use this instead of 2 lines above for static images
    int xpos = 400;
    int ypos = 700;
    int vx = 0;
    int vy = 0;
    player.setPosition(xpos, ypos); //top left "corner" of circle (not center!)
    bool keys[] = { false, false, false, false };
    bool shoot[] = { false };
    int ticker = 0;
    int frameNum = 0;


    //bullet variables
    double minBullets = 60;
    int counter = 0;
    int moveTimer = 0;
    vector<bullet*> bullets;
    vector<bullet*> ::iterator iter3;


    //missile (the other things the player shoots) setup----------
    int justShot = 0;
    //set up variables for missile image
    sf::Texture MissileImg;
    MissileImg.loadFromFile("missile.png");
    sf::Sprite MissilePic;
    MissilePic.setTexture(MissileImg);


    vector<stars*> starfield;
    vector<stars*>::iterator iter;
    for (int i = 0; i < 200; i++) {
        stars* gameing = new stars();
        starfield.push_back(gameing);
    }

    //vector to hold missiles
    vector<missile*> missiles;
    vector<missile*> ::iterator iter2;
    for (int i = 0; i < 5; i++) {
        missile* newMissile = new missile(xpos,ypos, MissilePic);
        missiles.push_back(newMissile);
    }


    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (screen.isOpen()) {//keep window open until user shuts it down

        while (screen.pollEvent(event)) { //look for events-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed)
                screen.close();

            //KEYBOARD INPUT 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                keys[LEFT] = true;
            }
            else keys[LEFT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                keys[RIGHT] = true;
            }
            else keys[RIGHT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                keys[UP] = true;
            }
            else keys[UP] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                keys[DOWN] = true;
            }
            else keys[DOWN] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                shoot[SPACE] = true;
            }
            else shoot[SPACE] = false;



        }//end event loop---------------------------------------------------------------



        justShot++;
        if (shoot[SPACE] == true) {
            for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
                if (((*iter2)->isAlive()) == false && justShot > 5) {
                    (*iter2)->shoot(xpos, ypos);
                    justShot = 0;
                }
            }
        }

        cout << "test1" << endl;
        counter++; // variable to slow down object creation. INitialize it to 0 above your game loop.
        minBullets -= .001; //variable initialized to 60. Subtracting here speeds up object creation over time!
        cout << "test2" << endl;
        if (counter > minBullets) {
            // create new bullets, push into vector
            bullet* newbullet = new bullet(500,100,0);
            bullets.push_back(newbullet);
            bullet* newbullet2 = new bullet(500, 100, 0);
            bullets.push_back(newbullet2);
            bullet* newbullet3 = new bullet(500, 100, 0);
            bullets.push_back(newbullet3);
            bullet* newbullet4 = new bullet(500, 100, 0);
            bullets.push_back(newbullet4);
            bullet* newbullet5 = new bullet(500, 100, 0);
            bullets.push_back(newbullet5);

            counter = 0;

        }
        cout << "test3" << endl;


         //move ship
        if (keys[LEFT] == true) {
            vx = -5;
            direction = 0;
        }
        

        else if (keys[RIGHT] == true) {
            vx = 5;
            direction = 1;
        }
        else vx = 0;

        if (keys[UP] == true) {
            vy = -5;
        }

        else if (keys[DOWN] == true) {
            vy = 5;
        }
        else vy = 0;
        
        xpos += vx;
        ypos += vy;
        player.setPosition(xpos, ypos);


        

        // move missiles
        for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
            if ((*iter2)->isAlive())
                (*iter2)->move();
        }
        //cull the missiles
        for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
            if ((*iter2)->offScreen())
                (*iter2)->kill();
        }

        cout << "test4" << endl;
        //move bullets
        moveTimer += 2;
        if (moveTimer > 1800)
            moveTimer = 0;

        for (iter3 = bullets.begin(); iter3 != bullets.end(); iter3++) {
            if (moveTimer < 600) {
                (*iter3)->move();
            }
            else if (moveTimer < 1200) {
                (*iter3)->move2();
            }
            else if (moveTimer < 1800) {
                (*iter3)->move3();
            }
        }

        //cull the missiles
        cout << "test5" << endl;
        for (iter3 = bullets.begin(); iter3 != bullets.end();) {
            if ((*iter3)->offScreen()) {
                (*iter3)->~bullet();
                iter3 = bullets.erase(iter3);
            }
            else {
                ++iter3;
            }
        }

        for (iter = starfield.begin(); iter != starfield.end();) {
               (*iter)->reposition();
               (*iter)->move();
                ++iter;
       
        }



        cout << "test 5.3" << endl;


        ticker += 1;

        if (ticker % 10 == 0)
            frameNum += 1;

        if (frameNum > 4)
            frameNum = 0;
        cout << "test 5.5" << endl;

        if (direction == 1) {
            playerImg = sf::IntRect((frameNum + 5) * 32, 0, 30, 30);
        }
        else if (direction == 0) {
            playerImg = sf::IntRect((frameNum + 5) * 32, 0, -30, 30);
            std :: cout << "left" << frameNum + 5;
        }
        else {
            playerImg = sf::IntRect(frameNum * 32, 0, 30, 30);
        }


        sf::Sprite player(ship, playerImg);
        player.setPosition(xpos, ypos);

        //render section-----------------------------------------
        screen.clear(); //wipes screen, without this things smear

        
        screen.draw(player); //draw player

        for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
            (*iter2)->draw(screen);
        }
        cout << "test6" << endl;
        for (iter3 = bullets.begin(); iter3 != bullets.end(); iter3++) {
            (*iter3)->draw(screen);
        }
        for (iter = starfield.begin(); iter != starfield.end(); iter++) {
            (*iter)->draw(screen);
        }

        screen.display(); //flips memory drawings onto screen

    }//######################## end game loop ###################################################################################

    std :: cout << "goodbye!" << endl;
} //end of main