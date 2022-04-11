#include "LevelTimer.h"


//------------------------------------------------------------------------------------------------

LevelTimer::LevelTimer()
{
	initTimer();
}
//------------------------------------------------------------------------------------------------
//this func initializes the timer text
void LevelTimer::initTimer()
{
	m_timerText.setFont(Manager::instance().getFont(Fonts::some_font));
	m_timerText.setString("00:000");
	m_timerText.setCharacterSize(35);
	m_timerText.setFillColor(sf::Color::Black);
	m_timerText.setPosition(0, 0);
}
//------------------------------------------------------------------------------------------------
//this func draws the Timer text

void LevelTimer::draw(sf::RenderWindow& window) const
{
	window.draw(m_timerText);
}

//------------------------------------------------------------------------------------------------
LevelTimer& LevelTimer::instance()
{
	static LevelTimer lvlTimer;
	return lvlTimer;
}

//------------------------------------------------------------------------------------------------
void LevelTimer::refreshTime()
{
	float fMilliseconds, fSeconds;
	int intMilliseconds, intSeconds;
	auto stringMilliseconds = sf::String();
	auto stringSeconds = sf::String();
	auto timerString = sf::String();
	// Timer Countdown //
	if (m_duration.asSeconds() > 0.f) {
		// Calculate countdown //
		m_duration -= m_time;
		fMilliseconds = std::modf(m_duration.asSeconds(), &fSeconds);
		// Change float to int //
		intSeconds = static_cast<int>(fSeconds);
		intMilliseconds = static_cast<int>(fMilliseconds * 1000);
		// Change int to string //
		stringMilliseconds = std::to_string(intMilliseconds);
		stringSeconds = std::to_string(intSeconds);

		if (intMilliseconds <= 0) {
			stringMilliseconds = "000";
		}

		if (intSeconds <= 0) {
			stringSeconds = "0";
			m_timerText.setFillColor(sf::Color::Red);
			m_timerText.setStyle(sf::Text::Bold);
			if (intMilliseconds % 5 == 0)
				m_timerText.setFillColor(sf::Color::Transparent);
		}
		else
			m_timerText.setFillColor(sf::Color::Black);

		timerString = stringSeconds + ":" + stringMilliseconds;
		m_timerText.setString(timerString);
	}

}
//--------------------------------------------------------------------------------------------------
void LevelTimer::updateTimer(const sf::Time& deltaTime)
{
	setTime(deltaTime);
	refreshTime();
}

//------------------------------------------------------------------------------------------------
//this func set m_time

void LevelTimer::setTime(const sf::Time& gameTime)
{
	m_time = gameTime;
}

//--------------------------------------------------------------------------------------------------
//this func update m_duration

void LevelTimer::updateDuration(const sf::Time& factor)
{
	m_duration += factor;

}