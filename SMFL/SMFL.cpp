//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES

#include "Player.h"
#include "BulletManager.h"
#include "PlControls.h"
#include "EnemyManager.h"
#include "Level.h"
#include "CollisionManager.h"
#include "UI.h"
#include "SoundManager.h"
#include "Score.h"
#include "ReverbButton.h"
#include "ThreeDeeSoundButton.h"
#include "DopplerButton.h"
#include "PauseSoundButton.h"


// Game Modes
//////////////////
const byte MAINMENU = 0, GAME = 1, OPTIONS = 2, SCORE = 3, GAMEOVER = 4, LEVELCOMPLETE = 5, DISCONNECTED = 6;
byte gameMode = MAINMENU;
byte prevGameMode = gameMode;

// Variables
//////////////////
std::vector<sf::Text> highscores(10);
sf::RectangleShape cursor;
byte cursorNum = 1;
byte cursorOffset = 62;
byte numOfHighScores = 10;
bool updateScores = true;
bool shakeScreen = false;

sf::Clock myClock;
sf::Time deltaTime;
Player player;
Level level;
sf::Texture m_tex, m_bgTex, mainTex, highScoreTex, controllerDisconnectedTex, controlsTex;
sf::Sprite m_titleSpr, highscoreSpr, disconnectedSpr, controlsSpr;
std::vector<sf::Texture> m_backGroundTex;
sf::Vector2f screenDimensions = sf::Vector2f(600, 800);
int fps = 0;
sf::Font font;
sf::Text text, cScoreTxt, hScoreTxt, livesTxt;
ReverbButton reverbButton = ReverbButton(sf::IntRect(5, 690, 200, 20));
ThreeDeeSoundButton threeDeeButton = ThreeDeeSoundButton(sf::IntRect(5, 750, 200, 20));
DopplerButton dopplerButton = DopplerButton(sf::IntRect(5, 720, 200, 20));
PauseSoundButton pauseSoundButton = PauseSoundButton(sf::IntRect(5, 780, 200, 20));

//////////////////
const byte m_MAXLEVELS = 1;
//////////////////
void Init()
{
	player = Player(*&m_tex, sf::Vector2f(280, 600));
	level = Level(*&m_backGroundTex, screenDimensions);
	UI::Instance().Init(*&m_tex);
	SoundManager::Instance().Init();
	Score::Instance().Init();
	BulletManager::Instance().Init(*&m_tex);
	EnemyManager::Instance().Init(*&m_tex);
	CollisionManager::Instance().Init();

	// Set Up Text for highScores
	for (int i = 0; i < numOfHighScores; i++)
	{
		highscores.at(i).setFont(font);
		highscores.at(i).setPosition(sf::Vector2f(260, 220 + 40 * i));
		highscores.at(i).setCharacterSize(30);
	}


}
void LoadContent()
{

	// Check that assets are been loaded
	m_tex.loadFromFile("../resources/sprite.png");

	mainTex.loadFromFile("../resources/title.png");
	m_titleSpr.setTexture(mainTex);
	m_titleSpr.setTextureRect(sf::IntRect(0, 0, 600, 800));

	highScoreTex.loadFromFile("../resources/highscore.png");
	highscoreSpr.setTexture(highScoreTex);
	highscoreSpr.setTextureRect(sf::IntRect(0, 0, 600, 800));

	controllerDisconnectedTex.loadFromFile("../resources/disconnected.png");
	disconnectedSpr.setTexture(controllerDisconnectedTex);
	disconnectedSpr.setTextureRect(sf::IntRect(0, 0, 600, 800));


	controlsTex.loadFromFile("../resources/controls.png");
	controlsSpr.setTexture(controlsTex);
	controlsSpr.setTextureRect(sf::IntRect(0, 0, 600, 800));


	for (int i = 0; i < m_MAXLEVELS; i++)
	{
		std::string text = "../resources/Level";
		text += std::to_string(i);
		text += ".png";
		m_bgTex.loadFromFile(text);
		m_backGroundTex.push_back(m_bgTex);
	}
}

// UPDATE GAME MODES
//////////////////
void(UpdateMainMenu())
{

	if (PlControls::Instance().m_leftAnalogStick.y > 60 && PlControls::Instance().m_leftAnalogStickPrev.y < 60)
	{
		if (cursorNum < SCORE)
		{
			cursorNum++;
			cursor.setPosition(sf::Vector2f(cursor.getPosition().x, cursor.getPosition().y + cursorOffset));
			SoundManager::Instance().PlaySFX(SoundManager::SoundsList::CURSOR_SFX);
		}
	}

	else if (PlControls::Instance().m_leftAnalogStick.y < -60 && PlControls::Instance().m_leftAnalogStickPrev.y > -60)
	{
		if (cursorNum > GAME)
		{
			cursorNum--;
			cursor.setPosition(sf::Vector2f(cursor.getPosition().x, cursor.getPosition().y - cursorOffset));
			SoundManager::Instance().PlaySFX(SoundManager::SoundsList::CURSOR_SFX);
		}
	}

	if (PlControls::Instance().m_buttons.at(0) && PlControls::Instance().m_buttons.at(0) != PlControls::Instance().m_buttonsPrev.at(0))
	{
		if (cursorNum == GAME)
		{
			gameMode = GAME;
			SoundManager::Instance().PlaySoundBG(SoundManager::SoundsList::BACKGROUND_MUSIC_LEVEL_1);
		}
		else if (cursorNum == OPTIONS)
		{
			cursorNum++;
			gameMode = OPTIONS;
			cursor.setPosition(sf::Vector2f(cursor.getPosition().x, cursor.getPosition().y + cursorOffset));
			SoundManager::Instance().PlaySFX(SoundManager::SoundsList::CONFIRM_SFX);
		}
		else if (cursorNum == SCORE)
		{
			gameMode = SCORE;
			SoundManager::Instance().PlaySFX(SoundManager::SoundsList::CONFIRM_SFX);
		}
	}
}
void(UpdateGame())
{
	level.Update(deltaTime.asSeconds(), EnemyManager::Instance().GetBoss()->CheckIfBossHasStopped(), EnemyManager::Instance().GetBoss()->CheckIfExploding());
	player.Update(deltaTime.asMicroseconds());
	BulletManager::Instance().Update(deltaTime, screenDimensions);
	EnemyManager::Instance().Update(player.getPosition(), deltaTime.asMicroseconds(), screenDimensions);
	CollisionManager::Instance().CheckCollisions(player.GetCollisionBox(), &player);
	CollisionManager::Instance().EnemBulletPl(&player);
	if (EnemyManager::Instance().ShouldCheckBoss())
		CollisionManager::Instance().CheckBossCollisions(player.GetCollisionBox());
	Score::Instance().UpdateScores();
	livesTxt.setString("x" + std::to_string(player.GetLivesNum()));
	cScoreTxt.setString(Score::Instance().getCurrentScore());
	hScoreTxt.setString(Score::Instance().getHighestScore());

}
void(UpdateLevelComplete())
{
}
void(UpdateGameOver())
{
}
void(UpdateOptions())
{
	if (PlControls::Instance().m_buttons.at(0) && PlControls::Instance().m_buttons.at(0) != PlControls::Instance().m_buttonsPrev.at(0))
	{
		gameMode = MAINMENU;
		cursorNum--;
		cursor.setPosition(sf::Vector2f(cursor.getPosition().x, cursor.getPosition().y - cursorOffset));
	}
}
void(UpdateScore())
{
	// Put in game over screen later on 
	////////////////////////////////////
	if (updateScores)
	{
		std::vector<std::string> temp;
		temp = Score::Instance().GetAndSortHighScores();
		for (int i = 0; i < numOfHighScores; i++)
			highscores.at(i).setString(temp.at(i));
		updateScores = false;
	}

	if (PlControls::Instance().m_buttons.at(0) && PlControls::Instance().m_buttons.at(0) != PlControls::Instance().m_buttonsPrev.at(0))
	{
		Score::Instance().SaveScoresToFile();
		gameMode = MAINMENU;
	}
}
// DRAW GAME MODES
//////////////////
void(DrawMainMenu(sf::RenderWindow &p_window))
{
	p_window.draw(m_titleSpr);
	p_window.draw(cursor);
}
void(DrawGame(sf::RenderWindow &p_window, sf::View &p_view))
{
		p_window.draw(level.getSprite());

		EnemyManager::Instance().Draw(p_window);
		BulletManager::Instance().Draw(p_window);

	int maxPlayerSprites = player.getSprite().size();

	if (!player.CheckIfHidden())
		for (int i = 0; i < maxPlayerSprites; i++)
			p_window.draw(player.getSprite().at(i));


	p_window.draw(UI::Instance().getSprite());
	pauseSoundButton.Draw(p_window);
	if (threeDeeButton.Is3DEnabled())
	{
		reverbButton.Draw(p_window);
		dopplerButton.Draw(p_window);
	}
	threeDeeButton.Draw(p_window);

	// Draw Score
	////////////////////
	p_window.draw(cScoreTxt);
	p_window.draw(hScoreTxt);
	p_window.draw(livesTxt);


	// Change to level complete scene
	////////////////////
	p_window.draw(level.getEndLevelImage());
	if (level.getEndLevelImage().getFillColor().a > 250)
	{
		SoundManager::Instance().StopAllSounds();
		shakeScreen = false;
		p_view.reset(sf::FloatRect(0, 0, 600, 800));
		p_window.setView(p_view);
		gameMode = LEVELCOMPLETE;
	}

	if (!shakeScreen)
	{
		if (EnemyManager::Instance().GetBoss()->CheckIfExploding())
			shakeScreen = true;
	}
	else
	{
		p_view.reset(sf::FloatRect(rand() % 21 + (-10), rand() % 21 + (-10), 600, 800));
		p_window.setView(p_view);
	}


}
void(DrawGameOver(sf::RenderWindow &p_window))
{

}
void(DrawLevelComplete(sf::RenderWindow &p_window))
{
	p_window.draw(controlsSpr);
	p_window.draw(cursor);
}
void(DrawOptions(sf::RenderWindow &p_window))
{
	p_window.draw(controlsSpr);
	p_window.draw(cursor);
}
void(DrawScore(sf::RenderWindow &p_window))
{
	p_window.draw(highscoreSpr);
	p_window.draw(cursor);

	for (int i = 0; i < numOfHighScores; i++)
		p_window.draw(highscores.at(i));
}

void DrawDisconnected(sf::RenderWindow & p_window)
{
	p_window.draw(disconnectedSpr);
}

// UPDATE EVENT
/////////////////////////////
void Update()
{
	deltaTime = myClock.getElapsedTime();
	fps = 1.f / deltaTime.asSeconds();

	PlControls::Instance().Update(deltaTime);

	myClock.restart();

	if (gameMode != prevGameMode && gameMode != DISCONNECTED)
		prevGameMode = gameMode;

	if (PlControls::Instance().CheckIfControllerIsConnected() == false)
		gameMode = DISCONNECTED;
	else
		gameMode = prevGameMode;

	// Update Game Modes
	/////////////////////////////
	switch (gameMode)
	{
	case MAINMENU:
		UpdateMainMenu();
		break;
	case GAME:
		UpdateGame();
		break;
	case GAMEOVER:
		UpdateGameOver();
		break;
	case OPTIONS:
		UpdateOptions();
		break;
	case SCORE:
		UpdateScore();
		break;
	case LEVELCOMPLETE:
		UpdateLevelComplete();
		break;
	case DISCONNECTED:
		break;
	}
	SoundManager::Instance().UpdateSound(player.getPosition(), player.getVelocity());
}

// DRAW EVENT
/////////////////////////////
void Draw(sf::RenderWindow &p_window, sf::View &p_view)
{
	// Clear Window
	p_window.clear();


	// Update Draw Modes
	/////////////////////////////
	switch (gameMode)
	{
	case MAINMENU:
		DrawMainMenu(p_window);
		break;
	case GAME:
		DrawGame(p_window, p_view);
		break;
	case GAMEOVER:
		DrawGameOver(p_window);
		break;
	case OPTIONS:
		DrawOptions(p_window);
		break;
	case SCORE:
		DrawScore(p_window);
		break;
	case LEVELCOMPLETE:
		DrawLevelComplete(p_window);
		break;
	case DISCONNECTED:
		DrawDisconnected(p_window);
		break;
	}

	// Display Window
	p_window.display();
}

////////////////////////////////////////////////////////////
///Entry point of application 
//////////////////////////////////////////////////////////// 
int main()
{

	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y, 32), "SFML First Program");
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 600, 800));
	window.setView(view);


	//window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	cursor.setOutlineColor(sf::Color::White);
	cursor.setOutlineThickness(3);
	cursor.setFillColor(sf::Color::Transparent);
	cursor.setSize(sf::Vector2f(220, 40));
	cursor.setPosition(sf::Vector2f(190 , 536));

	//load a font
	font.loadFromFile("C:\\Windows\\Fonts\\consolaz.TTF");
	cScoreTxt.setFont(font);
	//text.setStyle(sf::Text::Bold);
	cScoreTxt.setCharacterSize(22);
	cScoreTxt.setPosition(40, 30);

	hScoreTxt.setFont(font);
	//text.setStyle(sf::Text::Bold);
	hScoreTxt.setCharacterSize(22);
	hScoreTxt.setPosition(244, 30);

	livesTxt.setFont(font);
	livesTxt.setCharacterSize(22);
	livesTxt.setPosition(60, 60);


	// Load Content
	/////////////////////////////
	LoadContent();

	// Initialize
	/////////////////////////////
	Init();

	

	// Game Loop
	/////////////////////////////
	while (window.isOpen())
	{
		// Keyboard Events
		/////////////////////////////
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();

			if (Event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePos = sf::Vector2i(Event.mouseButton.x, Event.mouseButton.y);
				pauseSoundButton.Update(mousePos);
				if (threeDeeButton.Is3DEnabled())
				{
					reverbButton.Update(mousePos);
					dopplerButton.Update(mousePos);
				}

				threeDeeButton.Update(mousePos);
			}		
		}

		// Update World, Events, Game
		/////////////////////////////
		Update();

		// Draw World, Events, Game
		/////////////////////////////
		Draw(window, view);
	} 
	return EXIT_SUCCESS;
}



// Joystick Buttons
// (0, 0) - Y
// (0, 1) - A
// (0, 2) - X
// (0, 3) - B
// (0, 4) - Left Bumper
// (0, 5) - Right Bumper
// (0, 6) - Back Bumper
// (0, 7) - Start Bumper
// (0, 8) - Left Analog Press
// (0, 9) - Right Analog Press

// sf::Joystick::X - Left Analog X-Axis
// sf::Joystick::Y - Left Analog Y-Axis
// sf::Joystick::R - Right Analog X-Axis
// sf::Joystick::U - Right Analog Y-Axis
// sf::Joystick::PovX - D-Pad X-Axis
// sf::Joystick::PovY - D-Pad Y-Axis

//// JOYPAD CHECKS
////////////////////////////////////////////////////////////// 
//if (sf::Joystick::isConnected(0))
//{
//	std::cout << "Joypad 1 is connected" << std::endl;
//
//	// Check How Many Buttons Joypad 0 has
//	int buttonCount = sf::Joystick::getButtonCount(0);
//	std::cout << "Button count: " << buttonCount << std::endl;
//}
//else
//std::cout << "Joypad 1 is not connected" << std::endl;