#include "Game.h"
#include "Misc/icon.h"

sf::RenderWindow* g_renderWindow;

Game::Game() {
	reloadWindow();

	m_renderTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_renderTexture.setSmooth(g_resourceManager->getConfiguration().isSmoothing);
	m_mainSprite.setTexture(m_renderTexture.getTexture());
	
	m_cursor.setTexture(*g_resourceManager->getTexture(ResourceID::Texture_GUI_cursor));
	
	g_inputController->setWindow(&m_mainWindow, &m_renderTexture);
	g_renderWindow = &m_mainWindow;
	m_running = true;

	if (g_resourceManager->getConfiguration().isDebugMode) {
		CharacterCore* core = new CharacterCore();
		if (!(core->load(CharacterCore::DEBUGSAVE_LOCATION))) {
			std::string errormsg = std::string(CharacterCore::DEBUGSAVE_LOCATION) + ": save file corrupted!";
			g_resourceManager->setError(ErrorID::Error_dataCorrupted, errormsg);
			m_screenManager = new ScreenManager(new SplashScreen());
			delete core;
		}
		else {
			m_screenManager = new ScreenManager(new LoadingScreen(core));
		}
	}
	else {
		m_screenManager = new ScreenManager(new SplashScreen());
	}
}

Game::~Game() {
	delete m_screenManager;
}

void Game::reloadWindow() {
	if (g_resourceManager->getConfiguration().isFullscreen) {
		m_mainWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cendric", sf::Style::Fullscreen);
	}
	else {
		m_mainWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cendric", sf::Style::Default);
	}
	m_mainWindow.setMouseCursorVisible(false); // Hide cursor
	m_mainWindow.setVerticalSyncEnabled(g_resourceManager->getConfiguration().isVSyncEnabled);
	m_mainWindow.setIcon(cendric_icon.width, cendric_icon.height, cendric_icon.pixel_data);

	g_resourceManager->getConfiguration().isWindowReload = false;
}

void Game::run() {
	sf::Clock frameClock;
	sf::Time frameTime;
	frameTime = frameClock.restart();

	while (m_running) {
		sf::Event e;
		sf::Time deltaTime;

		// input
		g_inputController->update();
		m_cursor.setPosition(g_inputController->getDefaultViewMousePosition() - sf::Vector2f(9.f, 9.f));

		// don't count this loop into the frametime!
		deltaTime = frameClock.restart();
		while (m_mainWindow.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				m_running = false;
			}
			else if (e.type == sf::Event::Resized) {
				g_inputController->setCurrentWindowSize(e.size.width, e.size.height);
			}
			else if (e.type == sf::Event::TextEntered) {
				g_inputController->readUnicode(e.text.unicode);
			}
			else if (e.type == sf::Event::KeyPressed) {
				g_inputController->setLastPressedKey(e.key.code);
			}
			else if (e.type == sf::Event::MouseWheelScrolled) {
				g_inputController->setMouseWheelScrollTicks(e.mouseWheelScroll.delta);
			}
		}

		frameClock.restart();
		// hard bound: dt should not exeed 50ms (20fps)
		if (deltaTime.asMilliseconds() > 50) {
			frameTime = sf::milliseconds(50);
			g_logger->logInfo("Game Loop", "Frame time just exceeded 50ms and is set down to 50ms. Its time was (ms): " + std::to_string(deltaTime.asMilliseconds()));
		}
		else {
			frameTime = deltaTime;
		}

		// game updates
		m_screenManager->update(frameTime);
		if (m_screenManager->isQuitRequested()) {
			m_running = false;
		}
		if (g_resourceManager->pollError()->first != ErrorID::VOID) {
			m_screenManager->setErrorScreen();
		}
		if (g_resourceManager->getConfiguration().isWindowReload) {
			reloadWindow();
		}

		// render
		m_mainWindow.clear();
		m_renderTexture.clear(),
			m_screenManager->render(m_renderTexture);
		if (g_resourceManager->getConfiguration().isDebugRendering) {
			showFPSText(m_renderTexture, frameTime.asSeconds());
		}

		m_renderTexture.display();
		m_mainWindow.draw(m_mainSprite);
		m_mainWindow.draw(m_cursor);
		m_mainWindow.display();
	}

	m_mainWindow.close();
}

void Game::showFPSText(sf::RenderTarget& target, float frameTimeSeconds) {
	sf::View oldView = target.getView();
	target.setView(target.getDefaultView());
	m_fpsList.push_back(frameTimeSeconds);
	if (static_cast<int>(m_fpsList.size()) > FPS_AVERAGE_NR) {
		m_fpsList.pop_front();
	}
	// calc average
	float sum = 0.f;
	for (float f : m_fpsList) {
		sum += f;
	}
	int fps = static_cast<int>(1.f / (sum / FPS_AVERAGE_NR));

	BitmapText fpsText = BitmapText(
		"FPS: " + std::to_string(fps));
	fpsText.setColor(COLOR_BAD);
	fpsText.setPosition(sf::Vector2f(1050.f, 10.f));
	fpsText.setCharacterSize(16);

	target.draw(fpsText);
	target.setView(oldView);
}