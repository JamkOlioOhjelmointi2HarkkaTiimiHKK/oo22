#include "Merge.h"


Merge::Merge()
{
	
	std::string temp;
	facts.open("Files\\facts.txt");
	getline(facts, temp);
	facts.close();
	numberOfPart = 0;


	for (int i = 0; i < std::stoi(temp) + 1; i++)
	{
		
		for (int xAkseli = 0; xAkseli < 2; xAkseli++)
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

					if (name.compare("block") == 0)
					{
						mapObjects.push_back(new Block(std::stoi(x) + xAkseli * 512, std::stoi(y) + yAkseli * 512));
					}
					else if (name.compare("floor") == 0)
					{
						mapObjects.push_back(new Floor(std::stoi(x) + xAkseli * 512, std::stoi(y)+yAkseli * 512));
					}
				}
				numberOfPart++;
				file.close();
			}
		}
	}

	view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(view);
	position = sf::Vector2f(100, 100);



}

void Merge::update(float dt)
{
	if (Controls::get()->iskeydown(sf::Keyboard::D))
	{
		position.x += 50*dt;
		view.move(position);
		window.setView(view);
	}
	if (Controls::get()->iskeydown(sf::Keyboard::A))
	{
		position.x -= 50*dt;
		view.move(position);
		window.setView(view);
	}
	if (Controls::get()->iskeydown(sf::Keyboard::S))
	{
		position.y += 50*dt;
		view.move(position);
		window.setView(view);
	}
	if (Controls::get()->iskeydown(sf::Keyboard::W))
	{
		position.y -= 50*dt;
		view.move(position);
		window.setView(view);
	}

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

void merge::save()
{


	file.open("Files\\MapPart" + std::to_string(numberOfPart) + ".txt");

	for (unsigned i = 0; i < mapObjects.size(); ++i)
	{
		file << mapObjects[i]->getName() << " " << mapObjects[i]->getPos().x - pieceArea.getGlobalBounds().left << " " << mapObjects[i]->getPos().y - pieceArea.getGlobalBounds().top << std::endl;
	}


	file.close();

	for (unsigned i = 0; i < mapObjects.size(); ++i)
	{
		delete mapObjects[i];
	}

	std::string temp;
	facts.open("Files\\facts.txt");
	getline(facts, temp);
	facts.clear();
	if (std::stoi(temp) < numberOfPart)
	{
		facts.seekg(0, std::ios_base::beg);
		facts << numberOfPart;
		std::cout << temp;
	}

	facts.close();

	mapObjects.clear();
	numberOfPart++;



}

Merge::~Merge()
{
	for (unsigned i = 0; i < mapObjects.size(); ++i)
	{
		delete mapObjects[i];
	}
}
