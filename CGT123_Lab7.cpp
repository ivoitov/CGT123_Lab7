#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;

//Written by Ivan Voitov on October 24th 2022 Last edited on October 25th 2022
int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce Lab 7");
	World world(Vector2f(0, 1));

	// Create the ball and add an impulse to it
	PhysicsCircle ball;
	ball.setCenter(Vector2f(450, 00));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);
	ball.applyImpulse(Vector2f(.55, .2));
	
	// Create the floor right wall left wall roof and center rectangle
	PhysicsRectangle floor, roof, wLeft, wRight, cRect;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);
	
	wRight.setSize(Vector2f(20, 560));
	wRight.setCenter(Vector2f(790, 300));
	wRight.setStatic(true);
	world.AddPhysicsBody(wRight);

	cRect.setSize(Vector2f(150, 100));
	cRect.setCenter(Vector2f(400, 300));
	cRect.setStatic(true);
	world.AddPhysicsBody(cRect);

	wLeft.setSize(Vector2f(20, 560));
	wLeft.setCenter(Vector2f(10, 300));
	wLeft.setStatic(true);
	world.AddPhysicsBody(wLeft);
	
	roof.setSize(Vector2f(800, 20));
	roof.setCenter(Vector2f(400, 10));
	roof.setStatic(true);
	world.AddPhysicsBody(roof);	

	// Create thud/bang counter with a lambda function for each
	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud! " << thudCount + 1 << endl;
		thudCount++;
	};
	int bangCount(0);

	//lambda function required that exits out of the program if bangcount reaches 3
	cRect.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang! " << bangCount + 1 << endl;
		bangCount++;
		if (bangCount > 2) {
			exit(0);
		}
	};

	//Creates the clock
	Clock clock;
	Time lastTime(clock.getElapsedTime());
	//runs the program to display everything
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 120, 0));
		window.draw(ball);
		window.draw(cRect);
		window.draw(floor);
		window.draw(roof);
		window.draw(wRight);
		window.draw(wLeft);
		window.display();
		}	
}