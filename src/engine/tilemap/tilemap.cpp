#include "tilemap.hpp"

#include "../../utility/utility.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

engine::Tilemap::Tilemap(sf::Texture& allTiles) :
    texture(allTiles),
    renderSprite(allTiles)
    {
	this->collisionMap = nullptr;
	this->collisionShapes = new sf::FloatRect[1];
	const sf::Vector2f zz{ 0.f, 0.f };
	this->collisionShapes[0] = sf::FloatRect(zz, (sf::Vector2f)utility::game::tileSize);
}

void engine::Tilemap::Init(size_t width, size_t height, tile_t* tiles, sf::Sprite& playerShape, size_t startIndex) {
	// Eventially switch to tile map and texture (safe to have unoptimised for now)

	this->width = width;
	this->height = height;
	sf::Sprite** tilemap = new sf::Sprite* [width * height];
	this->pos = sf::Vector2f{ 0.f, this->height * (float)utility::game::tilemapDefinition };
	for (size_t i = 0; i < this->width * this->height; i++)
		this->_GenerateTile(tilemap, i, tiles[i]);
	// Set player pos
	playerShape.setPosition(sf::Vector2f(
		(startIndex % this->width) * utility::game::tilemapDefinition,
		(startIndex / this->width) * utility::game::tilemapDefinition
	));

	// Even though render texture no longer requires this->tilemap, collision detection depends on the drawable objects so it has to stay
	// Maybe look to reduce it to smart detection with this->collisonMap
	(void)this->renderTexture.resize(sf::Vector2u((unsigned int)this->width * (int)utility::game::tilemapDefinition, (unsigned int)this->height * (int)utility::game::tilemapDefinition));
	this->renderTexture.clear(sf::Color::Red);
	for (size_t i = 0; i < width * height; i++)
		this->renderTexture.draw(*tilemap[i]);
	this->renderTexture.display();
	this->renderSprite.setTexture(renderTexture.getTexture(), true);

	// Delete tilemap as its no longer needed (sprites rendered to RenderTexture & collison handled by floatrects
	for (size_t i = 0; i < this->width * this->height; i++) {
		if (tilemap[i] != nullptr)
			delete tilemap[i];
	}
	delete[] tilemap;
}

void engine::Tilemap::LoadAndInitFromFile(std::string filePath, sf::Sprite& playerShape) {
	this->filePath = filePath;
	std::string contents;
	std::ifstream fp{ filePath };
	std::uint16_t lineIndex{ 0 };
	size_t width{ 0 };
	size_t height{ 0 };
	std::uint8_t* dataMap{ nullptr };
	size_t startIndex1D;
	while (std::getline(fp, contents)) {
		switch (lineIndex)
		{
		case(0): {
			// Version
			if (contents != "0.0.6")
				exit((int)utility::StratErrorCodes::TilemapFileLoadFailed);
			break;
		}
		case(1): {
			// Width
			width = std::stoi(contents);
            std::cout << "Width: " << width << std::endl;
			break;
		}
		case(2): {
			// Height
			height = std::stoi(contents);
            std::cout << "Height: " << height << std::endl;
			break;
		}
		case(3): {
			// Tilemap Data
			dataMap = new std::uint8_t[width * height];
			std::stringstream ss{ contents };
			std::string segment;
			size_t i{ 0 };
			while (std::getline(ss, segment, ',')) {
				dataMap[i] = (std::uint8_t)std::stoi(segment);
				i++;
			}
			break;
		}
		case(4): {
			// Collision Data
			this->collisionMap = new std::uint8_t[width * height];
			for (size_t i = 0; i < width * height; i++) {
				this->collisionMap[i] = contents[i] - '0';
			}
			break;
		}
		case(5): {
			// Player start position
			startIndex1D = std::stoi(contents);
			break;
		}
		default:
			break;
		}
		lineIndex++;
	}
	fp.close();
	if (dataMap != nullptr) {
		this->Init(width, height, dataMap, playerShape, startIndex1D);
		delete[] dataMap;
	}
}

sf::Vector2<bool> engine::Tilemap::GetCollisionData(sf::FloatRect shape) {
	std::vector<sf::FloatRect> collidableItems;
	for (
		int y = std::max((int)((shape.position.y) / utility::game::tilemapDefinition), 0);
		(
			y <= (shape.position.y + shape.size.y) / utility::game::tilemapDefinition
			&& y < this->height
			);
		y++
		) {
		for (
			int x = std::max((int)((shape.position.x - this->pos.x) / utility::game::tilemapDefinition), 0);
			(
				x <= (int)((shape.position.x + shape.size.x) - this->pos.x) / utility::game::tilemapDefinition
				&& x < this->width
				);
			x++
			) {
			const size_t index{ x + y * this->width };
			if (this->collisionMap[index]) {
				this->collisionShapes[this->collisionMap[index] - 1].position.y = (float)(index % this->width) * utility::game::tilemapDefinition;
				this->collisionShapes[this->collisionMap[index] - 1].position.x = (float)(index / this->width) * utility::game::tilemapDefinition;
				collidableItems.push_back(this->collisionShapes[this->collisionMap[index] - 1]);
			}

		}
	}

	sf::Vector2<bool> newPos{ true, true };

	for (size_t i = 0; i < collidableItems.size(); i++) {
		if (collidableItems[i].findIntersection(shape)) {
			if (newPos.y) {
				if (shape.position.y < collidableItems[i].position.y || shape.position.y + shape.size.y > collidableItems[i].position.y) {
					newPos.y = false;
				}
			}
			if (newPos.x) {
				if (shape.position.x < collidableItems[i].position.x || shape.position.x + shape.size.x > collidableItems[i].position.x + collidableItems[i].size.x) {
					newPos.x = false;
				}
			}
		}
	}
	return newPos;
}

void engine::Tilemap::Draw(sf::RenderWindow& win) {
	win.draw(this->renderSprite);
}

void engine::Tilemap::UpdatePlayerLoadPosition(sf::Vector2f pos) {
	size_t x{ (size_t)((pos.x - this->pos.x) / utility::game::tilemapDefinition) };
	size_t y{ (size_t)((pos.y) / utility::game::tilemapDefinition) };
	size_t index = y * this->width + x;
	std::string contents;
	std::vector<std::string> contentsVector;
	std::string oldStartIndex;
	std::ifstream fp{ filePath };
	std::uint16_t lineIndex{ 0 };
	std::uint8_t* dataMap{ nullptr };
	while (std::getline(fp, contents)) {
		switch (lineIndex) {
		case(0): {
			if (contents != "0.0.6")
				exit((int)utility::StratErrorCodes::TilemapWriteFailed);
			break;
		}
		case(5): {
			contents = std::to_string(index);
			break;
		}
		default: {
			break;
		}
		}
		contentsVector.push_back(contents);
		lineIndex++;
	}
	fp.close();
	std::ofstream outFp{ filePath };
	for (const auto& line : contentsVector)
		outFp << line << "\n";
	outFp.close();
}

void engine::Tilemap::_GenerateTile(sf::Sprite** tilemap, size_t tileIndex, size_t tileTextureIndex) {
	tilemap[tileIndex] = new sf::Sprite(this->texture);
	//tilemap[tileIndex]->setTexture(this->texture);
	tilemap[tileIndex]->setTextureRect(sf::IntRect(
		sf::Vector2i((int)utility::game::tilemapDefinition * (int)tileTextureIndex,
		0),
		sf::Vector2i((int)utility::game::tilemapDefinition,
		(int)utility::game::tilemapDefinition)
	));
	tilemap[tileIndex]->setPosition(sf::Vector2f(
		(tileIndex % this->width) * utility::game::tilemapDefinition,
		(tileIndex / this->width) * utility::game::tilemapDefinition
	));
}

engine::Tilemap::~Tilemap() {
	delete[] this->collisionMap;
	delete[] this->collisionShapes;
}
