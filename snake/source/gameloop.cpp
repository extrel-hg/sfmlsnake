#include "mainheader.h"
#include <chrono>
#include <string>

int handleinput(sf::RenderWindow& gamewindow)
{
	sf::Event windowevent;

	while (gamewindow.pollEvent(windowevent))
	{
		if (windowevent.type == sf::Event::Closed)
		{
			return 2;
		}
	}

	return 1;
}

int render(sf::RenderWindow &gamewindow, Mapstate &mapstate, std::pair<int, int>& apple, std::vector<std::pair<int, int>>& snakeparts, double& speed,sf::Text text, sf::Font font)
{
	if (!(apple.first < 0 || apple.first > mapstate.mapxsize - 1 || apple.second < 0 || apple.second > mapstate.mapysize - 1))
	{
		mapstate.settilecolor(apple.first, apple.second, 1);
	}
	int valr = 255 - 1;
	int valg = 255 - 1;
	int valb = 0;
	for (int i = 1; i < snakeparts.size(); i++)
	{
		
		if (i %  2 == 0)
		{
			valr = 255-i;
			valg = 255-i;
			valb = 0;
		}
		else if (i % 2 == 1)
		{
			valr = 2*i;
			valg = 192-2*i;
			valb = 0;
		}
		mapstate.settilecolorRGB(snakeparts[i].first, snakeparts[i].second, valr, valg, valb, 255);
	}
	mapstate.settilecolorRGB(snakeparts[0].first, snakeparts[0].second, 140, 140, 140, 255);

	mapstate.transfermapstatetoVA(800, 600);

	gamewindow.clear();
	gamewindow.draw(mapstate);
	gamewindow.draw(text);
	gamewindow.display();

	return 1;
}

int simulate(Mapstate& mapstate, int t, double dt, std::pair<int,int> &apple, std::vector<std::pair<int, int>> &snakeparts, std::pair<int, int>& snakeheading, double& tillmove, double& movementcap, double& speed, sf::Text& text)
{
	if (apple.first == -1)
	{
		bool found = false;
		while (!found)
		{
			apple.first = rand() % mapstate.mapxsize;
			apple.second = rand() % mapstate.mapysize;
			
			bool checking = true;
			for (int i = 0; i < snakeparts.size(); i++)
			{
				if (apple.first == snakeparts[i].first && apple.second == snakeparts[i].second)
				{
					checking = false;
					break;
				}
			}
			if (checking)
			{
				found = true;
			}
		}
	}

	int truesnakesize = snakeparts.size() + 1;

	{
		int right = 0;
		int up = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			up = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			up = -1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			right = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			right = -1;
		}

		if (right == 1)
		{
			if (snakeparts.size() > 1)
			{
				if (snakeparts[0].first >= snakeparts[1].first)
				{
					snakeheading.first = 1;
					snakeheading.second = 0;
				}
			}
			else {
				snakeheading.first = 1;
				snakeheading.second = 0;
			}
		}
		if (right == -1)
		{
			if (snakeparts.size() > 1)
			{
				if (snakeparts[0].first <= snakeparts[1].first)
				{
					snakeheading.first = -1;
					snakeheading.second = 0;
				}
			}
			else {
				snakeheading.first = -1;
				snakeheading.second = 0;
			}
		}
		if (up == 1)
		{
			if (snakeparts.size() > 1)
			{
				if (snakeparts[0].second <= snakeparts[1].second)
				{
					snakeheading.first = 0;
					snakeheading.second = -1;
				}
			}
			else {
				snakeheading.first = 0;
				snakeheading.second = -1;
			}
		}
		if (up == -1)
		{
			if (snakeparts.size() > 1)
			{
				if (snakeparts[0].second >= snakeparts[1].second)
				{
					snakeheading.first = 0;
					snakeheading.second = 1;
				}
			}
			else {
				snakeheading.first = 0;
				snakeheading.second = 1;
			}
		}
	}

	tillmove = tillmove + dt*speed;

	bool ate = false;
	bool wallcollide = false;

	if (tillmove > movementcap)
	{
		{
			std::pair<int, int> temphead;
			temphead.first = snakeparts[0].first + snakeheading.first;
			temphead.second = snakeparts[0].second + snakeheading.second;

			if(temphead.first < 0) wallcollide = true;
			if(temphead.second < 0) wallcollide = true;
			if(temphead.first > mapstate.mapxsize - 1) wallcollide = true;
			if(temphead.second > mapstate.mapysize - 1) wallcollide = true;

			for (int i = 2; i < snakeparts.size(); i++)
			{
				if (temphead.first == snakeparts[i].first && temphead.second == snakeparts[i].second)
				{
					wallcollide = true;
					break;
				}
			}
		}
		if (!wallcollide)
		{
			std::pair<int, int> oldhead = snakeparts[0];
			snakeparts[0].first += snakeheading.first;
			snakeparts[0].second += snakeheading.second;
			tillmove = 0;

			if (snakeparts[0].first == apple.first && snakeparts[0].second == apple.second)
			{
				ate = true;
			}

			if (!ate)
			{
				if (snakeparts.size() > 1)
				{
					mapstate.settilecolor(snakeparts[snakeparts.size() - 1].first, snakeparts[snakeparts.size() - 1].second, 0);
				}
				else
				{
					mapstate.settilecolor(oldhead.first, oldhead.second, 0);
				}

			}
			for (int i = 1; i < snakeparts.size(); i++)
			{
				std::pair<int, int> temppart = snakeparts[i];
				snakeparts[i] = oldhead;
				oldhead = temppart;
			}
			if (ate)
			{
				apple.first = -1;
				apple.second = -1;

				//V1.1.0.0 speed = speed + ((snakeparts.size() + 3) / snakeparts.size() - snakeparts.size() / 100) * 0.05;

				speed = (-pow((0.013 * truesnakesize), 2)) + (truesnakesize / 25.0f) + 1.0f;

				int temp = snakeparts.size();
				std::string speedstring = std::to_string(speed);
				speedstring = speedstring.substr(0, 4);

				text.setString("Points:" + std::to_string(truesnakesize) + " Speed:" + speedstring);

				snakeparts.push_back(oldhead);
			}
		}
	}

	if (wallcollide)
	{
		return 2;
	}


	return 1;
}

int screenloopandinit(sf::RenderWindow& gamewindow, int& score)
{
	Mapstate mapstate(16, 12);

	std::vector<std::pair<int, int>> snakeparts;
	std::pair<int, int> snakeheading = { 1,0 }; //speed vector in tiles per second
	snakeparts.push_back({ 0,0 });

	std::pair<int, int> apple = { -1, -1 };

	double t = 0.0;
	const double dt = (1.0 / 64.0) / 4;

	double tillmove = 0;
	double movementcap = dt * 15*4;

	double speed = 1;

	double accumulator = 0.0;
	sf::Clock clock;

	//int framenum = 0;
	//int ticknum = 0;

	sf::Font font;
	font.loadFromFile("rsc/munro.ttf");

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::White);
	text.setString("Welcome to snake\nBy Hubert Gonera\n" + versiontag);

	gamewindow.setVerticalSyncEnabled(true);

	bool lost = false;
	bool won = false;
	bool quit = false;

	while (!lost && !won && !quit)
	{
		int temp = 0;;
		sf::Time frameTime = clock.restart();
		accumulator = accumulator + frameTime.asSeconds();

		//std::cout << t << " " << framenum << " " << ticknum << " " << framenum / t << " " << ticknum / t << " " << accumulator << "\n";
		//std::cout << tillmove << " " << snakeheading.first << " " << snakeheading.second <<" "<<snakeparts[0].first<<" "<<snakeparts[0].second<< "\n";

		temp = handleinput(gamewindow);
		if (temp == 2)
		{
			quit = true;
		}

		while (accumulator >= dt)
		{
			//std::cout << "                                                      USED\n";
			temp = simulate(mapstate, t, dt, apple, snakeparts, snakeheading, tillmove, movementcap, speed, text);
			if (temp == 2)
			{
				lost = true;
			}

			accumulator = accumulator - dt;
			t = t + dt;
			//ticknum++;
		}
		//framenum++;
		render(gamewindow, mapstate, apple, snakeparts, speed, text, font);
	}

	score = snakeparts.size();

	if (quit)
	{
		return 0;
	}

	int retcode = -1;

	if (won)
	{
		text.setString("Won!");
		retcode = 1;
	}
	if (lost)
	{
		text.setString("Lost!");
		retcode = 2;
	}

	text.setCharacterSize(60);
	{
		sf::FloatRect textrect = text.getLocalBounds();
		int h = textrect.height;
		int w = textrect.width;
		text.setOrigin(textrect.left + textrect.width / 2.0f, textrect.top + textrect.height / 2.0f);
		text.setPosition(sf::Vector2f(800 / 2.0f, 600 / 2.0f));
	}

	gamewindow.draw(text);
	gamewindow.display();

	sf::Clock endclock;
	sf::Time elapsed;

	elapsed = endclock.getElapsedTime();

	while (elapsed.asSeconds() <= 5)
	{
		sf::Event windowevent;
		while (gamewindow.pollEvent(windowevent))
		{
			if (windowevent.type == sf::Event::Closed)
			{
				return 0;
			}
			if (windowevent.type == sf::Event::KeyReleased)
			{
				if (windowevent.key.code == sf::Keyboard::Enter || windowevent.key.code == sf::Keyboard::Space)
				{
					return retcode;
				}
			}
		}
		elapsed = endclock.getElapsedTime();
	}
	return retcode;

	return -1;
}