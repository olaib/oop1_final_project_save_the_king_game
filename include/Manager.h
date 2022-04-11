#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>

const auto NUM_OF_FONTS = 6;
const auto NUM_OF_SOUND = 15;
const auto NUM_OF_TEXTURES = 17;
const auto PLAY = true;//play music
const auto STOP = false;//stop music

enum Textures :size_t {
	KING, WARRIOR, MAGE, THIEF, KEY, WALL, GATE, FIRE, THRONE,
	TELEPORT, ORC, DWARF1, GIFTS, BACKGROUND, TILE, CASTLE, BACK,
};

enum Sounds:size_t {
	PLAY_SOUND, CLICK, SELECTED ,DOOR , END_GAME ,LEVEL_UP,
	GameOver, FIGHTING, WIN_LVL, Got_Obj, RESTART,Tel_sound,
    Gift_remDwarfs, Gift_redTime , Gift_addTime
};

enum Fonts :size_t {
	menu_font,
	some_font,
	font3,
	font1,
	font4,
	font5
};


class Manager {
public:
	static Manager& instance();
	const sf::Font& getFont(const size_t indx)const;
	const sf::Texture& getTexture( size_t indx)const;
	void play_stop(Sounds sound, const bool& isPlay);
	void setLoop(Sounds sound,const bool& isLoop);
	bool isSoundStopped(Sounds sound);
private:
	Manager();
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
	std::array<sf::Font, NUM_OF_FONTS> m_fonts;
	std::array <sf::Sound, NUM_OF_SOUND> m_sounds;
	std::array <sf::Texture, NUM_OF_TEXTURES> m_textures;
	std::array <sf::SoundBuffer, NUM_OF_SOUND> m_soundsBuffer;
	void initTextures();
	void initSounds();
	void initFonts();
};