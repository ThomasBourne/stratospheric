#include "controllableentity.hpp"

#include "../../utility/utility.hpp"

engine::ControllableEntity::ControllableEntity(sf::Texture& controllablesTexture): Entity(
	controllablesTexture,
	utility::animate::player::playerSize,
	{
		std::make_pair<size_t, size_t>(0, 0),
		std::make_pair<size_t, size_t>(1, 2),
	}
	) {
}

void engine::ControllableEntity::RunPhysics(engine::Tilemap& tilemap, void* customData) {
    constexpr float stepWeight{ 1.5f };

    // TODO: Current implementation will enable sideways movement to be quicker than L-R & U-D
    // Must take in vec2f of magnitude (0-1, 0-1) then perform calculation with stepWeight to determine where on the circle the 2 points are 
	const sf::Vector2f cardinality {
        stepWeight * sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) +
        -stepWeight * sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A),
        stepWeight * sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) +
        -stepWeight * sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)
    };

	shape.move(sf::Vector2f(cardinality.x, 0.f));
	sf::Vector2<bool> collisionData = tilemap.GetCollisionData(this->shape.getGlobalBounds());
	if (!collisionData.x) {
		shape.move(sf::Vector2f(-cardinality.x, 0.f));
	}

	shape.move(sf::Vector2f(0.f, cardinality.y));
	collisionData = tilemap.GetCollisionData(this->shape.getGlobalBounds());
	if (!collisionData.y) {
		shape.move(sf::Vector2f(0.f, -cardinality.y));
	}

	// Handle animation
	this->UpdateAnimation(cardinality.x != 0.f, cardinality.x < 0.f);
}

sf::Sprite& engine::ControllableEntity::GetSpriteForModify() {
    return this->shape;
}
