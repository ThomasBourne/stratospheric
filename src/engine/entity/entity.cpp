#include "entity.hpp"

#include "../../utility/utility.hpp"

engine::Entity::Entity(sf::Texture& fullTexture, sf::Vector2f size, AnimationSet animationSets) :
    texture(fullTexture),
    shape(fullTexture),
    size(size),
    animationSets(animationSets),
    currentAnimationSet(0),
    framesSinceLastAnimationFrame(0),
    textureIndex(0)
    {
        this->shape.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)size));
    }

void engine::Entity::RunPhysics(/*Tilemap& tilemap, void* customData*/) {
    this->UpdateAnimation(1, false);
}

void engine::Entity::UpdateAnimation(size_t animationSet, bool flipSprite) {
	if (this->framesSinceLastAnimationFrame % utility::animate::player::framesPerAnimationFrame == 0) {
		this->textureIndex++;
		this->textureIndex = std::max<size_t>(this->textureIndex % (animationSets[animationSet].second+1), animationSets[animationSet].first);

		if (flipSprite) {
			this->shape.setTextureRect(sf::IntRect(
				sf::Vector2i((int)(this->size.x * (this->textureIndex + 1)), 0),
				sf::Vector2i((int)-this->size.x, (int)this->size.y)
			));
		}
		else {
			this->shape.setTextureRect(sf::IntRect(
				sf::Vector2i((int)(this->size.x * this->textureIndex), 0),
				(sf::Vector2i)this->size
			));
		}
	}

	this->framesSinceLastAnimationFrame++;
	
}

void engine::Entity::SetPosition(const sf::Vector2f position) { this->shape.setPosition(position); }

const sf::Vector2f engine::Entity::GetPosition() { return this->shape.getPosition(); }

const sf::Vector2f engine::Entity::GetSize() { return sf::Vector2f(shape.getLocalBounds().size.x, shape.getLocalBounds().size.y); }

void engine::Entity::Draw(sf::RenderWindow& win) { win.draw(this->shape); }
