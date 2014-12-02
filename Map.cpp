#include "Map.h"


Map::Map()
{
	kerroin = 0;
	size = 60;

	numberOfMap = 0;

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
		//mapObjects.clear();
	}
	file.close();
}

void Map::update()
{

}

void Map::draw(sf::View view)
{

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
	
	int tempX = xxx ;
	int tempY = yyy;
	std::cout << tempX << " " << tempY << std::endl;
}

Map::~Map()
{



}
