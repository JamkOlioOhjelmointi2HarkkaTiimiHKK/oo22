#pragma once
#include "SFML/Graphics.hpp"
#include <fstream>
#include "globals.h"
#include "Content.h"
#include "Button.h"

class MapObject;
class Button;

class EditorState
{
protected:
	std::vector<Button*> buttons;
	std::vector<MapObject*> mapObjects;
	sf::RectangleShape pieceArea;
	sf::Text numberText;
	std::vector<sf::Vertex> gridLines;
	MapObject *selectedObject;
	std::ofstream file;
	std::fstream facts;
	int numberOfPart;

	void resetSelectedObject();
	bool checkValid();
	void update();
	void draw();
	void save();


public:
	EditorState();
	void loop();
	~EditorState();
};

