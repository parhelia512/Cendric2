#include "Level/DynamicTiles/ParticleTile.h"
#include "Level/LevelMainCharacter.h"
#include "Spells/Spell.h"
#include "Screens/LevelScreen.h"
#include "Registrar.h"
#include "GameObjectComponents/LightComponent.h"
#include "GameObjectComponents/ParticleComponent.h"
#include "GlobalResource.h"

REGISTER_LEVEL_DYNAMIC_TILE(LevelDynamicTileID::Particle, ParticleTile)

ParticleTile::ParticleTile(LevelScreen* levelScreen) : LevelDynamicTile(levelScreen) {
}

void ParticleTile::init() {
	setBoundingBox(sf::FloatRect(0.f, 0.f, 50.f, 50.f));
	m_isCollidable = false;
}

void ParticleTile::loadAnimation(int skinNr_) {
	// initial values
	m_state = GameObjectState::Idle;
	int skinNr = skinNr_ / 2;
	m_isForegroundTile = skinNr_ % 2 != 0;

	loadParticleSystem(skinNr);
}

void ParticleTile::update(const sf::Time& frameTime) {
	// skip animation update, using game object only
	GameObject::update(frameTime);
}

void ParticleTile::setPosition(const sf::Vector2f& pos) {
	GameObject::setPosition(pos);
	if (m_velGen) {
		m_velGen->goal = sf::Vector2f(getPosition().x + 0.5f * getBoundingBox()->width, getPosition().y - 10.f);
	}
}

void ParticleTile::render(sf::RenderTarget& target) {
	if (m_isFirstRenderIteration) {
		GameObject::render(target);
		m_isFirstRenderIteration = false;
	}
	else {
		m_isFirstRenderIteration = true;
	}
}

void ParticleTile::onHit(LevelMovableGameObject* mob) {
	// nop?
}

void ParticleTile::onHit(Spell* spell) {
	// nop?
}

void ParticleTile::loadWaterParticles(int skinNr) {
	ParticleComponentData data;
	data.particleCount = 1000;
	data.emitRate = 100.f;
	data.isAdditiveBlendMode = true;
	data.texturePath = GlobalResource::TEX_PARTICLE_DROP;
	data.particleTexture = getParticleTexture();

	// Generators
	auto posGen = new particles::BoxSpawner();
	posGen->size = sf::Vector2f(30.f, 20.f);
	data.spawner = posGen;

	auto sizeGen = new particles::SizeGenerator();
	sizeGen->minStartSize = 5.f;
	sizeGen->maxStartSize = 10.f;
	sizeGen->minEndSize = 10.f;
	sizeGen->maxEndSize = 20.f;
	data.sizeGen = sizeGen;

	auto colGen = new particles::ColorGenerator();
	colGen->minStartCol = sf::Color(60, 110, 40);
	colGen->maxStartCol = sf::Color(80, 100, 50);
	colGen->minEndCol = sf::Color(60, 80, 40, 100);
	colGen->maxEndCol = sf::Color(110, 140, 80, 100);
	data.colorGen = colGen;

	auto velGen = new particles::AngledVelocityGenerator();
	velGen->minStartSpeed = 30.f;
	velGen->maxStartSpeed = 50.f;
	velGen->minAngle = 180.f;
	velGen->maxAngle = 180.f;
	data.velGen = velGen;

	auto timeGen = new particles::TimeGenerator();
	timeGen->minTime = 1.0f;
	timeGen->maxTime = 2.0f;
	data.timeGen = timeGen;

	m_pc = new ParticleComponent(data, this);
	m_pc->setOffset(sf::Vector2f(0.5f * getBoundingBox()->width, 0.8f * getBoundingBox()->height));
	addComponent(m_pc);
}

void ParticleTile::loadEmberParticles(int skinNr) {
	ParticleComponentData data;
	data.particleCount = 50;
	data.emitRate = 5.f;
	data.isAdditiveBlendMode = true;
	data.texturePath = GlobalResource::TEX_PARTICLE_STAR;
	data.particleTexture = getParticleTexture();

	// Generators
	auto posGen = new particles::DiskSpawner();
	posGen->radius = 30.f;
	data.spawner = posGen;

	auto sizeGen = new particles::SizeGenerator();
	sizeGen->minStartSize = 5.f;
	sizeGen->maxStartSize = 10.f;
	sizeGen->minEndSize = 0.f;
	sizeGen->maxEndSize = 0.f;
	data.sizeGen = sizeGen;

	auto colGen = new particles::ColorGenerator();
	switch (skinNr) {
	default:
	case 4:
		colGen->minStartCol = sf::Color(110, 255, 100);
		colGen->maxStartCol = sf::Color(110, 255, 100);
		colGen->minEndCol = sf::Color(20, 200, 0, 200);
		colGen->maxEndCol = sf::Color(20, 200, 0, 200);
		break;
	case 5:
		colGen->minStartCol = sf::Color(190, 120, 180);
		colGen->maxStartCol = sf::Color(200, 140, 190);
		colGen->minEndCol = sf::Color(230, 140, 200, 200);
		colGen->maxEndCol = sf::Color(255, 180, 230, 200);
		break;
	}
	data.colorGen = colGen;

	auto velGen = new particles::AngledVelocityGenerator();
	velGen->minStartSpeed = 20.f;
	velGen->maxStartSpeed = 30.f;
	velGen->minAngle = -10.f;
	velGen->maxAngle = 10.f;
	data.velGen = velGen;

	auto timeGen = new particles::TimeGenerator();
	timeGen->minTime = 4.0f;
	timeGen->maxTime = 6.0f;
	data.timeGen = timeGen;

	m_pc = new ParticleComponent(data, this);
	m_pc->setOffset(sf::Vector2f(0.5f * getBoundingBox()->width, 0.8f * getBoundingBox()->height));
	addComponent(m_pc);

	// light
	addComponent(new LightComponent(LightData(
		sf::Vector2f(TILE_SIZE_F * 0.5f, -TILE_SIZE_F * 0.2f),
		sf::Vector2f(200.f, 300.f), 0.3f), this));
}

void ParticleTile::loadFlameParticles(int skinNr) {
	ParticleComponentData data;
	data.particleCount = 1000;
	data.emitRate = 60.f;
	data.isAdditiveBlendMode = true;
	data.texturePath = GlobalResource::TEX_PARTICLE_FLAME;
	data.particleTexture = getParticleTexture();

	// Generators
	auto posGen = new particles::BoxSpawner();
	posGen->size = sf::Vector2f(40.f, 0.f);
	data.spawner = posGen;

	auto sizeGen = new particles::SizeGenerator();
	sizeGen->minStartSize = 30.f;
	sizeGen->maxStartSize = 50.f;
	sizeGen->minEndSize = 30.f;
	sizeGen->maxEndSize = 50.f;
	data.sizeGen = sizeGen;

	auto colGen = new particles::ColorGenerator();
	switch (skinNr) {
	default:
	case 0:
		colGen->minStartCol = sf::Color(255, 160, 64);
		colGen->maxStartCol = sf::Color(255, 160, 64);
		colGen->minEndCol = sf::Color(255, 0, 0, 200);
		colGen->maxEndCol = sf::Color(255, 0, 0, 200);
		break;
	case 1:
		colGen->minStartCol = sf::Color(100, 146, 186);
		colGen->maxStartCol = sf::Color(100, 146, 186);
		colGen->minEndCol = sf::Color(20, 83, 255, 200);
		colGen->maxEndCol = sf::Color(20, 83, 255, 200);
		break;
	case 3:
		colGen->minStartCol = sf::Color(110, 230, 100);
		colGen->maxStartCol = sf::Color(110, 230, 100);
		colGen->minEndCol = sf::Color(20, 150, 10, 200);
		colGen->maxEndCol = sf::Color(20, 150, 10, 200);
		break;
	}
	data.colorGen = colGen;

	m_velGen = new particles::AimedVelocityGenerator();
	m_velGen->goal = sf::Vector2f(getPosition().x + 0.5f * getBoundingBox()->width, getPosition().y - 10.f);
	m_velGen->minStartSpeed = 40.f;
	m_velGen->maxStartSpeed = 80.f;
	data.velGen = m_velGen;

	auto timeGen = new particles::TimeGenerator();
	timeGen->minTime = 0.3f;
	timeGen->maxTime = 0.8f;
	data.timeGen = timeGen;

	m_pc = new ParticleComponent(data, this);
	m_pc->setOffset(sf::Vector2f(0.5f * getBoundingBox()->width, 0.5f * getBoundingBox()->height));
	addComponent(m_pc);

	// light
	addComponent(new LightComponent(LightData(
		sf::Vector2f(TILE_SIZE_F * 0.5f, -TILE_SIZE_F * 0.5f),
		sf::Vector2f(200.f, 250.f), 0.6f), this));
}

void ParticleTile::loadParticleSystem(int skinNr) {
	switch (skinNr) {
	case 0:
	case 1:
	case 3:
		loadFlameParticles(skinNr);
		break;
	case 2:
		loadWaterParticles(skinNr);
		break;
	case 4:
	case 5:
	default:
		loadEmberParticles(skinNr);
		break;
	}
}

sf::RenderTexture* ParticleTile::getParticleTexture() {
	return m_isForegroundTile ? &dynamic_cast<LevelScreen*>(getScreen())->getParticleFGRenderTexture()	:
		&dynamic_cast<LevelScreen*>(getScreen())->getParticleBGRenderTexture();
}
