#ifndef ENGINE_TILEMAP_TILEMAP_HPP
#define ENGINE_TILEMAP_TILEMAP_HPP

#include <cstdint>

#include <SFML/Graphics.hpp>

namespace engine {
    class Tilemap {
        // Public typedefs
    public:
        typedef std::uint8_t tile_t;

        // Public functions
    public:
        Tilemap(sf::Texture&);
        void Init(size_t, size_t, tile_t*, sf::Sprite&, size_t);
        void LoadAndInitFromFile(std::string filePath, sf::Sprite&);
        sf::Vector2<bool> GetCollisionData(sf::FloatRect); // TODO: Collision seems to have been ported wrong
        void Draw(sf::RenderWindow& win);
        void UpdatePlayerLoadPosition(sf::Vector2f);
        ~Tilemap();

        // Private functions
    private:
        void _GenerateTile(sf::Sprite**, size_t, size_t);
    
        // Private members
    private:
        std::string filePath;
        size_t width{};
        size_t height{};
        sf::Vector2f pos;
        sf::RenderTexture renderTexture;
        sf::Sprite renderSprite;
        sf::FloatRect* collisionShapes;
        std::uint8_t* collisionMap;
        sf::Texture& texture;

    };
}

#endif