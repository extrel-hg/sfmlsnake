#include "mainheader.h"
#include "mainmenuheader.h"

int screenreswidth = 800;
int screenresheight = 600;
bool fullscreen = false;
std::string defaultplayername = "placeholder";
bool askforcustomnameafteraround = true;

int mainmenurecalcbuttons(sf::Font& font, sf::Text& titletext, sf::Text& highscoretext, Button& playbutton, Button& quitbutton, Button& setbutton, sf::Sprite& mainmenugameicon, Button& logobox,
	Button& leaderboardbutton, Button& twoplayerbutton)
{
	titletext.setCharacterSize(TORELXPOS(40));
	titletext.setPosition(TORELXPOS(10), TORELYPOS(10));

	highscoretext.setCharacterSize(TORELXPOS(30));
	highscoretext.setPosition(TORELXPOS(10), TORELYPOS(550));

	playbutton.recalculatepos({ TORELXPOS(90),TORELYPOS(220) }, { TORELXPOS(160),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));
	leaderboardbutton.recalculatepos({ TORELXPOS(90),TORELYPOS(400) }, { TORELXPOS(160),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));
	setbutton.recalculatepos({ TORELXPOS(90),TORELYPOS(340) }, { TORELXPOS(160),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));
	quitbutton.recalculatepos({ TORELXPOS(90),TORELYPOS(460) }, { TORELXPOS(160),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));
	twoplayerbutton.recalculatepos({ TORELXPOS(90),TORELYPOS(280) }, { TORELXPOS(160),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));

	mainmenugameicon.setScale(sf::Vector2f(screenreswidth / 800.f, screenresheight / 600.f));
	mainmenugameicon.setPosition(sf::Vector2f(TORELXPOS(800-128), TORELYPOS(0)));

	logobox.recalculatepos({ TORELXPOS(800 - 64),TORELYPOS(64) }, { TORELXPOS(128),TORELYPOS(128) }, TORELXPOS(5));

	return 1;
}

int mainmenu(sf::RenderWindow& gamewindow)
{
	bool visitedsettingsyet = false;

	std::vector < std::pair<int, std::string>> highscores;
	std::vector <std::string> highscorenames;

	if (loadhighscores(highscores, highscorenames) == -1)
	{
		return -1;
	}
	savehighscoredata(highscores);

	{
		int loadsettingsretcode = loadsettings(screenreswidth,screenresheight,fullscreen,defaultplayername,askforcustomnameafteraround,visitedsettingsyet);
		if(loadsettingsretcode == -1)
		{
			errorbox("Error loading settings.", "Error while loading the settings. Try reinstalling your game, or fixing the set.txt file manually.");
		}
	}

	bool quitfull = false;
	int returncode = 0;
	
	sf::Font font;
	if (!font.loadFromFile("rsc/munro.ttf"))
	{
		errorbox("Could not load font.", "Could not load munro.ttf in rsc folder. Try reinstalling your game or putting the font back.");
		return -1;
	}
	

	sf::Sprite mainmenugameicon;
	sf::Texture gameicontexture;
	if (!gameicontexture.loadFromFile("rsc/icon.png"))
	{
		errorbox("Could not load icon image.", "Could not load icon.png in rsc folder. Try reinstalling your game or putting the file back.");
		return -1;
	}

	mainmenugameicon.setTexture(gameicontexture);

	sf::Text titletext("Snake " + versiontag + "\nBy Hubert Gonera\n" + builddate, font);
	sf::Text highscoretext("Current highscore: None", font);
	
	int currenthighscore = 0;

	if (highscores.size() > 0)
	{
		std::string goodhighscorename = "NOGOODHIGHSCORENAMES";
		int goodhighscorenumber = 0;
		for (int i = 0; i < highscores.size(); i++)
		{
			std::string vtag = getvtagfromstring(highscores[i].second);
			if (vtag == versiontag)
			{
				goodhighscorename = highscorenames[i];
				goodhighscorenumber = i;
				break;
			}
		}
		if (goodhighscorename == "NOGOODHIGHSCORENAMES")
		{
			highscoretext.setString("Current highscore: None");
		}
		else {
			highscoretext.setString("Current highscore by " + goodhighscorename + ": " + std::to_string(highscores[goodhighscorenumber].first));
			currenthighscore = highscores[goodhighscorenumber].first;
		}
	}

	Button playbutton(font, "Play");
	Button quitbutton(font, "Quit");
	Button setbutton(font, "Settings");
	Button twoplayerbutton(font, "2 Players");
	Button leaderboardbutton(font, "Leaderboard");
	Button logobox(font, " ");

	mainmenurecalcbuttons(font, titletext, highscoretext, playbutton, quitbutton, setbutton, mainmenugameicon, logobox, leaderboardbutton,twoplayerbutton);

	if (createwindow(gamewindow) == -1)
	{
		return -1;
	}

	while (!quitfull)
	{
		int gameloopreturncode = -69;
		sf::Event windowevent;
		
		while (gamewindow.pollEvent(windowevent))
		{
			bool startgame = false;
			bool quit = false;
			bool settings = false;
			bool recalculate = false;
			bool leaderboard = false;
			bool twoplayers = false;
			if (windowevent.type == sf::Event::Closed)
			{
				quit = true;
			}
			if (windowevent.type == sf::Event::MouseButtonReleased)
			{
				if (playbutton.arethosethisbuttoncords({ sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y }))
				{
					startgame = true;
				}
				else if (quitbutton.arethosethisbuttoncords({ sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y }))
				{
					quit = true;
				}
				else if (setbutton.arethosethisbuttoncords({ sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y }))
				{
					settings = true;
				}
				else if (leaderboardbutton.arethosethisbuttoncords({ sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y }))
				{
					leaderboard = true;
				}
				else if (twoplayerbutton.arethosethisbuttoncords({ sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y }))
				{
					twoplayers = true;
				}
			}
			if (windowevent.type == sf::Event::KeyReleased)
			{
				if (windowevent.key.code == sf::Keyboard::Enter)
				{
					startgame = true;
				}
				else if (windowevent.key.code == sf::Keyboard::Q)
				{
					quit = true;
				}
				else if (windowevent.key.code == sf::Keyboard::S)
				{
					settings = true;
				}
				else if (windowevent.key.code == sf::Keyboard::L)
				{
					leaderboard = true;
				}
				else if (windowevent.key.code == sf::Keyboard::D)
				{
					twoplayers = true;
				}
			}
			if (startgame)
			{
				int scorefromround = -1;
				std::string namefromround = "placeholder";
				gameloopreturncode = screenloopandinit(gamewindow, scorefromround, namefromround, font);
				loadhighscores(highscores, highscorenames);
				if (gameloopreturncode != 3)
				{
					updatehighscores(highscores, highscorenames, scorefromround, namefromround);
					if (scorefromround > currenthighscore)
					{
						highscoretext.setString("Current highscore by " + namefromround + ": " + std::to_string(scorefromround));
					}
					savehighscoredata(highscores);
				}
				if (gameloopreturncode == 0)
				{
					quit = true;
				}
				{
					int loadsettingsretcode = loadsettings(screenreswidth,screenresheight,fullscreen,defaultplayername,askforcustomnameafteraround,visitedsettingsyet);
					if(loadsettingsretcode == -1)
					{
						errorbox("Error loading settings.", "Error while loading the settings. Try reinstalling your game, or fixing the set.txt file manually.");
					}
				}
			}

			if(twoplayers)
			{
				int scorefromround = -1;
				gameloopreturncode = twoplayerscreenloopandinit(gamewindow, font);
				if (gameloopreturncode == 0)
				{
					quit = true;
				}
				{
					int loadsettingsretcode = loadsettings(screenreswidth,screenresheight,fullscreen,defaultplayername,askforcustomnameafteraround,visitedsettingsyet);
					if(loadsettingsretcode == -1)
					{
						errorbox("Error loading settings.", "Error while loading the settings. Try reinstalling your game, or fixing the set.txt file manually.");
					}
				}
			}

			if (leaderboard)
			{
				loadhighscores(highscores, highscorenames);
				int leaderboardretcode = leaderboardmenu(gamewindow, font, highscores, highscorenames);
				if (leaderboardretcode == 0)
				{
					quit = true;
				}
				loadhighscores(highscores, highscorenames);
				{
					int loadsettingsretcode = loadsettings(screenreswidth,screenresheight,fullscreen,defaultplayername,askforcustomnameafteraround,visitedsettingsyet);
					if(loadsettingsretcode == -1)
					{
						errorbox("Error loading settings.", "Error while loading the settings. Try reinstalling your game, or fixing the set.txt file manually.");
					}
				}
			}

			if (settings)
			{
				int settingsmenuretcode;
				settingsmenuretcode = settingsmenu(gamewindow, font, visitedsettingsyet);
				if (settingsmenuretcode == 0)
				{
					quit = true;
				}
				recalculate = true;
				loadhighscores(highscores, highscorenames);
				{
					int loadsettingsretcode = loadsettings(screenreswidth,screenresheight,fullscreen,defaultplayername,askforcustomnameafteraround,visitedsettingsyet);
					if(loadsettingsretcode == -1)
					{
						errorbox("Error loading settings.", "Error while loading the settings. Try reinstalling your game, or fixing the set.txt file manually.");
					}
				}
			}

			if (quit)
			{
				gamewindow.close();
				returncode = 1;
				quitfull = true;
			}

			if (recalculate)
			{
				mainmenurecalcbuttons(font, titletext, highscoretext, playbutton, quitbutton, setbutton, mainmenugameicon, logobox, leaderboardbutton,twoplayerbutton);
			}
		}

		gamewindow.clear(backgroundcolor);
		gamewindow.draw(titletext);
		gamewindow.draw(highscoretext);
		gamewindow.draw(playbutton);
		gamewindow.draw(quitbutton);
		gamewindow.draw(setbutton);
		gamewindow.draw(mainmenugameicon);
		gamewindow.draw(logobox);
		gamewindow.draw(leaderboardbutton);
		gamewindow.draw(twoplayerbutton);
		gamewindow.display();	
	}

	return returncode;
}