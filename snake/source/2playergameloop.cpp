#include "mainheader.h"
#include <chrono>
#include <string>

int twoplayerhandleinput(sf::RenderWindow& gamewindow)
{
	sf::Event windowevent;

	while (gamewindow.pollEvent(windowevent))
	{
		if (windowevent.type == sf::Event::Closed)
		{
			return 2;
		}
		if (windowevent.type == sf::Event::KeyReleased)
		{
			if (windowevent.key.code == sf::Keyboard::Q)
			{
				return 2;
			}
			else if (windowevent.key.code == sf::Keyboard::B)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl))
				{
					return 3;
				}
			}
		}
	}

	return 1;
}

int twoplayerrender(sf::RenderWindow &gamewindow, Mapstate &mapstate, std::pair<int, int>& apple1, std::pair<int, int>& apple2, std::vector<std::pair<int, int>>& snakeparts1,std::pair<int, int>& snakeheading1,
	std::vector<std::pair<int, int>>& snakeparts2,std::pair<int, int>& snakeheading2, sf::Text text, sf::Font font, sf::Text point_text)
{
	mapstate.fillmapstatewithrgb(backgroundcolor.r, backgroundcolor.g, backgroundcolor.b, backgroundcolor.a);

	if (!(apple1.first < 0 || apple1.first > mapstate.mapxsize - 1 || apple1.second < 0 || apple1.second > mapstate.mapysize - 1))
	{
		mapstate.settilecolor(apple1.first, apple1.second, 1);
	}

	if (!(apple2.first < 0 || apple2.first > mapstate.mapxsize - 1 || apple2.second < 0 || apple2.second > mapstate.mapysize - 1))
	{
		mapstate.settilecolor(apple2.first, apple2.second, 1);
	}
	/*
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
	*/
	/*
	for (int i = 1; i < snakeparts.size(); i++)
	{
		double val = abs(abs(255 * sin((i + 50) / 25.f)) - i / 5.f);
		mapstate.settilecolorRGB(snakeparts[i].first, snakeparts[i].second, 25, 25, floor(val), 255);
	}
	*/
	{
		for (int i = 1; i < snakeparts1.size(); i++)
		{
			double valb = abs(abs(255 * sin((3 * i + 70) / 25.f)) - 2 * i / 5.f);
			double valg = abs(abs(255 * cos((3 * i / 3.f + 65) / 25.f)) - 1.5f * i / 5.f);
			double valr = abs(abs(255 * sin((4 * i + 70) / 25.f)) - 2 * i / 5.f);
			mapstate.settilecolorRGB(snakeparts1[i].first, snakeparts1[i].second, floor(valr / 3.5f), floor(valg / 2.f), floor(valb), 255);
		}

		mapstate.settilecolorRGB(snakeparts1[0].first, snakeparts1[0].second, 0, 140, 140, 255);
		mapstate.transfermapstatetoVA(screenreswidth, screenresheight);

		for (int i = 1; i < snakeparts2.size(); i++)
		{
			double valb = abs(abs(255 * sin((3 * i + 70) / 25.f)) - 2 * i / 5.f);
			double valg = abs(abs(255 * cos((3 * i / 3.f + 65) / 25.f)) - 1.5f * i / 5.f);
			double valr = abs(abs(255 * sin((4 * i + 70) / 25.f)) - 2 * i / 5.f);
			valb = 255 - valb;
			valg = 255 - valg;
			valr = 255 - valr;
			mapstate.settilecolorRGB(snakeparts2[i].first, snakeparts2[i].second, floor(valr / 3.5f), floor(valg / 2.f), floor(valb), 255);
		}

		mapstate.settilecolorRGB(snakeparts2[0].first, snakeparts2[0].second, 140, 140, 0, 255);
		mapstate.transfermapstatetoVA(screenreswidth, screenresheight);
	}

	gamewindow.clear();
	gamewindow.draw(mapstate);
	gamewindow.draw(text);
	gamewindow.draw(point_text);
	gamewindow.display();

	return 1;
}

void calcplayer1(Mapstate& mapstate, int t, double dt, std::pair<int,int> &apple1,std::pair<int,int> &apple2, std::vector<std::pair<int, int>> &snakeparts1, std::pair<int, int>& snakeheading1,
	std::vector<std::pair<int, int>> &snakeparts2, std::pair<int, int>& snakeheading2, double& tillmove1,double& tillmove2,const double movementcap, double& speed1, double& speed2, sf::Text& text,
	bool& ate1, bool& wallcollide1,	int& whichappleeaten, int& truesnakesize1, int& truesnakesize2)
{
	if (tillmove1 > movementcap)
	{
		{
			std::pair<int, int> temphead;
			temphead.first = snakeparts1[0].first + snakeheading1.first;
			temphead.second = snakeparts1[0].second + snakeheading1.second;

			if(temphead.first < 0) wallcollide1 = true;
			if(temphead.second < 0) wallcollide1 = true;
			if(temphead.first > mapstate.mapxsize - 1) wallcollide1 = true;
			if(temphead.second > mapstate.mapysize - 1) wallcollide1 = true;

			for (int i = 2; i < snakeparts1.size(); i++)
			{
				if (temphead.first == snakeparts1[i].first && temphead.second == snakeparts1[i].second)
				{
					wallcollide1 = true;
					break;
				}
			}

			for (int i = 0; i < snakeparts2.size(); i++)
			{
				if (temphead.first == snakeparts2[i].first && temphead.second == snakeparts2[i].second)
				{
					wallcollide1 = true;
					break;
				}
			}
		}
		if (!wallcollide1)
		{
			std::pair<int, int> oldhead = snakeparts1[0];
			snakeparts1[0].first += snakeheading1.first;
			snakeparts1[0].second += snakeheading1.second;
			tillmove1 = 0;

			if (snakeparts1[0].first == apple1.first && snakeparts1[0].second == apple1.second)
			{
				ate1 = true;
				whichappleeaten = 1;
			}
			if (snakeparts1[0].first == apple2.first && snakeparts1[0].second == apple2.second)
			{
				ate1 = true;
				whichappleeaten = 2;
			}

			if (!ate1)
			{
				if (snakeparts1.size() > 1)
				{
					mapstate.settilecolor(snakeparts1[snakeparts1.size() - 1].first, snakeparts1[snakeparts1.size() - 1].second, 0);
				}
				else
				{
					mapstate.settilecolor(oldhead.first, oldhead.second, 0);
				}

			}
			for (int i = 1; i < snakeparts1.size(); i++)
			{
				std::pair<int, int> temppart = snakeparts1[i];
				snakeparts1[i] = oldhead;
				oldhead = temppart;
			}
			if (ate1)
			{
				if(whichappleeaten == 1)
				{
					apple1.first = -1;
					apple1.second = -1;
				}
				if(whichappleeaten == 2)
				{
					apple2.first = -1;
					apple2.second = -1;
				}

				//V1.1.0.0 speed = speed + ((snakeparts.size() + 3) / snakeparts.size() - snakeparts.size() / 100) * 0.05;

				speed1 = (-pow((0.013 * truesnakesize1), 2)) + (truesnakesize1 / 25.0f) + 1.0f;

				snakeparts1.push_back(oldhead);
			}
		}
	}
}

void calcplayer2(Mapstate& mapstate, int t, double dt, std::pair<int,int> &apple1,std::pair<int,int> &apple2, std::vector<std::pair<int, int>> &snakeparts1, std::pair<int, int>& snakeheading1,
	std::vector<std::pair<int, int>> &snakeparts2, std::pair<int, int>& snakeheading2, double& tillmove1,double& tillmove2,const double movementcap, double& speed1, double& speed2, sf::Text& text,
	bool& ate2, bool& wallcollide2,	int& whichappleeaten, int& truesnakesize1, int& truesnakesize2)
{
	if (tillmove2 > movementcap)
	{
		{
			std::pair<int, int> temphead;
			temphead.first = snakeparts2[0].first + snakeheading2.first;
			temphead.second = snakeparts2[0].second + snakeheading2.second;

			if(temphead.first < 0) wallcollide2 = true;
			if(temphead.second < 0) wallcollide2 = true;
			if(temphead.first > mapstate.mapxsize - 1) wallcollide2 = true;
			if(temphead.second > mapstate.mapysize - 1) wallcollide2 = true;

			for (int i = 2; i < snakeparts2.size(); i++)
			{
				if (temphead.first == snakeparts2[i].first && temphead.second == snakeparts2[i].second)
				{
					wallcollide2 = true;
					break;
				}
			}

			for (int i = 0; i < snakeparts1.size(); i++)
			{
				if (temphead.first == snakeparts1[i].first && temphead.second == snakeparts1[i].second)
				{
					wallcollide2 = true;
					break;
				}
			}
		}
		if (!wallcollide2)
		{
			std::pair<int, int> oldhead = snakeparts2[0];
			snakeparts2[0].first += snakeheading2.first;
			snakeparts2[0].second += snakeheading2.second;
			tillmove2 = 0;

			if (snakeparts2[0].first == apple1.first && snakeparts2[0].second == apple1.second)
			{
				ate2 = true;
				whichappleeaten = 1;
			}
			if (snakeparts2[0].first == apple2.first && snakeparts2[0].second == apple2.second)
			{
				ate2 = true;
				whichappleeaten = 2;
			}

			if (!ate2)
			{
				if (snakeparts2.size() > 1)
				{
					mapstate.settilecolor(snakeparts2[snakeparts2.size() - 1].first, snakeparts2[snakeparts2.size() - 1].second, 0);
				}
				else
				{
					mapstate.settilecolor(oldhead.first, oldhead.second, 0);
				}

			}
			for (int i = 1; i < snakeparts2.size(); i++)
			{
				std::pair<int, int> temppart = snakeparts2[i];
				snakeparts2[i] = oldhead;
				oldhead = temppart;
			}
			if (ate2)
			{
				if(whichappleeaten == 1)
				{
					apple1.first = -1;
					apple1.second = -1;
				}
				if(whichappleeaten == 2)
				{
					apple2.first = -1;
					apple2.second = -1;
				}

				//V1.1.0.0 speed = speed + ((snakeparts.size() + 3) / snakeparts.size() - snakeparts.size() / 100) * 0.05;

				speed2 = (-pow((0.013 * truesnakesize2), 2)) + (truesnakesize2 / 25.0f) + 1.0f;

				snakeparts2.push_back(oldhead);
			}
		}
	}
}

int twoplayersimulate(Mapstate& mapstate, int t, double dt, std::pair<int,int> &apple1,std::pair<int,int> &apple2, std::vector<std::pair<int, int>> &snakeparts1, std::pair<int, int>& snakeheading1,
	std::vector<std::pair<int, int>> &snakeparts2, std::pair<int, int>& snakeheading2, double& tillmove1,double& tillmove2,const double movementcap, double& speed1, double& speed2, sf::Text& text)
{
	if (apple1.first == -1)
	{
		bool found = false;
		while (!found)
		{
			apple1.first = rand() % mapstate.mapxsize;
			apple1.second = rand() % mapstate.mapysize;
			
			bool checking = true;
			for (int i = 0; i < snakeparts1.size(); i++)
			{
				if ((apple1.first == snakeparts1[i].first && apple1.second == snakeparts1[i].second))
				{
					checking = false;
					break;
				}
			}
			for (int i = 0; i < snakeparts2.size(); i++)
			{
				if ((apple1.first == snakeparts2[i].first && apple1.second == snakeparts2[i].second))
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

	if (apple2.first == -1)
	{
		bool found = false;
		while (!found)
		{
			apple2.first = rand() % mapstate.mapxsize;
			apple2.second = rand() % mapstate.mapysize;
			
			bool checking = true;
			for (int i = 0; i < snakeparts1.size(); i++)
			{
				if ((apple2.first == snakeparts1[i].first && apple2.second == snakeparts1[i].second))
				{
					checking = false;
					break;
				}
			}
			for (int i = 0; i < snakeparts2.size(); i++)
			{
				if ((apple2.first == snakeparts2[i].first && apple2.second == snakeparts2[i].second))
				{
					checking = false;
					break;
				}
			}
			if(apple2.first == apple1.first && apple2.second == apple1.second)
			{
				checking = false;
			}
			if (checking)
			{
				found = true;
			}
		}
	}

	int truesnakesize1 = snakeparts1.size() + 1;
	int truesnakesize2 = snakeparts2.size() + 1;

	{
		int right = 0;
		int up = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			up = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			up = -1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			right = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			right = -1;
		}

		if (right == 1)
		{
			if (snakeparts1.size() > 1)
			{
				if (snakeparts1[0].first >= snakeparts1[1].first)
				{
					snakeheading1.first = 1;
					snakeheading1.second = 0;
				}
			}
			else {
				snakeheading1.first = 1;
				snakeheading1.second = 0;
			}
		}
		if (right == -1)
		{
			if (snakeparts1.size() > 1)
			{
				if (snakeparts1[0].first <= snakeparts1[1].first)
				{
					snakeheading1.first = -1;
					snakeheading1.second = 0;
				}
			}
			else {
				snakeheading1.first = -1;
				snakeheading1.second = 0;
			}
		}
		if (up == 1)
		{
			if (snakeparts1.size() > 1)
			{
				if (snakeparts1[0].second <= snakeparts1[1].second)
				{
					snakeheading1.first = 0;
					snakeheading1.second = -1;
				}
			}
			else {
				snakeheading1.first = 0;
				snakeheading1.second = -1;
			}
		}
		if (up == -1)
		{
			if (snakeparts1.size() > 1)
			{
				if (snakeparts1[0].second >= snakeparts1[1].second)
				{
					snakeheading1.first = 0;
					snakeheading1.second = 1;
				}
			}
			else {
				snakeheading1.first = 0;
				snakeheading1.second = 1;
			}
		}
	}

	{
		int right = 0;
		int up = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			up = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			up = -1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			right = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			right = -1;
		}

		if (right == 1)
		{
			if (snakeparts2.size() > 1)
			{
				if (snakeparts2[0].first >= snakeparts2[1].first)
				{
					snakeheading2.first = 1;
					snakeheading2.second = 0;
				}
			}
			else {
				snakeheading2.first = 1;
				snakeheading2.second = 0;
			}
		}
		if (right == -1)
		{
			if (snakeparts2.size() > 1)
			{
				if (snakeparts2[0].first <= snakeparts2[1].first)
				{
					snakeheading2.first = -1;
					snakeheading2.second = 0;
				}
			}
			else {
				snakeheading2.first = -1;
				snakeheading2.second = 0;
			}
		}
		if (up == 1)
		{
			if (snakeparts2.size() > 1)
			{
				if (snakeparts2[0].second <= snakeparts2[1].second)
				{
					snakeheading2.first = 0;
					snakeheading2.second = -1;
				}
			}
			else {
				snakeheading2.first = 0;
				snakeheading2.second = -1;
			}
		}
		if (up == -1)
		{
			if (snakeparts2.size() > 1)
			{
				if (snakeparts2[0].second >= snakeparts2[1].second)
				{
					snakeheading2.first = 0;
					snakeheading2.second = 1;
				}
			}
			else {
				snakeheading2.first = 0;
				snakeheading2.second = 1;
			}
		}
	}

	tillmove1 = tillmove1 + dt*speed1;
	tillmove2 = tillmove2 + dt*speed2;

	bool ate1 = false;
	bool wallcollide1 = false;

	int whichappleeaten = 1;
	
	bool ate2 = false;
	bool wallcollide2 = false;

	if(truesnakesize1 > 2 || truesnakesize2 > 2)
	{
		std::string speedstring1 = std::to_string(speed1);
		speedstring1 = speedstring1.substr(0, 4);

		std::string speedstring2 = std::to_string(speed2);
		speedstring2 = speedstring2.substr(0, 4);

		text.setString("Arrows (P1): " + std::to_string(truesnakesize1-1) + " Speed:" + speedstring1 + "\nWASD (P2): " + std::to_string(truesnakesize2-1) + " Speed:" + speedstring2);
	}

	if(rand()%2 == 0)
	{
		calcplayer1(mapstate, t, dt, apple1, apple2, snakeparts1, snakeheading1, snakeparts2, snakeheading2, tillmove1,tillmove2, movementcap, speed1,speed2, text, ate1, wallcollide1, whichappleeaten, truesnakesize1, truesnakesize2);
		calcplayer2(mapstate, t, dt, apple1, apple2, snakeparts1, snakeheading1, snakeparts2, snakeheading2, tillmove1,tillmove2, movementcap, speed1,speed2, text, ate2, wallcollide2, whichappleeaten, truesnakesize1, truesnakesize2);	
	} else {
		calcplayer2(mapstate, t, dt, apple1, apple2, snakeparts1, snakeheading1, snakeparts2, snakeheading2, tillmove1,tillmove2, movementcap, speed1,speed2, text, ate2, wallcollide2, whichappleeaten, truesnakesize1, truesnakesize2);
		calcplayer1(mapstate, t, dt, apple1, apple2, snakeparts1, snakeheading1, snakeparts2, snakeheading2, tillmove1,tillmove2, movementcap, speed1,speed2, text, ate1, wallcollide1, whichappleeaten, truesnakesize1, truesnakesize2);	
	}
	

	if(wallcollide1 == wallcollide2 && wallcollide1 == 1 && wallcollide2 == 1)
	{
		return rand()%2+1;
	}

	if (wallcollide1)
	{
		return 1;
	}

	if (wallcollide2)
	{
		return 2;
	}

	return 0;
}

int twoplayerscreenloopandinit(sf::RenderWindow& gamewindow, sf::Font font, int& player1points, int& player2points)
{
	Mapstate mapstate(16, 12);

	std::vector<std::pair<int, int>> snakeparts1;
	std::pair<int, int> snakeheading1 = { -1,0 }; //speed vector in tiles per second
	snakeparts1.push_back({ 15, 11 });

	std::vector<std::pair<int, int>> snakeparts2;
	std::pair<int, int> snakeheading2 = { 1,0 }; //speed vector in tiles per second
	snakeparts2.push_back({ 0,0 });

	std::pair<int, int> apple1 = { -1, -1 };
	std::pair<int, int> apple2 = { -1, -1 };

	double t = 0.0;
	const double dt = 1 / (128.0f);

	double tillmove1 = 0;
	double tillmove2 = 0;
	const double movementcap = (1 / 64.0f) * 15;

	/*
	const double dt = (1.0 / 64.0) / 4;
	0.00390625

	movement cap 0.234375

	double tillmove = 0;
	double movementcap = dt * 15*4;
	*/

	double speed1 = 1.0;
	double speed2 = 1.0;

	double accumulator = 0.0;
	sf::Clock clock;

	//int framenum = 0;
	//int ticknum = 0;

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(TORELXPOS(20));
	text.setFillColor(sf::Color::White);
	text.setString("Welcome to snake TWO PLAYER MODE!\nBy Hubert Gonera\n" + versiontag);

	sf::Text point_text;
	point_text.setFont(font);
	point_text.setCharacterSize(TORELXPOS(20));
	point_text.setFillColor(sf::Color::White);
	point_text.setString(std::to_string(player2points) + ":" + std::to_string(player1points));
	point_text.setPosition(TORELXPOS(400),TORELYPOS(560));

	gamewindow.setVerticalSyncEnabled(true);

	int playerwhowon = -1;
	bool quit = false;
	bool backtomenu = false;

	while (playerwhowon == -1 && !quit && !backtomenu)
	{
		int temp = 0;;
		sf::Time frameTime = clock.restart();
		accumulator = accumulator + frameTime.asSeconds();

		//std::cout << t << " " << framenum << " " << ticknum << " " << framenum / t << " " << ticknum / t << " " << accumulator << "\n";
		//std::cout << tillmove << " " << snakeheading.first << " " << snakeheading.second <<" "<<snakeparts[0].first<<" "<<snakeparts[0].second<< "\n";

		temp = twoplayerhandleinput(gamewindow);
		if (temp == 2)
		{
			quit = true;
		}
		if (temp == 3)
		{
			backtomenu = true;
		}

		while (accumulator >= dt)
		{
			//std::cout << "                                                      USED\n";
			temp = twoplayersimulate(mapstate, t, dt, apple1, apple2, snakeparts1, snakeheading1, snakeparts2, snakeheading2, tillmove1,tillmove2, movementcap, speed1,speed2, text);
			if (temp == 1)
			{
				playerwhowon = 2;
			}
			if (temp == 2)
			{
				playerwhowon = 1;
			}

			accumulator = accumulator - dt;
			t = t + dt;
			//ticknum++;
		}
		//framenum++;
		twoplayerrender(gamewindow, mapstate, apple1, apple2, snakeparts1 ,snakeheading1, snakeparts2, snakeheading2, text, font, point_text);
	}

	if (quit)
	{
		return 0;
	}

	if (backtomenu)
	{
		return 3;
	}

	int retcode = -1;

	if (playerwhowon == 1)
	{
		text.setString("Player 1 won!");
		player1points++;
		retcode = 1;
	}
	if (playerwhowon == 2)
	{
		text.setString("Player 2 won!");
		player2points++;
		retcode = 1;
	}

	text.setCharacterSize(TORELXPOS(60));
	{
		sf::FloatRect textrect = text.getLocalBounds();
		int h = textrect.height;
		int w = textrect.width;
		text.setOrigin(textrect.left + textrect.width / 2.0f, textrect.top + textrect.height / 2.0f);
		text.setPosition(sf::Vector2f(TORELXPOS(400), TORELYPOS(300)));
	}

	gamewindow.draw(text);
	gamewindow.display();

	sf::Clock endclock;
	sf::Time elapsed;

	elapsed = endclock.getElapsedTime();

	bool go = false;

	while (elapsed.asSeconds() <= 7 && !go)
	{
		sf::Event windowevent;
		while (gamewindow.pollEvent(windowevent))
		{
			if (windowevent.type == sf::Event::Closed)
			{
				retcode = 0;
				go = true;
			}
			if (windowevent.type == sf::Event::KeyReleased)
			{
				if (windowevent.key.code == sf::Keyboard::Enter)
				{
					go = true;
				}
				if (windowevent.key.code == sf::Keyboard::Space)
				{
					go = true;
				}
				if (windowevent.key.code == sf::Keyboard::Q)
				{
					retcode = 0;
					go = true;
				}
			}
		}
		elapsed = endclock.getElapsedTime();
	}

	if (retcode == 0)
	{
		return retcode;
	}

	bool quitgame = false;

	return retcode;
}