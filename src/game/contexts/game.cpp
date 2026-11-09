#include "contexts.hpp"

#include "SFML/System/Vector2.hpp"

#include "../../utility/utility.hpp"

using namespace game::contexts;

Game::Game(THE_BIG_THREE_WITH_TEXT, sf::Texture& tilemap, sf::Texture& playerTexture, sf::Texture& entityTexture, engine::UI_Template& ui) :
    engine::Context(winRef, viewGame, viewUI),
    player(playerTexture),
    entity(entityTexture, sf::Vector2f(50.f, 30.f), {std::make_pair<size_t, size_t>(0, 0),std::make_pair<size_t, size_t>(1, 2)}),
    tilemap(tilemap),
    ui(ui)
    {
        // TODO: Move this to reload & unload when unload is implemented
        this->tilemap.LoadAndInitFromFile( ASSET_FILE(utility::game::tilemapFileName), player.GetSpriteForModify() );

        this->isUiShown = false;
        this->ui.SetInventoryControl(&this->isUiShown);
    }

void Game::Reload() {
    // player.setPosition(sf::Vector2f(800.f, 200.f));
    // player.setTextureRect({{0, 0}, {utility::game::tilemapDefinition, utility::game::tilemapDefinition}});
}

bool Game::Poll(const std::optional<sf::Event>& event, void* nextContext) {
     if (
        event->is<sf::Event::KeyReleased>()
    ) {
        if(event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::Escape) {
            *((Contexts*)nextContext) = Contexts::Settings;
            return true;
        }
        else if(event->getIf<sf::Event::KeyReleased>()->code == sf::Keyboard::Key::M) {
            this->isUiShown = !this->isUiShown;
        }
    }
    return false;
}

void Game::Physics() {
    if (this->isUiShown) {
        return;
    }

    this->player.RunPhysics(tilemap, nullptr);
    
    // Check if view needs shifting
    // This is slightly unexpected behaviour with the latter checks, but its ok because its slightly quicker (probably)
    sf::View& v = viewGame;
    if (abs(player.GetPosition().x) < abs(v.getCenter().x - utility::game::viewBounds.x.x)) {
        v.move(sf::Vector2f(
            player.GetPosition().x - (abs(v.getCenter().x) - utility::game::viewBounds.x.x)
        , 0.f));
    }
    else if (abs(player.GetPosition().x) > abs(v.getCenter().x + utility::game::viewBounds.x.y)) {
        v.move(sf::Vector2f(
            player.GetPosition().x - (abs(v.getCenter().x) + utility::game::viewBounds.x.y)
            , 0.f));
    }
    if (abs(player.GetPosition().y) < abs(v.getCenter().y - utility::game::viewBounds.y.x)) {
        v.move(sf::Vector2f(
            0.f,
            player.GetPosition().y - (abs(v.getCenter().y) - utility::game::viewBounds.y.x)
        ));
    }
    else if (abs(player.GetPosition().y) > abs(v.getCenter().y + utility::game::viewBounds.y.y)) {
        v.move(sf::Vector2f(
            0.f,
            player.GetPosition().y - (abs(v.getCenter().y) + utility::game::viewBounds.y.y)
        ));
    }
    
    winRef.setView(v);

    entity.RunPhysics();
}

void Game::PhysicsUI() {

}

void Game::ResizeUI() {
    ui.Resize(this->viewUI);
}

void Game::DrawContext() {
    tilemap.Draw(winRef);
    player.Draw(winRef);
    entity.Draw(winRef);
}

void Game::DrawUIContext() {
    ui.Draw(winRef);
}
