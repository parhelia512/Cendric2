#pragma once

#include "global.h"
#include "Map.h"
#include "MapMainCharacter.h"
#include "Screen.h"
#include "ResourceManager.h"
#include "Screens/LoadingScreen.h"

#include "Enums/MapID.h"

class MapScreen : public Screen
{
public:
	MapScreen(MapID mapID, CharacterCore* core);

	Screen* update(const sf::Time& frameTime) override;
	void render(sf::RenderTarget& renderTarget) override;

	void execOnEnter(const Screen* previousScreen) override;
	void execOnExit(const Screen* nextScreen) override;

private:
	Map m_currentMap;
	MapMainCharacter* m_mainChar;
};