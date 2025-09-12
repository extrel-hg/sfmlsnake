#include "mainheader.h"
#include "mainmenuheader.h"

int recalcleaderboardmenu(Button& backtomenubutton,Button& amountofhighscores, Button& highscoreframe, Button& downbutton, Button& upbutton, Button& shownhighscores, Button& changesorting)
{
	backtomenubutton.recalculatepos({ TORELXPOS(100),TORELYPOS(35) }, { TORELXPOS(180),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));
	amountofhighscores.recalculatepos({ TORELXPOS(100+180+10+20),TORELYPOS(35) }, { TORELXPOS(220),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));
	highscoreframe.recalculatepos({ TORELXPOS(400),TORELYPOS(300 + (35 + 20) / 2) }, { TORELXPOS(800 - 20),TORELYPOS(600 - 35 - 10 - 10 - 20) }, TORELXPOS(5));

	changesorting.recalculatepos({ TORELXPOS(700),TORELYPOS(35) }, { TORELXPOS(180),TORELYPOS(50) }, TORELXPOS(5), TORELXPOS(25));

	downbutton.recalculatepos({ TORELXPOS(757.5),TORELYPOS(100+38*12) }, { TORELXPOS(35),TORELYPOS(35) }, TORELXPOS(5), TORELXPOS(15));
	upbutton.recalculatepos({ TORELXPOS(757.5),TORELYPOS(100 + 38 * 0) }, { TORELXPOS(35),TORELYPOS(35) }, TORELXPOS(5), TORELXPOS(15));
	shownhighscores.recalculatepos({ TORELXPOS(757.5),TORELYPOS((100 + 38 * 0 + 100 + 38*12)/2) }, { TORELXPOS(35),TORELYPOS(35) }, TORELXPOS(0), TORELXPOS(15));

	return 1;
}

void loadandsort_leaderboard(std::vector<Button>& highscorebuttonsname, std::vector<Button>& highscorebuttonstag, std::vector<Button>& highscorebuttonshighscore,std::vector <std::pair<int, std::string>>& highscores, std::vector<std::string>& highscorenames, sf::Font font, int sort = 0) //0-by highscore, decreasing; 1-increasing 2- by name A-Z, 3-Z-A   4-By version tag decreasing, increasing
{
	highscorebuttonshighscore.clear();
	highscorebuttonstag.clear();
	highscorebuttonsname.clear();
	if(sort == 0 || sort == 1)
	{
		bool sorted = false;
		while(!sorted)
		{
			bool did_a_swap = false;
			for(int i = 1; i < highscores.size(); i++)
			{
				std::pair<int, std::string> temp = highscores[i];
				std::string tempstring = highscorenames[i];
				if(sort == 0)
				{
					if(highscores[i].first > highscores[i-1].first)
					{
						highscores[i] = highscores[i-1];
						highscores[i-1] = temp;
						highscorenames[i] = highscorenames[i-1];
						highscorenames[i-1] = tempstring;
						did_a_swap = true;
					}
				}
				if(sort == 1)
				{
					if(highscores[i].first < highscores[i-1].first)
					{
						highscores[i] = highscores[i-1];
						highscores[i-1] = temp;
						highscorenames[i] = highscorenames[i-1];
						highscorenames[i-1] = tempstring;
						did_a_swap = true;
					}
				}
				if(highscores[i].first == highscores[i-1].first)
				{
					if(highscorenames[i] < highscorenames[i-1])
					{
						highscores[i] = highscores[i-1];
						highscores[i-1] = temp;
						highscorenames[i] = highscorenames[i-1];
						highscorenames[i-1] = tempstring;
						did_a_swap = true;
					}
				}
			}
			if(!did_a_swap) sorted = true;
		}
	}

	if(sort == 2 || sort == 3)
	{
		bool sorted = false;
		while(!sorted)
		{
			bool did_a_swap = false;
			for(int i = 1; i < highscores.size(); i++)
			{
				std::pair<int, std::string> temp = highscores[i];
				std::string tempstring = highscorenames[i];
				if(sort == 3)
				{
					if(highscorenames[i] > highscorenames[i-1])
					{
						highscores[i] = highscores[i-1];
						highscores[i-1] = temp;
						highscorenames[i] = highscorenames[i-1];
						highscorenames[i-1] = tempstring;
						did_a_swap = true;
					}
				}
				if(sort == 2)
				{
					if(highscorenames[i] < highscorenames[i-1])
					{
						highscores[i] = highscores[i-1];
						highscores[i-1] = temp;
						highscorenames[i] = highscorenames[i-1];
						highscorenames[i-1] = tempstring;
						did_a_swap = true;
					}
				}
				if(highscorenames[i] == highscorenames[i-1])
				{
					if(highscores[i].first > highscores[i-1].first)
					{
						highscores[i] = highscores[i-1];
						highscores[i-1] = temp;
						highscorenames[i] = highscorenames[i-1];
						highscorenames[i-1] = tempstring;
						did_a_swap = true;
					}
				}
			}
			if(!did_a_swap) sorted = true;
		}
	}

	if(sort == 4 || sort == 5)
	{
		bool sorted = false;
		while(!sorted)
		{
			bool did_a_swap = false;
			for(int i = 1; i < highscores.size(); i++)
			{
				std::pair<int, std::string> temp = highscores[i];
				std::string tempstring = highscorenames[i];

				std::string temptagstring = highscores[i].second;
				std::reverse(temptagstring.begin(), temptagstring.end());
				size_t pos = temptagstring.find(';');
				temptagstring = temptagstring.substr(0, pos);
				std::reverse(temptagstring.begin(), temptagstring.end());

				std::string temptagstring_prev = highscores[i-1].second;
				std::reverse(temptagstring_prev.begin(), temptagstring_prev.end());
				pos = temptagstring_prev.find(';');
				temptagstring_prev= temptagstring_prev.substr(0, pos);
				std::reverse(temptagstring_prev.begin(), temptagstring_prev.end());

				if(sort == 4)
				{
					if(temptagstring > temptagstring_prev)
					{
						highscores[i] = highscores[i-1];
						highscores[i-1] = temp;
						highscorenames[i] = highscorenames[i-1];
						highscorenames[i-1] = tempstring;
						did_a_swap = true;
					}
				}
				if(sort == 5)
				{
					if(temptagstring < temptagstring_prev)
					{
						highscores[i] = highscores[i-1];
						highscores[i-1] = temp;
						highscorenames[i] = highscorenames[i-1];
						highscorenames[i-1] = tempstring;
						did_a_swap = true;
					}
				}
				if(temptagstring==temptagstring_prev)
				{
					if(highscores[i].first > highscores[i-1].first)
					{
						highscores[i] = highscores[i-1];
						highscores[i-1] = temp;
						highscorenames[i] = highscorenames[i-1];
						highscorenames[i-1] = tempstring;
						did_a_swap = true;
					}
				}
			}
			if(!did_a_swap) sorted = true;
		}
	}

	for (int i = 0; i < highscores.size(); i++)
	{
		highscorebuttonsname.push_back(Button(font, highscorenames[i], { TORELXPOS(370 / 2 + 25),TORELYPOS(100 + (35 + 3) * i) }, { TORELXPOS(370),TORELYPOS(35) }, TORELXPOS(5), TORELXPOS(25)));
		highscorebuttonshighscore.push_back(Button(font, std::to_string(highscores[i].first), { TORELXPOS(370 + 25 + 90 / 2 - 5),TORELYPOS(100 + (35 + 3) * i) }, { TORELXPOS(90),TORELYPOS(35) }, TORELXPOS(5), TORELXPOS(25)));
		std::string temptagstring = highscores[i].second;
		std::reverse(temptagstring.begin(), temptagstring.end());
		size_t pos = temptagstring.find(';');
		if (pos == std::string::npos)
		{
			highscorebuttonsname.pop_back();
			highscorebuttonshighscore.pop_back();
			continue;
		}
		else {
			temptagstring = temptagstring.substr(0, pos);
			//std::cout<<highscorenames[i]<<" "<<std::to_string(highscores[i].first)<<" "<<temptagstring<<"\n";
			std::reverse(temptagstring.begin(), temptagstring.end());
		}
		highscorebuttonstag.push_back(Button(font, temptagstring, { TORELXPOS(370 + 25 + 90 - 10 + 250 / 2),TORELYPOS(100 + (35 + 3) * i) }, { TORELXPOS(250),TORELYPOS(35) }, TORELXPOS(5), TORELXPOS(25)));
	}
}

int leaderboardmenu(sf::RenderWindow& gamewindow, sf::Font font, std::vector <std::pair<int, std::string>> highscores, std::vector <std::string> highscorenames)
{
	gamewindow.clear();

	bool quitfull = false;

	int drawto = 13;
	int drawfrom = 0;
	int sorting_type = 0;

	Button backtomenubutton(font, "Back to menu");
	Button amountofhighscores(font);
	Button highscoreframe(font,"");
	Button changesorting(font, "'S' to change");

	Button downbutton(font, "\\/");
	Button upbutton(font, "/\\");
	Button shownhighscores(font, "NULL");

	std::vector<Button> highscorebuttonsname;
	std::vector<Button> highscorebuttonshighscore;
	std::vector<Button> highscorebuttonstag;

	loadandsort_leaderboard(highscorebuttonsname,highscorebuttonstag,highscorebuttonshighscore,highscores,highscorenames,font,sorting_type);

	amountofhighscores.buttonstring = "No. highscores:" + std::to_string(highscores.size());
	amountofhighscores.buttontextupdate();

	recalcleaderboardmenu(backtomenubutton, amountofhighscores, highscoreframe,downbutton,upbutton,shownhighscores,changesorting);
	int extra_scrolls = 0;

	while (!quitfull)
	{
		sf::Event windowevent;
		while (gamewindow.pollEvent(windowevent))
		{
			bool backtomenu = false;
			bool quitgame = false;
			bool resetwindow = false;
			bool goup = false;
			bool godown = false;
			bool changesorting_now = false;
			int amountofscrollticks = 0;
			if (windowevent.type == sf::Event::Closed)
			{
				quitgame = true;
			}
			if (windowevent.type == sf::Event::MouseWheelMoved)
			{
				amountofscrollticks = windowevent.mouseWheel.delta;
				if(amountofscrollticks > 0)
				{
					goup = true;
				}
				else if (amountofscrollticks < 0)
				{
					godown = true;
					amountofscrollticks = -amountofscrollticks;
				}
			}
			if (windowevent.type == sf::Event::MouseButtonReleased)
			{
				if (backtomenubutton.arethosethisbuttoncords({ sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y }))
				{
					backtomenu = true;
				}
				if (downbutton.arethosethisbuttoncords({ sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y }))
				{
					godown = true;
				}
				if (upbutton.arethosethisbuttoncords({ sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y }))
				{
					goup = true;
				}
				if (changesorting.arethosethisbuttoncords({sf::Mouse::getPosition(gamewindow).x,sf::Mouse::getPosition(gamewindow).y}))
				{
					changesorting_now = true;
				}
			}
			if (windowevent.type == sf::Event::KeyReleased)
			{
				if (windowevent.key.code == sf::Keyboard::Q)
				{
					quitgame = true;
				}
				else if (windowevent.key.code == sf::Keyboard::B)
				{
					backtomenu = true;
				}
				else if (windowevent.key.code == sf::Keyboard::Up)
				{
					goup = true;
				}
				else if (windowevent.key.code == sf::Keyboard::Down)
				{
					godown = true;
				}
				else if (windowevent.key.code == sf::Keyboard::F)
				{
					if(extra_scrolls==0)
					{
						extra_scrolls=highscorebuttonsname.size()/10;
					} 
					else if(extra_scrolls!=0)
					{
						extra_scrolls=0;
					}
				} else if (windowevent.key.code == sf::Keyboard::S)
				{
					changesorting_now = true;
				}
			}

			if (godown)
			{
				for(int i = 0; i <= amountofscrollticks+extra_scrolls; i++)
				{
					if (highscorebuttonsname.size() > 13)
					{
						if (drawto < highscorebuttonsname.size())
						{
							drawfrom++;
							drawto++;
						}
					}
				}
			}

			if (goup)
			{
				for(int i = 0; i <= amountofscrollticks+extra_scrolls; i++)
				{
					if (highscorebuttonsname.size() > 13)
					{
						if (drawfrom > 0)
						{
							drawfrom--;
							drawto--;
						}
					}
				}
			}

			if (quitgame || backtomenu)
			{

			}

			if (quitgame)
			{
				return 0;
			}

			if (backtomenu)
			{
				return 1;
			}

			if(changesorting_now)
			{
				sorting_type++;
				if(sorting_type > 5) sorting_type = 0;
				std::string tempstring;
				if(sorting_type == 0) tempstring = "Score \\/";
				if(sorting_type == 1) tempstring = "Score /\\";
				if(sorting_type == 2) tempstring = "Name \\/";
				if(sorting_type == 3) tempstring = "Name /\\";
				if(sorting_type == 4) tempstring = "Version \\/";
				if(sorting_type == 5) tempstring = "Version /\\";
				changesorting.buttonstring = tempstring;
				changesorting.buttontextupdate();
				loadandsort_leaderboard(highscorebuttonsname,highscorebuttonstag,highscorebuttonshighscore,highscores,highscorenames,font,sorting_type);
			}
		}

		gamewindow.clear(backgroundcolor);
		gamewindow.draw(backtomenubutton);
		gamewindow.draw(amountofhighscores);
		gamewindow.draw(highscoreframe);
		gamewindow.draw(changesorting);	
		sf::Transform buttonoffset;
		buttonoffset.translate(sf::Vector2f(0, -TORELYPOS(38 * drawfrom)));
		for (int i = drawfrom; i < drawto && i < highscorebuttonsname.size(); i++)
		{
			if (highscorebuttonsname.size() > 0 && highscorebuttonshighscore.size() > 0 && highscorebuttonstag.size() > 0)
			{
				Button tempbutton = highscorebuttonsname[i];
				tempbutton.buttontextupdate();
				gamewindow.draw(tempbutton, buttonoffset);
				
				tempbutton = highscorebuttonshighscore[i];
				tempbutton.buttontextupdate();
				gamewindow.draw(tempbutton, buttonoffset);
				
				tempbutton = highscorebuttonstag[i];
				tempbutton.buttontextupdate();
				gamewindow.draw(tempbutton, buttonoffset);
			}
		}
		gamewindow.draw(upbutton);
		gamewindow.draw(downbutton);

		{
			std::string range;

			if (highscorebuttonsname.size() == 0)
			{
				range = "0-0";
			}
			else if (highscorebuttonsname.size() < 14)
			{
				range = "1-" + std::to_string(highscorebuttonsname.size());
			}
			else {
				range = std::to_string(drawfrom + 1) + "-" + std::to_string(drawto);
			}

			shownhighscores.buttonstring = range;
		}
		shownhighscores.buttontextupdate();

		gamewindow.draw(shownhighscores);
		gamewindow.display();
	}
	return -1;
}