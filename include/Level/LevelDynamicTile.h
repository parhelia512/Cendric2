#pragma once

#include "global.h"
#include "AnimatedGameObject.h"
#include "ResourceManager.h"
#include "Enums/LevelDynamicTileID.h"

class Spell;
class LevelMovableGameObject;
class Level;
class LevelMainCharacter;
class LevelScreen;

// A dynamic tile in a level
class LevelDynamicTile : public virtual AnimatedGameObject {
public:
	LevelDynamicTile(LevelScreen* levelScreen);
	virtual ~LevelDynamicTile() {};

	// loads sprite offset & bounding box.
	virtual void init() = 0;
	// loads the resources (sprite, sound)
	virtual void loadResources();
	// loads the dynamic tile with the specified skin nr
	virtual void loadAnimation(int skinNr) = 0;
	// gets called by a spell when it hits the dynamic tile
	virtual void onHit(Spell* spell) = 0;
	// gets called by a mob when it hits the dynamic tile. default does nothing
	virtual void onHit(LevelMovableGameObject* mob);
	// the render method of level dynamic tiles gets called twice per game loop
	// this is to seperate the water tiles which are rendered after the game objects
	// from the other tiles.
	virtual void render(sf::RenderTarget& target) override;

	// sets the position offset for a dynamic tile. DON'T use that for collidable dynamic tiles.
	void setPositionOffset(const sf::Vector2f& offset);

	const sf::Vector2f& getPositionOffset() const;
	virtual LevelDynamicTileID getDynamicTileID() const = 0;
	bool isCollidable() const;
	bool isStrictlyCollidable() const;
	bool isOneWay() const;
	GameObjectType getConfiguredType() const override;
	const Level* getLevel() const;

protected:
	virtual std::string getSpritePath() const { return ""; }
	virtual std::string getSoundPath() const { return ""; }
	// dynamic tile textures have a border (border width in pixel)
	const int BORDER = 1;
	const Level* m_level;
	LevelMainCharacter* m_mainChar;
	bool m_isCollidable = false;
	bool m_isStrictlyCollidable = false;
	bool m_isOneWay = false;
	bool m_isRenderAfterObjects = false;
	bool m_isFirstRenderIteration = true;

private:
	sf::Vector2f m_positionOffset = sf::Vector2f(0.f, 0.f);
};