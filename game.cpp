#include "game.hpp"
#include <iostream>
using namespace std;

const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() {
	m_mainWindow.create(sf::VideoMode(750, 500, 32), "Soccer2d");
	m_ball.setRadius(40.f);
	m_ball.setPosition(200.f, 200.f);
	m_ball.setFillColor(sf::Color::White);
	
	m_player.setRadius(50.f);
	m_player.setPosition(500.f, 400.f);
	m_player.setFillColor(sf::Color::Cyan);
	
	is_moving_up = false;
	is_moving_down = false;
	is_moving_left = false;
	is_moving_right = false;
}

void Game::run() {	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while (m_mainWindow.isOpen()) {
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents() {
	sf::Event event;

	while (m_mainWindow.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::KeyPressed:
				//cout << "Key pressed" << endl;
				handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				//cout << "Key released" << endl;
				handlePlayerInput(event.key.code, false);
				break;
			case sf::Event::Closed:
				m_mainWindow.close();
				break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool is_pressed) {
	if (key == sf::Keyboard::W)
		is_moving_up = is_pressed;
	else if (key == sf::Keyboard::S)
		is_moving_down = is_pressed;
	else if (key == sf::Keyboard::A)
		is_moving_left = is_pressed;
	else if (key == sf::Keyboard::D)
		is_moving_right = is_pressed;
		
	/*cout << endl << "directions are now: " << endl;
	cout << "Up: " << is_moving_up << endl;
	cout << "Down: " << is_moving_down << endl;
	cout << "Left: " << is_moving_left << endl;
	cout << "Right: " << is_moving_right << endl;*/
}

void Game::update(sf::Time deltaTime) {
	sf::Vector2f player_movement(0.f, 0.f);
	
	if (is_moving_up)
		player_movement.y -= PlayerSpeed;
	if (is_moving_down)
		player_movement.y += PlayerSpeed;
	if (is_moving_left)
		player_movement.x -= PlayerSpeed;
	if (is_moving_right)
		player_movement.x += PlayerSpeed;
		
	m_player.move(player_movement * deltaTime.asSeconds());
}

void Game::render() {
	m_mainWindow.clear();
	m_mainWindow.draw(m_ball);
	m_mainWindow.draw(m_player);
	m_mainWindow.display();
}

