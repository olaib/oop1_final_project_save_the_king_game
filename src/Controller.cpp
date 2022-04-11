#include "Controller.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
const auto FILE_NAME = "resources/messages.txt"; //Input file name of the message text

Controller::Controller() : m_window(sf::VideoMode(800, 600, 32), "Save the King", sf::Style::Titlebar | sf::Style::Close)
                         , m_board(sf::Vector2u(800, 600)),
                           m_menu(sf::Vector2u(800, 600), Manager::instance().getFont(Fonts::menu_font)) {
    initTexts();
    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);
    srand(static_cast<unsigned>(std::time(nullptr)));
    Manager::instance().setLoop(PLAY_SOUND, true);
    m_background.setTexture(Manager::instance().getTexture(CASTLE));
}



void Controller::run()
{
    static sf::Clock gameClock;
    while (m_window.isOpen())
    {
        draw(gameClock);
        handleEvents();
        updateGameObjects(gameClock);
    }
    Manager::instance().play_stop(PLAY_SOUND, STOP);
}

void Controller::updateGameObjects(sf::Clock& gameClock)
{
    const auto deltaTime = gameClock.restart();
    switch (m_gameStatus) {
    case GameStatus::START_GAME:
        LevelTimer::instance().initTimer();
        Manager::instance().play_stop(PLAY_SOUND,PLAY);
        m_board.NewGame(m_window.getSize());
        LevelTimer::instance().setDuration(sf::seconds(m_board.getLvlTime()));
        drawGetReady(gameClock);
        m_gameStatus = GameStatus::PLAYING;
        break;
        //----------------------
    case GameStatus::EXIT:
        m_window.close();
        return;
        //----------------------
    case GameStatus::RESTART_LEVEL:
        m_board.restartLvl();
        LevelTimer::instance().setDuration(sf::seconds(m_board.getLvlTime()));
        if (Manager::instance().isSoundStopped(RESTART)) {
            gameClock.restart();
            m_gameStatus = GameStatus::PLAYING;
        }
        break;
        //-----------------------
    case GameStatus::PLAYING:
        playing(deltaTime);
        break;
        //----------------------
    case GameStatus::LEVEL_UP:
        if (Manager::instance().isSoundStopped(LEVEL_UP)) {
            lvlUp();
            m_gameStatus = GameStatus::PLAYING;
        }
        break;
        //----------------------
    case GameStatus::GAME_OVER:
        LevelTimer::instance().setColor();
        Manager::instance().play_stop(PLAY_SOUND, STOP);
        m_menu.gameOver(m_window);
        m_gameMsgs[RESTART_MSG].setString("Level " + std::to_string(m_board.getLvlNum()));
        m_gameMsgs[RESTART_MSG].setOrigin({ m_gameMsgs[RESTART_MSG].getLocalBounds().width / 2.f
            ,m_gameMsgs[RESTART_MSG].getLocalBounds().height });
        Manager::instance().play_stop(RESTART, PLAY);
        m_gameStatus = GameStatus::RESTART_LEVEL;
        break;
        //----------------------
    case GameStatus::END_GAME:
        Manager::instance().play_stop(PLAY_SOUND, STOP);
        Manager::instance().setLoop(END_GAME,true);
        Manager::instance().play_stop(END_GAME, PLAY);
        break;
    }
}



void Controller::draw(sf::Clock& gameClock)
{
    m_window.clear();
    m_window.draw(m_background);
    switch (m_gameStatus) {
    case GameStatus::END_GAME:
        drawEndMsg(gameClock);
        break;

    case GameStatus::PLAYING:
        m_board.draw(m_window);
        m_window.draw(m_numOfLevel);
        LevelTimer::instance().draw(m_window);
        break;

    case GameStatus::LEVEL_UP:
            m_window.draw(m_gameMsgs[LVL_UP_MSG]);
        break;

    case GameStatus::RESTART_LEVEL:
        m_window.draw(m_gameMsgs[RESTART_MSG]);
        break;
    }
    m_window.display();    
};


// this function checks the events in the game

void Controller::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        while (m_menu.menuStatus() == Menu_t::MENU || m_gameStatus == GameStatus::MENU)
        {
            m_menu.run(m_window);
            if (m_menu.menuStatus() == Menu_t::PLAY) {
                m_gameStatus = GameStatus::START_GAME;
            }
            if (m_menu.menuStatus() == Menu_t::EXIT) {
                m_gameStatus = GameStatus::EXIT;
                break;
            }
        }

        switch (event.type)
        {
        case sf::Event::Closed:
            m_window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
            {
                m_window.close();
                break;
            }
            if (event.key.code == sf::Keyboard::E && m_gameStatus == GameStatus::PLAYING) {
                m_board.updateCurrIndx();//next player
                break;
            }
        }
    }
}



//------------------------------------------------
void Controller::lvlUp() {
    m_board.NewLevel(m_window.getSize());
    LevelTimer::instance().setColor();
    LevelTimer::instance().setDuration(sf::seconds(m_board.getLvlTime()));
    m_numOfLevel.setString("Level: " + std::to_string(m_board.getLvlNum()));
}

void Controller::playing(const sf::Time& deltaTime) {
    LevelTimer::instance().updateTimer(deltaTime);
    if (m_board.isLvlWin()) {
        if (!m_board.isFileExist(m_board.getLvlNum() + 1)) {
            m_gameStatus = GameStatus::END_GAME;
            return;
        }
        Manager::instance().play_stop(Sounds::LEVEL_UP,PLAY);
        m_gameStatus = GameStatus::LEVEL_UP;
        return;
    }
    //check if timer has over
    else if (LevelTimer::instance().isTimerOver())
    {
        Manager::instance().play_stop(PLAY_SOUND, STOP);
        Manager::instance().play_stop(GameOver, PLAY);
        m_gameStatus = GameStatus::GAME_OVER;
        return;
    }
    m_board.move(deltaTime);
    m_board.dwarfCollision();
    m_board.handleCollisions(*m_board.getPlayer(m_board.getCurrIndx()));
    
}
//============================init=======================================
void Controller::initTexts()
{
    readMessages();//read messages from txt file
    //get ready text
    m_board.initText(m_gameMsgs[GETREADY_MSG], 50, Manager::instance().getFont(Fonts::some_font), "", 2,
        { m_window.getSize().x / 2.f, m_window.getSize().y / 2.f });
    //numOfLevel text
    m_board.initText(m_numOfLevel, 35, Manager::instance().getFont(Fonts::font5)
        , "Level: " + std::to_string(m_board.getLvlNum()), 1.f, { 740.f, 5.f });
    //level up text
    m_board.initText(m_gameMsgs[LVL_UP_MSG], 50, Manager::instance().getFont(Fonts::font3),
        m_messages[LVL_UP_MSG], 2.f
        , { m_window.getSize().x / 2.f, m_window.getSize().y / 2.f });
    //RESTART msg
    m_board.initText(m_gameMsgs[RESTART_MSG], 50, Manager::instance().getFont(Fonts::font3), "", 2.f
        , { m_window.getSize().x / 2.f, m_window.getSize().y / 2.f });
    //end game text
    m_board.initText(m_gameMsgs[END_GAME_MSG], 30, Manager::instance().getFont(Fonts::some_font), m_messages[END_GAME_MSG], 2.f
        , { m_window.getSize().x / 2.f, m_window.getSize().y / 2.f });
    //press key text
    m_board.initText(m_gameMsgs[PRESS_KEY], 50, Manager::instance().getFont(Fonts::font4), "press B to return to main menu\n", 2.f
        , { m_window.getSize().x / 2.f, m_window.getSize().y / 2.f });
    //frame for end game text
    initMsgFrame();
}


//This function initializes the frame of the game end message

void Controller::initMsgFrame() {
    m_msgFrame.setFillColor(sf::Color::White - sf::Color(0, 0, 0, 128));
    m_msgFrame.setOutlineColor(sf::Color::Black);
    m_msgFrame.setOutlineThickness(4.f);
    m_msgFrame.setOrigin(m_gameMsgs[END_GAME_MSG].getOrigin());
    m_msgFrame.setPosition(sf::Vector2f(m_gameMsgs[END_GAME_MSG].getPosition()));
    m_msgFrame.setSize(sf::Vector2f(m_gameMsgs[END_GAME_MSG].getLocalBounds().width
        , m_gameMsgs[END_GAME_MSG].getLocalBounds().height));
}


//This function reads text messages from an input fileand saves them in an array of strings

void Controller::readMessages()
{
    auto msgFile = std::ifstream(FILE_NAME);
    if (!msgFile) {
        std::cerr << "Error in opening file!" << std::endl;
        return;
    }
    auto line = string();
    auto i = size_t(0);
    auto isreadMsg = false;
    while (std::getline(msgFile, line)) {
        if (line[0] == '-')
            isreadMsg = true;
        else if (line[0] == '=') {
            i++;
            isreadMsg = false;
            continue;
        }
        else if (isreadMsg) {
            m_messages[i] += line;
            m_messages[i] += "\n";
        }
    }
    msgFile.close();
}


// this function draws the "GET READY!" sign 

void Controller::drawGetReady( sf::Clock& gameClock)
{
    auto getReady = std::string();
    auto time = float(0);
    gameClock.restart();
    for (int i = 0; i < 3;)
    {
        getReady = "GET READY!\n         " + std::to_string(3 - i);
        time += gameClock.getElapsedTime().asSeconds();
        m_gameMsgs[GETREADY_MSG].setPosition(sf::Vector2f(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f));
        m_gameMsgs[GETREADY_MSG].setString(getReady);
        auto rect = sf::FloatRect(m_gameMsgs[GETREADY_MSG].getLocalBounds());
        m_gameMsgs[GETREADY_MSG].setOrigin(rect.width / 2.f, rect.height / 2.f);

        m_window.draw(m_background);
        m_window.draw(m_gameMsgs[GETREADY_MSG]);
        m_window.display();
        m_window.clear();
        if (time >= 10)
        {
            i++;
            time = 0;
            gameClock.restart();
        }
    }
}


// this function draws the end game message

void Controller::drawEndMsg(sf::Clock& gameClock) {
    auto time = float(0);
    gameClock.restart();
    string line, currMsg;
    //read from the string as if it were a stream
    std::stringstream ss(m_messages[END_GAME_MSG]);
    while (std::getline(ss, line))
    {
        currMsg += line + "\n";
        m_gameMsgs[END_GAME_MSG].setString(currMsg);
        while (time <= 60)
        {
            m_window.clear();
            m_window.draw(m_background);
            m_window.draw(m_msgFrame);
            m_window.draw(m_gameMsgs[END_GAME_MSG]);
            m_window.display();
            time += gameClock.getElapsedTime().asSeconds();
        }
        gameClock.restart();
        time = 0;
    }
    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
        m_window.clear();
        m_window.draw(m_background);
        m_window.draw(m_gameMsgs[PRESS_KEY]);
        m_window.display();
    }
    Manager::instance().play_stop(END_GAME, STOP);
    m_gameStatus = GameStatus::MENU;
}