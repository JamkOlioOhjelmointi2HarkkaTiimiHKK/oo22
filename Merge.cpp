#include "Merge.h"


Merge::Merge()
{
	halfScreenX = SCREEN_WIDTH / 2;
	halfscreenY = SCREEN_HEIGHT / 2;

		facts.open("Files\\facts.txt");
	getline(facts, howManuMapParts);
	getline(facts, howManyMaps);
	numberOfMap = std::stoi(howManyMaps);
	numberOfPart = std::stoi(howManuMapParts);//t‰m‰ pit‰‰ korvata jos haluaa vanhan
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


	Build(); //t‰m‰ on hyv‰ tapa

	//t‰m‰ no huono tapa
	/*
#pragma region huono	
	std::string temp, temp2;

	facts.open("Files\\facts.txt");
	getline(facts, temp);
	getline(facts, temp2);
	numberOfMap = std::stoi(temp);
	numberOfPart = std::stoi(temp2);
	facts.close();

	numberOfPart = Utility::random(0, std::stoi(temp));

	
		for (int xAkseli = 0; xAkseli < 170; xAkseli++)
		{
			for (int yAkseli = 0; yAkseli < 170; yAkseli++)
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
#pragma endregion
		*/
		
	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(view);

}

void Merge::Build()
{
	killAll(); // tyhj‰t‰‰n jos reshuflataan

	for (int xAkseli = 0; xAkseli < 100; xAkseli++)
	{
		for (int yAkseli = 0; yAkseli < 100; yAkseli++)
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
	if (Controls::get()->kIsPressed(sf::Keyboard::Z))
	{
		save();
	}
	if (Controls::get()->kIsPressed(sf::Keyboard::X))
	{
		Build();
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

}
void Merge::draw()
{
	int temp = mapObjects.size();

	for (unsigned i = 0; i < temp; ++i)
	{	
		//ylempi on tapa mill‰ pelitilassa piirto + tˆrm‰ystarkastelut toimii. Keskimm‰inen on vaan k‰tev‰mpi nopeaan tarkasteluun. Alin on tehokkain
		//if (std::pow(mapObjects[i]->getPos().x - view.getCenter().x,2)-350*70 < std::pow(halfScreenX,2) && std::pow(mapObjects[i]->getPos().y-view.getCenter().y,2)-350*70 < std::pow(halfscreenY,2))		
		//if (mapObjects[i]->getPos().x - view.getCenter().x < halfScreenX && mapObjects[i]->getPos().y-view.getCenter().y < halfscreenY)
		if ((mapObjects[i]->getPos().x - view.getCenter().x)*(mapObjects[i]->getPos().x - view.getCenter().x)  < halfScreenX*halfScreenX && (mapObjects[i]->getPos().y - view.getCenter().y)*(mapObjects[i]->getPos().y - view.getCenter().y) < halfscreenY*halfscreenY)
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

	

	facts.open("Files\\facts.txt");
	if (std::stoi(howManyMaps) < numberOfMap)
	{
		facts.seekg(sizeof(numberOfPart), std::ios_base::beg);
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
	mapObjects.clear(); // there's no such a thing as overkill


}

Merge::~Merge()
{
	killAll();
	for (unsigned i = 0; i < parts.size(); ++i)
	for (unsigned i = 0; i < partObjects.size(); ++i)
	{
		delete partObjects[i];
	}
	parts.clear();

}
