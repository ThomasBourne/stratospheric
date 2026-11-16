#ifndef ENGINE_ENTITY_CONTROLLABLE_ENTITY_HPP
#define ENGINE_ENTITY_CONTROLLABLE_ENTITY_HPP

#include "entity.hpp"

#include "../tilemap/tilemap.hpp"
#include "../settings/keybinds.hpp"

namespace engine {
    class ControllableEntity : public Entity {
        // Public Members
    public:

        // Public Functions
    public:
        ControllableEntity(sf::Texture&);
        void RunPhysics(engine::Tilemap& tilemap, engine::Keybinds& keybinds, void* customData);
        sf::Sprite& GetSpriteForModify();

        // Protected Members
    protected:
    };
}

#endif