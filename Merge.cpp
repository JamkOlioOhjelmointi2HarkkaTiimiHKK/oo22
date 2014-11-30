#include "Merge.h"


Merge::Merge()
{
	halfScreenX = SCREEN_WIDTH / 2;
	halfscreenY = SCREEN_HEIGHT / 2;

	openAndBuild(); //tämä on hyvä tapa

	//tämä no huono tapa
	/*
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
		*/

	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(view);

	buttons.push_back(new Button(sf::Vector2f(100, 50), sf::Vector2f(800, 470), "save", [&]()
	{
		save();

	}));
	buttons.push_back(new Button(sf::Vector2f(100, 50), sf::Vector2f(950, 470), "reShufle", [&]()
	{
		openAndBuild();

	}));
}

void Merge::openAndBuild()
{
	killAll(); // tyhjätään jos reshuflataan

	facts.open("Files\\facts.txt");
	getline(facts, howManuMapParts);
	getline(facts, howManyMaps);
	numberOfMap = std::stoi(howManyMaps);
	numberOfPart = std::stoi(howManuMapParts);//tämä pitää korvata jos haluaa vanhan
	facts.close();

	for (int i = 0; i < numberOfPart + 1; i++)
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
				partObjects.push_back(new Block(std::stoi(x), std::stoi(y)));
			}
			else if (name.compare("floor") == 0)
			{
				partObjects.push_back(new Floor(std::stoi(x), std::stoi(y)));
			}
			else if (name.compare("ladde") == 0)
			{
				partObjects.push_back(new Ladder(std::stoi(x), std::stoi(y)));
			}
			else if (name.compare("spawP") == 0)
			{
				partObjects.push_back(new SpawnPoint(std::stoi(x), std::stoi(y)));
			}
			else if (name.compare("spawE") == 0)
			{
				partObjects.push_back(new SpawnEnemy(std::stoi(x), std::stoi(y)));
			}
#pragma endregion
		}
		parts.push_back(partObjects);
		file.close();
		partObjects.clear();
	}

	for (int xAkseli = 0; xAkseli < 9; xAkseli++)
	{
		for (int yAkseli = 0; yAkseli < 9; yAkseli++)
		{
			std::vector<MapObject*> kamikaze = parts[Utility::random(0, parts.size() - 1)];
			for (unsigned i = 0; i < kamikaze.size(); i++)
			{
				MapObject* temp = new MapObject(*kamikaze[i]);
				sf::Vector2f tempposition(kamikaze[i]->getPos().x + xAkseli * 512, kamikaze[i]->getPos().y + yAkseli * 512);
				temp->setPos(tempposition);
				mapObjects.push_back(temp);
			}
		}
	}



}

void Merge::update(float dt)
{
	position.x = 0;
	position.y = 0;

	if (Controls::get()->iskeydown(sf::Keyboard::D))
	{
		position.x += 500*dt;
	}
	if (Controls::get()->iskeydown(sf::Keyboard::A))
	{
		position.x -= 500*dt;
	}
	if (Controls::get()->iskeydown(sf::Keyboard::S))
	{
		position.y += 500*dt;
	}
	if (Controls::get()->iskeydown(sf::Keyboard::W))
	{
		position.y -= 500*dt;
	}
	if (Controls::get()->mIsPressed(sf::Mouse::Button::Middle))
	{
		view.zoom(2);
	}
	if (Controls::get()->mIsPressed(sf::Mouse::Button::Right))
	{
		view.zoom(0.5);
	}
	view.move(position);
	window.setView(view);

	for (unsigned i = 0; i < buttons.size(); ++i)
	{
		buttons[i]->update();
	}

}
void Merge::draw()
{
	int temp = mapObjects.size();

	for (unsigned i = 0; i < temp; ++i)
	{	
		//if (std::pow(mapObjects[i]->getPos().x - view.getCenter().x,2)-350*70 < std::pow(halfScreenX,2) && std::pow(mapObjects[i]->getPos().y-view.getCenter().y,2)-350*70 < std::pow(halfscreenY,2))
		if (mapObjects[i]->getPos().x - view.getCenter().x < halfScreenX && mapObjects[i]->getPos().y-view.getCenter().y < halfscreenY)
		window.draw(mapObjects[i]->shape);
	}

	for (unsigned i = 0; i < buttons.size(); ++i)
	{
		buttons[i]->draw();
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
	getline(facts, howManyMaps);

	if (std::stoi(howManyMaps) < numberOfMap)
	{
		facts.seekg(3, std::ios_base::beg);
		facts << numberOfMap;
	}

	facts.close();

	numberOfMap++;
}

void Merge::killAll()
{
	for (unsigned i = 0; i < mapObjects.size(); ++i)
	{
		delete mapObjects[i];
	}
	mapObjects.clear();

	for (unsigned i = 0; i < parts.size(); ++i)
	for (unsigned i = 0; i < partObjects.size(); ++i)
	{
		delete partObjects[i];
	}
	parts.clear();

}

Merge::~Merge()
{
	killAll();
}
