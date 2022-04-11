#include "Manager.h"
#include <array>
#include <iostream>

using std::cerr;

Manager::Manager()
{
	initTextures();
	initSounds();
	initFonts();
}


void Manager::initTextures()
{
	auto filesName = std::array<std::string, NUM_OF_TEXTURES>({
		"resources/king.png",
		"resources/warrior.png",
		"resources/mage.png",
		"resources/theif.png",
		"resources/key.png",
		"resources/wall.png",
		"resources/gate-sheet.png",
		"resources/fire-sheet.png",
		"resources/throne.png",
		"resources/teleport.png",
		"resources/orc.png",
		"resources/smurf2.png",
		"resources/gifts.png",
		"resources/background.png",
		"resources/tile.png",
		"resources/castle.png",
		"resources/back.png"
		});
	auto texture = sf::Texture();
	for (auto i = size_t(0); i < NUM_OF_TEXTURES; i++) {
		if (!texture.loadFromFile(filesName[i])) {
			cerr << "Could not load texture" << std::endl; return;
		}
		m_textures[i]=texture;
	}
}

void Manager::initSounds()
{
	auto filesName = std::array<std::string, NUM_OF_SOUND>({
		"resources/back_sound.ogg",
		"resources/click.wav",
		"resources/selected.wav",
		"resources/opening-door.wav",
		"resources/endGame.wav",
		"resources/level up.wav",
		"resources/Game Over.wav",
		"resources/fighting.wav",
		"resources/game_win.wav",
		"resources/gotKey.wav",
		"resources/restart_level.wav",
		"resources/teleport.wav",
		"resources/death.wav",
		"resources/reduce_time.wav",
		"resources/add_time.wav"
		});
	for (auto i = size_t(0); i < NUM_OF_SOUND; i++) {
		if (!m_soundsBuffer[i].loadFromFile(filesName[i])) 
		{
			cerr << "Could not load sound " <<i<< std::endl;  
			return;
		}
		m_sounds[i].setBuffer(m_soundsBuffer[i]);
		m_sounds[i].setVolume(35.f);
	}
	m_sounds[0].setVolume(15.f);
}

void Manager::initFonts()
{
	auto filesName = std::array<std::string, NUM_OF_FONTS>({
		"resources/menu_font.ttf",
		"resources/some_font.ttf",
		"resources/font3.ttf",
		"resources/font1.ttf",
		"resources/font4.otf",
		"resources/font5.otf"
		});
	for (auto i = size_t(0); i < NUM_OF_FONTS; i++) {
		if (!m_fonts[i].loadFromFile(filesName[i]))
		{
			cerr << "Could not load font " << std::endl;  return;
		}
	}

}

Manager& Manager::instance()
{
	static auto instance = Manager();
	return instance;
}


const sf::Font& Manager::getFont(const size_t indx) const
{
	return m_fonts[indx];
}


const sf::Texture& Manager::getTexture( size_t indx) const
{
	return m_textures[indx];
}

void Manager::play_stop(Sounds sound, const bool& isPlay)
{
	isPlay ? m_sounds[sound].play() : m_sounds[sound].stop();
}

void Manager::setLoop(Sounds sound, const bool& isLoop)
{
	m_sounds[sound].setLoop(isLoop);
}

bool Manager::isSoundStopped(Sounds sound)
{
	return  m_sounds[sound].getStatus() == sf::SoundSource::Status::Stopped;
}