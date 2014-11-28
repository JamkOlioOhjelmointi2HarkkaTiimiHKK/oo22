#include "Merge.h"


Merge::Merge()
{
	
	std::string temp; // m‰‰r‰ mappipalojen m‰‰r‰st‰. helvetin hienot "temp" muuttujat
	std::string temp2; //m‰‰r‰ mappien m‰‰r‰st‰
	facts.open("Files\\facts.txt");
	getline(facts, temp);
	getline(facts, temp2);
	numberOfMap = std::stoi(temp2);
	//numberOfPart = std::stoi(temp);//t‰m‰ pit‰‰ korvata jos haluaa vanhan
	facts.close();
	/*
	for (int i = 0; i < numberOfPart+1; i++)
	{
		file.open("Files\\MapPart" + std::to_string(i) + ".txt");
		while (getline(file, line))
		{
			int temp = line.find(" ");
			name = line.substr(0, temp);
			int temp2 = line.find(" ", temp + 1);
			x = line.substr(temp + 1, temp2 - temp - 1);
			int temp3 = line.find("\n", temp2 + 1);
			y = line.substr(temp2 + 1, temp3 - temp2 - 1);
#pragma region vertailu
			if (name.compare("block") == 0)
			{
				mapObjects.push_back(new Block(std::stoi(x), std::stoi(y)));
			}
			else if (name.compare("floor") == 0)
			{
				mapObjects.push_back(new Floor(std::stoi(x), std::stoi(y)));
			}
			else if (name.compare("ladde") == 0)
			{
				mapObjects.push_back(new Ladder(std::stoi(x), std::stoi(y)));
			}
			else if (name.compare("spawP") == 0)
			{
				mapObjects.push_back(new SpawnPoint(std::stoi(x), std::stoi(y)));
			}
			else if (name.compare("spawE") == 0)
			{
				mapObjects.push_back(new SpawnEnemy(std::stoi(x), std::stoi(y)));
			}
#pragma endregion
		}
		parts.push_back(mapObjects);
		file.close();
		mapObjects.clear();
	}
	
	for (int xAkseli = 0; xAkseli < 2; xAkseli++)
	{
		
		for (int yAkseli = 0; yAkseli < 1; yAkseli++)
		{
			std::vector<MapObject*> kamikaze = parts[Utility::random(0, parts.size() - 1)];
			for (unsigned i = 0; i < kamikaze.size(); i++)
			{
				sf::Vector2f tempposition(kamikaze[i]->getPos().x+xAkseli*512, kamikaze[i]->getPos().y+yAkseli*512);
				kamikaze[i]->setPos(tempposition);
				
				std::cout << kamikaze[i]->getPos().x << std::endl;
				
				mapObjects.push_back(kamikaze[i]);			
			}
		}
	}

	for (unsigned i = 0; i < mapObjects.size(); i++)
	{
		std::cout << mapObjects[i]->getName() << " "<<mapObjects[i]->getPos().x << " "<< mapObjects[i]->getPos().y<<std::endl;
	}
	*/
	
	numberOfPart = Utility::random(0, std::stoi(temp));


		for (int xAkseli = 0; xAkseli < 6; xAkseli++)
		{
			for (int yAkseli = 0; yAkseli < 2; yAkseli++)
			{
				file.open("Files\\MapPart" + std::to_string(numberOfPart) + ".txt");
				while (getline(file, line))
				{
					int temp = line.find(" ");
					name = line.substr(0, temp);
					int temp2 = line.find(" ", temp + 1);
					x = line.substr(temp + 1, temp2 - temp - 1);
					int temp3 = line.find("\n", temp2 + 1);
					y = line.substr(temp2 + 1, temp3 - temp2 - 1);
#pragma region vertailu
					if (name.compare("block") == 0)
					{
						mapObjects.push_back(new Block(std::stoi(x) + xAkseli * 512, std::stoi(y) + yAkseli * 512));
					}
					else if (name.compare("floor") == 0)
					{
						mapObjects.push_back(new Floor(std::stoi(x) + xAkseli * 512, std::stoi(y)+yAkseli * 512));
					}
					else if (name.compare("ladde") == 0)
					{
						mapObjects.push_back(new Ladder(std::stoi(x) + xAkseli * 512, std::stoi(y) + yAkseli * 512));
					}
					else if (name.compare("spawP") == 0)
					{
						mapObjects.push_back(new SpawnPoint(std::stoi(x) + xAkseli * 512, std::stoi(y) + yAkseli * 512));
					}
					else if (name.compare("spawE") == 0)
					{
						mapObjects.push_back(new SpawnEnemy(std::stoi(x) + xAkseli * 512, std::stoi(y) + yAkseli * 512));
					}
#pragma endregion
				}
				numberOfPart = Utility::random(0, std::stoi(temp));
				file.close();
			}
		}
		

	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(view);

	save(); // temp. teh‰‰n nappulat
	
}

void Merge::update(float dt)
{
	if (Controls::get()->iskeydown(sf::Keyboard::D))
	{
		position.x += 50*dt;
	}
	if (Controls::get()->iskeydown(sf::Keyboard::A))
	{
		position.x -= 50*dt;
	}
	if (Controls::get()->iskeydown(sf::Keyboard::S))
	{
		position.y += 50*dt;
	}
	if (Controls::get()->iskeydown(sf::Keyboard::W))
	{
		position.y -= 50*dt;
	}
	view.move(position);
	window.setView(view);

}
void Merge::draw()
{
	for (unsigned i = 0; i < mapObjects.size(); ++i)
	{
		window.draw(mapObjects[i]->shape);
	}
}

void Merge::loop(float dt)
{
	update(dt);
	window.clear(sf::Color(0, 0, 0));
	draw();
	window.display();
}

void Merge::save()
{
	file2.open("Files\\Maps\\Map" + std::to_string(numberOfMap) + ".txt");

	for (unsigned i = 0; i < mapObjects.size(); ++i)
	{
		file2 << mapObjects[i]->getName() << " " << mapObjects[i]->getPos().x  << " " << mapObjects[i]->getPos().y<< std::endl;
	}

	file2.close();

	std::string temp;
	facts.open("Files\\facts.txt");
	getline(facts, temp);
	getline(facts, temp);

	if (std::stoi(temp) < numberOfMap)
	{
		facts.seekg(3, std::ios_base::beg);
		facts << numberOfMap;
	}

	facts.close();

	numberOfMap++;
}

Merge::~Merge()
{
	for (unsigned i = 0; i < mapObjects.size(); ++i)
	{
		delete mapObjects[i];
	}
	mapObjects.clear();

	for (unsigned i = 0; i < parts.size(); ++i)
	{
		std::vector<MapObject*> kamikaze = parts[i];
		for (unsigned u = 0; u < kamikaze.size(); ++i)
		{
			delete kamikaze[i];
		}
	}

}
