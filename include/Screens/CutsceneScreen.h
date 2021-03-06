#pragma once

#include "global.h"
#include "ResourceManager.h"
#include "Screen.h"
#include "Cutscene/Cutscene.h"

class CutsceneScreen : public Screen {
public:
	CutsceneScreen(CharacterCore* core, const std::string& cutsceneID);

	void execUpdate(const sf::Time& frameTime) override;
	void render(sf::RenderTarget& renderTarget) override;

	void execOnEnter(const Screen* previousScreen) override;
	void execOnExit(const Screen* nextScreen) override;

private:
	Cutscene* m_cutscene = nullptr;
	std::string m_cutsceneID;
};