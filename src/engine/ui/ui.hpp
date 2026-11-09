#ifndef ENGINE_UI_UI_HPP
#define ENGINE_UI_UI_HPP

#include "../../utility/utility.hpp"

#include <SFML/Graphics.hpp>

#include <vector>
#include <array>

#define INVENTORY_COL 10
#define INVENTORY_ROW 5
#define INVENTORY_SIZE (INVENTORY_COL * INVENTORY_ROW)
#define HOTBAR_SIZE INVENTORY_COL

#define MAX_ITEM_PER_SLOT 3

namespace engine {
	class UI_Template {
	public:
		struct ItemSlot {
			size_t type;
			size_t count;
		};

	private:
		sf::Font& inventoryFont;
		sf::Texture& itemsTexture;
		size_t current_selection = 0;

		std::vector<ItemSlot*> inventory;
		std::vector<sf::Text*> inventory_item_amount;

		sf::RenderTexture render_inventory;
		sf::Sprite render_inventory_sprite;
		//std::array<sf::Sprite, INVENTORY_SIZE> render_inventory_items; // TODO: Make this a RenderTexture later
		ItemSlot* inventory_selection_for_move = nullptr;
		size_t inventory_selection_for_move_index = 0;
		sf::RectangleShape render_inventory_selection_for_move;

		sf::RenderTexture render_hotbar;
		sf::Sprite render_hotbar_sprite;
		sf::RectangleShape render_current_selection;

		bool* inventoryControl;

		std::uint8_t healthCount;
		sf::RectangleShape healthSliderBackground;
		sf::RectangleShape healthSlider;

		sf::Vector2f windowSize{ utility::defaultWindowSize };

	private:
		sf::Vector2f _GetPosOfHotbarItemAtIndex(size_t index);
		sf::Vector2f _GetPosOfInventoryItemAtIndex(size_t index);
		inline void _MoveTopRowSpriteInvAndHotbar(sf::Sprite* sprite, size_t index, bool moveToHotbar);
		inline void _DrawHotbar(sf::RenderWindow& win);
		inline void _DrawInventory(sf::RenderWindow& win);
		inline void _ChangeDisplayHealth();

	public:
		UI_Template(bool* inventoryControl, sf::Texture& itemsTexture, sf::Font& font);

        void SetInventoryControl(bool* inventoryControl);

		bool AddItemToInventorySlot(size_t index, size_t item, size_t amount = 1);

		bool AddItemToLowestInventorySlot(size_t item);

		void RemoveItemFromSlot(size_t index);

		bool MoveItemSlotToNewSlot(ItemSlot* oldSlot, size_t oldSlotIndex, size_t newSlotIndex);

		void SelectInventorySlotForMove(sf::Vector2f mousePos);

		bool DropSelectedItem(size_t* droppedItemType);

		void SetHotbarSelection(size_t newHotbarSelection);

		bool MouseSelectHotbarSlot(sf::Vector2f mousePos);

		bool IsHotbarSelectionValid();

		size_t __DangerousGetHotbarSelection();

		bool ChangeHealth(std::uint8_t change, bool positiveChange);

		void Resize(const sf::View&);

		void Draw(sf::RenderWindow& win);

		~UI_Template();
	};
}

#endif