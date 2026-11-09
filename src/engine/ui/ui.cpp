#include "ui.hpp"

const sf::Vector2f item_size_hotbar{ 60.f, 60.f };
const sf::Vector2f item_size_inventory{ 100.f, 100.f };
constexpr float item_border{ 4.f };

const sf::Color itemBgFillColour { 30, 30, 30, 230 };
const sf::Color itemOutlnColour{ 194, 139, 30 };
const sf::Color selectedColour{ 200, 200, 200, 50 };

constexpr float healthbarWidth = 300.f;

sf::Vector2f engine::UI_Template::_GetPosOfHotbarItemAtIndex(size_t index) {
	return sf::Vector2f(
		(windowSize.x / 2) - (((item_size_hotbar.x + item_border) * HOTBAR_SIZE) / 2) + ((item_border + item_size_hotbar.x) * index + (item_border / 2)),
		windowSize.y - (item_border * 2 + item_size_hotbar.y + 50.f)
	);
}

sf::Vector2f engine::UI_Template::_GetPosOfInventoryItemAtIndex(size_t index) {
	return sf::Vector2f(
		(windowSize.x / 2) -
		((item_size_inventory.x + item_border) * INVENTORY_COL) / 2 +
		(item_border + item_size_inventory.x) * (index % INVENTORY_COL) + (item_border / 2),
		100.f + (item_border * 2 + item_size_inventory.y + 10.f) * (index/INVENTORY_COL)
	);
}

void engine::UI_Template::_MoveTopRowSpriteInvAndHotbar(sf::Sprite* sprite, size_t index, bool moveToHotbar) {
	if (moveToHotbar) {
		sprite->setPosition(this->_GetPosOfHotbarItemAtIndex(index));
	}
	else {
		sprite->setPosition(this->_GetPosOfInventoryItemAtIndex(index) +
			sf::Vector2f(
				(item_size_inventory.x - item_size_hotbar.x) / 2.f,
				(item_size_inventory.y - item_size_hotbar.y) / 2.f
			)
		);
	}
}

engine::UI_Template::UI_Template(bool* inventoryControl, sf::Texture& itemsTexture, sf::Font& font):
	render_inventory_sprite(render_inventory.getTexture()),
	render_hotbar_sprite(render_hotbar.getTexture()),
    inventoryFont(font),
    itemsTexture(itemsTexture)
{
	this->inventoryControl = inventoryControl;
	
	(void)this->render_hotbar.resize(sf::Vector2u((unsigned int)windowSize.x, (unsigned int)windowSize.y));
	(void)this->render_inventory.resize(sf::Vector2u((unsigned int)windowSize.x, (unsigned int)windowSize.y));

	sf::RectangleShape bg_slot{ item_size_hotbar };
	bg_slot.setFillColor(itemBgFillColour);
	bg_slot.setOutlineColor(itemOutlnColour);
	bg_slot.setOutlineThickness(item_border);
	for (size_t i = 0; i < HOTBAR_SIZE; i++) {
		bg_slot.setPosition(this->_GetPosOfHotbarItemAtIndex(i));
		this->render_hotbar.draw(bg_slot);
	}
	this->render_hotbar_sprite.setTexture(this->render_hotbar.getTexture());

	this->render_current_selection = sf::RectangleShape(item_size_hotbar + sf::Vector2f(item_border * 2, item_border * 2));
	this->render_current_selection.setPosition(this->_GetPosOfHotbarItemAtIndex(current_selection) - sf::Vector2f(item_border, item_border));
	this->render_current_selection.setFillColor(selectedColour);

	bg_slot.setSize(item_size_inventory);
	for (size_t i = 0; i < INVENTORY_SIZE; i++) {
		bg_slot.setPosition(this->_GetPosOfInventoryItemAtIndex(i));
		this->render_inventory.draw(bg_slot);
	}
	this->render_inventory_sprite.setTexture(this->render_inventory.getTexture());

	this->render_inventory_selection_for_move = sf::RectangleShape(item_size_inventory);
	this->render_inventory_selection_for_move.setFillColor(selectedColour);

	this->healthSliderBackground = sf::RectangleShape(sf::Vector2f(healthbarWidth, 30.f));
	this->healthSliderBackground.setFillColor(sf::Color(itemBgFillColour));
	this->healthSliderBackground.setPosition(sf::Vector2f(15.f, 5.f));
	this->healthCount = 100;
	this->healthSlider = sf::RectangleShape();
	this->_ChangeDisplayHealth();
	this->healthSlider.setFillColor(sf::Color(200, 10, 12));
	this->healthSlider.setPosition(healthSliderBackground.getPosition());

	// Set inventory and hotbar
	this->inventory.reserve(INVENTORY_SIZE);
	for (size_t i = 0; i < INVENTORY_SIZE; i++) {
		this->inventory.push_back(nullptr);
		this->inventory_item_amount.push_back(nullptr);
	}

	this->render_hotbar.display();
	this->render_inventory.display();

    render_inventory_sprite.setTexture(render_inventory.getTexture(), true);
	render_hotbar_sprite.setTexture(render_hotbar.getTexture(), true);
}

void engine::UI_Template::SetInventoryControl(bool* inventoryControl) {
    this->inventoryControl = inventoryControl;
}

bool engine::UI_Template::AddItemToInventorySlot(size_t index, size_t item_type, size_t amount) {
	if (this->inventory[index] == nullptr) {
		this->inventory[index] = new ItemSlot{item_type, 0};
		/*this->render_inventory_items[index].setTexture(*this->itemsTexture);
		this->render_inventory_items[index].setTextureRect(sf::IntRect(
			sf::Vector2i((int)(utils::game::itemSize.x * item_type), 0),
			sf::Vector2i(utils::game::itemSize)
		));
		this->render_inventory_items[index].setPosition(
			this->_GetPosOfInventoryItemAtIndex(index) +
			sf::Vector2f(
				(item_size_inventory.x - item_size_hotbar.x) / 2.f,
				(item_size_inventory.y - item_size_hotbar.y) / 2.f
			)
		);*/
		this->inventory_item_amount[index] = new sf::Text(this->inventoryFont);
		//this->inventory_item_amount[index]->setFont(this->inventoryFont);
		this->inventory_item_amount[index]->setPosition(this->_GetPosOfInventoryItemAtIndex(index));
	}
	if (this->inventory[index]->type == item_type) {
		inventory[index]->count += amount;
		this->inventory_item_amount[index]->setString(std::to_string(inventory[index]->count));
		return true;
	}
	return false;
}

void engine::UI_Template::_DrawHotbar(sf::RenderWindow& win) {
	win.draw(this->render_hotbar_sprite);
	for (size_t i = 0; i < HOTBAR_SIZE; i++) {
		if (this->inventory[i] != nullptr) {
			// this->_MoveTopRowSpriteInvAndHotbar(&this->render_inventory_items[i], i, true);
			// win.draw(this->render_inventory_items[i]);
		}
	}
	win.draw(render_current_selection);
}

void engine::UI_Template::_DrawInventory(sf::RenderWindow& win) {
	win.draw(this->render_inventory_sprite);
	for (size_t i = 0; i < INVENTORY_SIZE; i++) {
		if (this->inventory[i] != nullptr) {
			// if (i < HOTBAR_SIZE)
			// 	this->_MoveTopRowSpriteInvAndHotbar(&this->render_inventory_items[i], i, false);
			// win.draw(this->render_inventory_items[i]);
			win.draw(*this->inventory_item_amount[i]);
		}
	}
	if (this->inventory_selection_for_move != nullptr)
		win.draw(this->render_inventory_selection_for_move);
}

bool engine::UI_Template::AddItemToLowestInventorySlot(size_t item) {
	for (size_t i = 0; i < INVENTORY_SIZE; i++) {
		if (this->inventory[i] != nullptr && this->inventory[i]->type == item) {
			if (this->AddItemToInventorySlot(i, item))
				return true;
		}
	}
	for (size_t i = 0; i < INVENTORY_SIZE; i++) {
		if (this->AddItemToInventorySlot(i, item))
			return true;
	}
	return false;
}

void engine::UI_Template::RemoveItemFromSlot(size_t index) {
	delete this->inventory[index];
	delete this->inventory_item_amount[index];
	this->inventory[index] = nullptr;
	this->inventory_item_amount[index] = nullptr;
}

bool engine::UI_Template::MoveItemSlotToNewSlot(ItemSlot* oldSlot, size_t oldSlotIndex, size_t newSlotIndex) {
	if (this->AddItemToInventorySlot(newSlotIndex, oldSlot->type, oldSlot->count)) {
		this->RemoveItemFromSlot(oldSlotIndex);
		return true;
	}
	return false;
}

void engine::UI_Template::SelectInventorySlotForMove(sf::Vector2f mousePos) {
	sf::FloatRect currentItem{ sf::Vector2f(0.f, 0.f), item_size_inventory };
	for (size_t i = 0; i < this->inventory.size(); i++) {
		sf::Vector2f newPos = this->_GetPosOfInventoryItemAtIndex(i);
		currentItem.position.x = newPos.x;
		currentItem.position.y = newPos.y;
		if (currentItem.contains(mousePos)) {
			if (this->inventory_selection_for_move == nullptr && this->inventory[i] != nullptr) {
				this->inventory_selection_for_move = this->inventory[i];
				this->inventory_selection_for_move_index = i;
				this->render_inventory_selection_for_move.setPosition(newPos);
			}
			else if (this->inventory_selection_for_move == this->inventory[i]) {
				this->inventory_selection_for_move = nullptr;
			}
			else if (this->inventory_selection_for_move != nullptr) {
				(void)this->MoveItemSlotToNewSlot(inventory_selection_for_move, inventory_selection_for_move_index, i);
				this->inventory_selection_for_move = nullptr;
			}
			return;
		}
	}
}

bool engine::UI_Template::DropSelectedItem(size_t* droppedItemType) {
	if (this->inventory[current_selection] == nullptr)
		return false;
	this->inventory[current_selection]->count--;
	*droppedItemType = this->inventory[current_selection]->type;
	this->inventory_item_amount[current_selection]->setString(std::to_string(inventory[current_selection]->count));
	
	if (this->inventory[current_selection]->count == 0) {
		this->RemoveItemFromSlot(current_selection);
	}
	return true;
}

void engine::UI_Template::SetHotbarSelection(size_t newHotbarSelection) {
	this->current_selection = newHotbarSelection;
	this->render_current_selection.setPosition(this->_GetPosOfHotbarItemAtIndex(this->current_selection) - sf::Vector2f(item_border, item_border));
}

bool engine::UI_Template::MouseSelectHotbarSlot(sf::Vector2f mousePos) {
	sf::FloatRect currentItem{ sf::Vector2f(0.f, 0.f), item_size_hotbar };
	for (size_t i = 0; i < HOTBAR_SIZE; i++) {
		sf::Vector2f newPos = this->_GetPosOfHotbarItemAtIndex(i);
		currentItem.position.x = newPos.x;
		currentItem.position.y = newPos.y;
		if (currentItem.contains(mousePos)) {
			this->current_selection = i;
			this->render_current_selection.setPosition(this->_GetPosOfHotbarItemAtIndex(this->current_selection) - sf::Vector2f(item_border, item_border));
			return true;
		}
	}
	return false;
}

bool engine::UI_Template::IsHotbarSelectionValid() {
	return this->inventory[this->current_selection] != nullptr;
}

size_t engine::UI_Template::__DangerousGetHotbarSelection() {
	return this->inventory[this->current_selection]->type;
}

void engine::UI_Template::_ChangeDisplayHealth() {
	this->healthSlider.setSize(sf::Vector2f((float)this->healthCount / 100.f * healthbarWidth, 30.f));
}

bool engine::UI_Template::ChangeHealth(std::uint8_t change, bool positiveChange) {
	if (positiveChange) {
		this->healthCount = std::min<std::uint8_t>(100, this->healthCount + change);
	}
	else if (change <= this->healthCount) {
		this->healthCount -= change;
		if (this->healthCount == 0)
			return false;
	}
	else {
		return false; // Only returns false if "dead" not if change affected health (i.e. adding over max)
	}

	this->_ChangeDisplayHealth();
	return true;
}

void engine::UI_Template::Resize(const sf::View& uiView) {
	// TODO: The UI almost works it struggles with artifacts sometimes
	// Set new screen size
	this->windowSize = uiView.getSize();

	// Inventory & Hotbar
	// Clear
	(void)this->render_hotbar.resize(sf::Vector2u((unsigned int)windowSize.x, (unsigned int)windowSize.y));
	this->render_hotbar.clear(sf::Color::Transparent);
	this->render_inventory.clear(sf::Color::Transparent);
	(void)this->render_inventory.resize(sf::Vector2u((unsigned int)windowSize.x, (unsigned int)windowSize.y));
	sf::RectangleShape bg_slot{ item_size_hotbar };
	bg_slot.setFillColor(itemBgFillColour);
	bg_slot.setOutlineColor(itemOutlnColour);
	bg_slot.setOutlineThickness(item_border);
	// Draw
	for (size_t i = 0; i < INVENTORY_SIZE; i++) {
		// Hotbar
		if (i < HOTBAR_SIZE) {
			bg_slot.setSize(item_size_hotbar);
			bg_slot.setPosition(this->_GetPosOfHotbarItemAtIndex(i));
			this->render_hotbar.draw(bg_slot);
		}
		// Inventory
		bg_slot.setSize(item_size_inventory);
		bg_slot.setPosition(this->_GetPosOfInventoryItemAtIndex(i));
		this->render_inventory.draw(bg_slot);
		// this->render_inventory_items[i].setPosition(
		// 	this->_GetPosOfInventoryItemAtIndex(i) +
		// 	sf::Vector2f(
		// 		(item_size_inventory.x - item_size_hotbar.x) / 2.f,
		// 		(item_size_inventory.y - item_size_hotbar.y) / 2.f
		// 	)
		// );
		if (this->inventory_item_amount[i] != nullptr)
			this->inventory_item_amount[i]->setPosition(this->_GetPosOfInventoryItemAtIndex(i));
	}
	this->render_current_selection.setPosition(this->_GetPosOfHotbarItemAtIndex(this->current_selection) - sf::Vector2f(item_border, item_border));
	// Compute
	this->render_hotbar.display();
	this->render_inventory.display();
	this->render_hotbar_sprite.setTextureRect(sf::IntRect(
		sf::Vector2i(0, 0),
		(sf::Vector2i)this->render_hotbar.getSize()
	));
	this->render_inventory_sprite.setTextureRect(sf::IntRect(
		sf::Vector2i(0, 0),
		(sf::Vector2i)this->render_inventory.getSize()
	));
}

void engine::UI_Template::Draw(sf::RenderWindow& win) {
	if (*this->inventoryControl)
		this->_DrawInventory(win);
	this->_DrawHotbar(win);

	win.draw(healthSliderBackground);
	win.draw(healthSlider);
}

engine::UI_Template::~UI_Template() {
	for (size_t i = 0; i < INVENTORY_SIZE; i++) {
		if (this->inventory[i] != nullptr)
			delete this->inventory[i];
		if (this->inventory_item_amount[i] != nullptr)
			delete this->inventory_item_amount[i];
	}
}
