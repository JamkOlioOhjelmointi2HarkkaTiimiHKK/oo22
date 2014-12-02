#include "Merge.h"


Merge::Merge()
{
	koko = 7;

	halfScreenX = SCREEN_WIDTH / 2;
	halfscreenY = SCREEN_HEIGHT / 2;

#pragma region hyvä
		facts.open("Files\\facts.txt");
	getline(facts, howManuMapParts);
	getline(facts, howManyMaps);
	numberOfMap = std::stoi(howManyMaps);
	numberOfPart = std::stoi(howManuMapParts);
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


	Build(); 
#pragma endregion
	
	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(view);

}

void Merge::Build()
{
	killAll(); // tyhjätään jos reshuflataan

	for (int xAkseli = 0; xAkseli < koko; xAkseli++)
	{
		for (int yAkseli = 0; yAkseli < koko; yAkseli++)
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
		//ylempi on tapa millä pelitilassa piirto + törmäystarkastelut toimii. Keskimmäinen on vaan kätevämpi nopeaan tarkasteluun. Alin on tehokkain
		//if (std::pow(mapObjects[i]->getPos().x - view.getCenter().x,2)-350*70 < std::pow(halfScreenX,2) && std::pow(mapObjects[i]->getPos().y-view.getCenter().y,2)-350*70 < std::pow(halfscreenY,2))		
		//if (mapObjects[i]->getPos().x - view.getCenter().x < halfScreenX && mapObjects[i]->getPos().y-view.getCenter().y < halfscreenY)
		if ((mapObjects[i]->getPos().x - view.getCenter().x)*(mapObjects[i]->getPos().x - view.getCenter().x)  < (halfScreenX + 350)*(halfScreenX + 350) && (mapObjects[i]->getPos().y - view.getCenter().y)*(mapObjects[i]->getPos().y - view.getCenter().y) < (halfscreenY + 350)*(halfscreenY + 350))
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
	kerroinY = 1;
	int temp = 1;

	file2.open("Files\\Maps\\Map" + std::to_string(numberOfMap) + ".txt");

	for (unsigned i = 0; i < mapObjects.size(); ++i)
	{
		if (kerroinY == koko && mapObjects[i]->getPos().x > temp * 512)
		{
			file2 << "--" << std::endl;
			file2 << mapObjects[i]->getName() << " " << mapObjects[i]->getPos().x << " " << mapObjects[i]->getPos().y << std::endl;			
			temp++;
			kerroinY = 1;
		}
		else if (mapObjects[i]->getPos().y > kerroinY * 512)
		{
			file2 << "--" << std::endl;
			file2 << mapObjects[i]->getName() << " " << mapObjects[i]->getPos().x << " " << mapObjects[i]->getPos().y << std::endl;
			kerroinY++;

		}
		else
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
