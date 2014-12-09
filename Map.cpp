#include "Map.h"


Map::Map()
{
	//alustetaan tausta
#pragma region tausta

	tausta1.setTexture(&Content::get()->backgroundTexture1);
	tausta1.setPosition(0, 0);
	tausta1.setSize(sf::Vector2f(1536, 1536));

	for (int i = 0; i < 10; i++)
	{
		clouds.push_back(new Cloud());
		clouds[i]->setPos(sf::Vector2f(Utility::random(0, SCREEN_WIDTH), Utility::random(0, SCREEN_HEIGHT)));
	}
#pragma endregion

#pragma region luku

	kerroin = 0;
	size = 50;

	numberOfMap = 0;
	//luetaan mappi fili ja pilkotaan se x ja y akselittain
	file.open("Files\\Maps\\Map" + std::to_string(numberOfMap) + ".txt");
	while (getline(file, line))
	{
		if (line.compare("--") == 0)
		{
			yRivi.push_back(mapObjects);
			kerroin++;
			mapObjects.clear();
			if (kerroin == size)
			{
				xRivi.push_back(yRivi);
				kerroin = 0;
				yRivi.clear();
			}
		}
		else
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
	}
	file.close();
#pragma endregion
}

void Map::update(sf::View view, float speed)
{

	//p‰ivitet‰‰n taustan sijaintia
	tausta1.setPosition(view.getCenter().x - tausta1.getGlobalBounds().width / 2, view.getCenter().y - tausta1.getGlobalBounds().height / 2);
	//p‰ivitet‰‰n pilvi‰
	for (int i = 0; i < clouds.size(); i++)
	{
		clouds[i]->setPos(sf::Vector2f(clouds[i]->getPos().x - (speed)*clouds[i]->speed, clouds[i]->getPos().y));
		
		if (view.getCenter().x - clouds[i]->getPos().x > SCREEN_WIDTH / 2)
			clouds[i]->setPos(sf::Vector2f(clouds[i]->getPos().x + SCREEN_WIDTH, view.getCenter().y + Utility::random(-512, 512)));
		else if (clouds[i]->getPos().x - view.getCenter().x > SCREEN_WIDTH / 2)
			clouds[i]->setPos(sf::Vector2f(clouds[i]->getPos().x - SCREEN_WIDTH, view.getCenter().y + Utility::random(-512, 512)));
	}		
}

void Map::draw(sf::View view)
{
	window.draw(tausta1);

	for (int i = 0; i < clouds.size(); i++)
		window.draw(clouds[i]->shape);

	//otetaan kamerasta pelaajan sijainti
	int xxx = floor(view.getCenter().x / 512);
	int yyy = floor(view.getCenter().y / 512);


	for (int xx = -1; xx < 2; ++xx)
	{
		for (int yy = -1; yy < 2; ++yy)
		{
			if (xxx + xx >= 0 && yyy + yy >= 0 && xxx + xx < xRivi.size() && yyy + yy < xRivi.size())
			{
				for (int i = 0; i < xRivi[xxx + xx][yyy + yy].size(); ++i)
				{
					window.draw(xRivi[xxx + xx][yyy + yy][i]->shape);
				}
			}
		}
	}

	
}

int Map::getSize(){
	return this->size;
}

Map::~Map()
{
	for (int i = 0; i < xRivi.size();i++)
	for (int k = 0; k < xRivi[i].size();k++)
	for (int e = 0; e < xRivi[i][k].size(); e++)
		delete xRivi[i][k][e];

	for (int i = 0; i < clouds.size(); i++)
		delete clouds[i];

}
