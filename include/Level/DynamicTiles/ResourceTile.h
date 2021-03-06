#pragma once

#include "global.h"
#include "Level/LevelDynamicTile.h"
#include "GUI/LootWindow.h"

class LevelMainCharacter;
class InteractComponent;

class ResourceTile : public LevelDynamicTile {
public:
	ResourceTile(LevelScreen* levelScreen) : LevelDynamicTile(levelScreen) {}
	void update(const sf::Time& frameTime) override;
	void init() override;
	void loadAnimation(int skinNr) override;
	void onRightClick() override;
	void onHit(Spell* spell) override {};
	void loot();
	
	LevelDynamicTileID getDynamicTileID() const override { return LevelDynamicTileID::Resource; }

private:
	void initializeResource(int skinNr);
	std::string getSpritePath() const override;
	// the object id in the dynamic chest tiles object layer.
	int m_objectID = -1;
	// the message that pops up if the main char has not the right tool
	std::string m_noToolMessage;
	// the tool that is used to loot this tile
	std::string m_toolItemID;
	// loot that can be gotten from that tile
	std::map<std::string, int> m_lootableItems;
	int m_lootableGold = 0;
	sf::Time m_lootTime = sf::Time::Zero;

	InteractComponent* m_interactComponent = nullptr;
	
	// the resource can only be gotten if the main char is in this range
	const float PICKUP_RANGE = 100.f;
};