#include "EditorState.h"
#include "Block.h"
#include "Floor.h"
#include "SpawnPoint.h"
#include "SpawnEnemy.h"
#include "Ladder.h"

EditorState::EditorState()
{	
	numberOfPart = 0;
	pieceArea.setPosition(128, 128);
	pieceArea.setSize(sf::Vector2f(512, 512));
	pieceArea.setFillColor(sf::Color::Magenta);

	numberText.setFont(Content::get()->font);
	numberText.setString(std::to_string(numberOfPart));
	numberText.setColor(sf::Color::White);
	numberText.setPosition((250+380)/2, 690);

#pragma region grid
	for (float i = 0; i <= pieceArea.getGlobalBounds().width / 32; ++i)
	{
		gridLines.push_back(sf::Vertex(sf::Vector2f(pieceArea.getGlobalBounds().left + 1 + i * 32, pieceArea.getGlobalBounds().top)));
		gridLines.push_back(sf::Vertex(sf::Vector2f(pieceArea.getGlobalBounds().left + 1 + i * 32, pieceArea.getGlobalBounds().top + pieceArea.getGlobalBounds().height)));
	}
	for (float i = 0; i <= pieceArea.getGlobalBounds().height / 32; ++i)
	{
		gridLines.push_back(sf::Vertex(sf::Vector2f(pieceArea.getGlobalBounds().left + 1, pieceArea.getGlobalBounds().top + i * 32)));
		gridLines.push_back(sf::Vertex(sf::Vector2f(pieceArea.getGlobalBounds().left + 1 + pieceArea.getGlobalBounds().width, pieceArea.getGlobalBounds().top + i * 32)));
	}
#pragma endregion

	
#pragma region Nappulat
	buttons.push_back(new Button(sf::Vector2f(100, 50), sf::Vector2f(800, 170), "block", [&]()
	{
		resetSelectedObject();
		selectedObject = new Block();
	}));
	
	buttons.push_back(new Button(sf::Vector2f(100, 50), sf::Vector2f(950, 170), "floor", [&]()
	{
		resetSelectedObject();
		selectedObject = new Floor();
	}));

	buttons.push_back(new Button(sf::Vector2f(100, 50), sf::Vector2f(800, 370), "spawnP", [&]()
	{
		resetSelectedObject();
		selectedObject = new SpawnPoint();
	}));

	buttons.push_back(new Button(sf::Vector2f(100, 50), sf::Vector2f(950, 370), "spawnE", [&]()
	{
		resetSelectedObject();
		selectedObject = new SpawnEnemy();
	}));

	buttons.push_back(new Button(sf::Vector2f(100, 50), sf::Vector2f(800, 270), "Ladder", [&]()
	{
		resetSelectedObject();
		selectedObject = new Ladder();
	}));

	buttons.push_back(new Button(sf::Vector2f(100, 50), sf::Vector2f(800, 470), "save", [&]()
	{
		save();

	}));

	buttons.push_back(new Button(sf::Vector2f(50, 50), sf::Vector2f(250, 690), "+", [&]()
	{
		if (Controls::get()->iskeydown(sf::Keyboard::LShift))
			numberOfPart = numberOfPart + 5;
		else
		numberOfPart++;

	}));

	buttons.push_back(new Button(sf::Vector2f(50, 50), sf::Vector2f(380, 690), "-", [&]()
	{
		if (numberOfPart>0)
		{
			if (Controls::get()->iskeydown(sf::Keyboard::LShift) && numberOfPart > 5)
				numberOfPart = numberOfPart - 5;
			else if (Controls::get()->iskeydown(sf::Keyboard::LShift))
				numberOfPart = 0;
			else
				numberOfPart--;
		}
	}));
#pragma endregion
}

bool EditorState::checkValid()
{
	if (pieceArea.getGlobalBounds().contains(Controls::get()->getmousepos()))
	{
		sf::Vector2f snappedPos = Controls::get()->getmousepos();
		int xpos = pieceArea.getGlobalBounds().left + (floor((snappedPos.x - pieceArea.getGlobalBounds().left) / 32) * 32);
		int ypos = pieceArea.getGlobalBounds().top + (floor((snappedPos.y - pieceArea.getGlobalBounds().top) / 32) * 32);
		
		if (xpos + selectedObject->getSize().x > pieceArea.getGlobalBounds().left + pieceArea.getGlobalBounds().width)
			xpos = pieceArea.getGlobalBounds().left + pieceArea.getGlobalBounds().width - selectedObject->getSize().x;
		if (ypos + selectedObject->getSize().y > pieceArea.getGlobalBounds().top + pieceArea.getGlobalBounds().height)
			ypos = pieceArea.getGlobalBounds().top + pieceArea.getGlobalBounds().height - selectedObject->getSize().y;
		snappedPos = sf::Vector2f(xpos, ypos);
		selectedObject->setPos(snappedPos);
		return true;
	}
	else
		return false;
}

void EditorState::update()
{
	for (unsigned i = 0; i < buttons.size(); ++i)
	{
		buttons[i]->update();
	}

	if (selectedObject != NULL)
		selectedObject->setPos(Controls::get()->getmousepos());

	if ((Controls::get()->mIsReleased(sf::Mouse::Left))&& checkValid())
	{
		mapObjects.push_back(selectedObject);
		if (Controls::get()->iskeydown(sf::Keyboard::LShift))
		{
			selectedObject = new MapObject(*selectedObject);
		}	
		else
			selectedObject = NULL;
	}
	if (Controls::get()->mIsReleased(sf::Mouse::Right))
	{
		resetSelectedObject();
	}
	numberText.setPosition((300 + 380) / 2 - numberText.getGlobalBounds().width / 2, 690);
	numberText.setString(std::to_string(numberOfPart));
}

void EditorState::draw()
{
	window.draw(pieceArea);
	window.draw(&gridLines[0], gridLines.size(), sf::Lines);
	window.draw(numberText);

	for (unsigned i = 0; i < buttons.size(); ++i)
	{
		buttons[i]->draw();
	}
	
	for (unsigned i = 0; i < mapObjects.size(); ++i)
	{
		window.draw(mapObjects[i]->shape);
	}
	
	if (selectedObject != NULL && checkValid())
		window.draw(selectedObject->shape);
}

void EditorState::save()
{

	
	file.open("Files\\MapPart" + std::to_string(numberOfPart)+ ".txt");
	
	for (unsigned i = 0; i < mapObjects.size(); ++i)
	{
		file << mapObjects[i]->getName() << " " << mapObjects[i]->getPos().x-pieceArea.getGlobalBounds().left << " " << mapObjects[i]->getPos().y-pieceArea.getGlobalBounds().top << std::endl;
	}
	

	file.close();

	for (unsigned i = 0; i < mapObjects.size(); ++i)
	{
		delete mapObjects[i];
	}

	std::string temp;
	facts.open("Files\\facts.txt");
	getline(facts, temp);
	if (std::stoi(temp) < numberOfPart)
	{
		facts.seekg(0,std::ios_base::beg);
		facts << numberOfPart;
	}
		
	facts.close();

	mapObjects.clear();
	numberOfPart++;
	
	

}

void EditorState::resetSelectedObject()
{
	if (selectedObject != NULL)
	{
		delete selectedObject;
		selectedObject = NULL;
	}
}
void EditorState::loop()
{
	update();
	window.clear(sf::Color(255, 0, 0));
	draw();
	window.display();

}
EditorState::~EditorState()
{
}
