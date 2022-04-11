#pragma once
#include "SFML/Graphics.hpp"
#include "Manager.h"



class LevelTimer {
public:
	static LevelTimer& instance();
	~LevelTimer() {};
	void initTimer();
	void refreshTime();
	const bool isTimerOver()const { return m_duration.asSeconds() <= 0.f; }
	void setTime(const sf::Time& gameTime);
	void setColor() { m_timerText.setFillColor(sf::Color::Black); }
	void setDuration(const sf::Time& gameTime) { m_duration = gameTime; }
	void updateDuration(const sf::Time& factor);
	void updateTimer(const sf::Time& deltaTime);
	void draw(sf::RenderWindow& window)const;
private:
	LevelTimer();
	LevelTimer(const LevelTimer&) = delete;
	LevelTimer& operator=(const LevelTimer&) = delete;
	sf::Text m_timerText;
	sf::Time m_time;
	sf::Time m_duration;
};