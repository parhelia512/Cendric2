#include "Level/Enemies/WolfBoss.h"
#include "Level/LevelMainCharacter.h"
#include "Level/MOBBehavior/MovingBehaviors/WolfBossMovingBehavior.h"
#include "Level/MOBBehavior/AttackingBehaviors/AggressiveBehavior.h"
#include "Registrar.h"
#include "GlobalResource.h"

REGISTER_ENEMY(EnemyID::Boss_Wolf, WolfBoss)

void WolfBoss::insertDefaultLoot(std::map<std::string, int>& loot, int& gold) const {
	gold = 50;
	loot.insert({ "mi_firstguardianheart", 1 });
	loot.insert({ "fo_ham", 2 });
}

WolfBoss::~WolfBoss() {
	delete m_ps;
}

void WolfBoss::insertRespawnLoot(std::map<std::string, int>& loot, int& gold) const {
	// nothing
}

WolfBoss::WolfBoss(const Level* level, Screen* screen) :
	LevelMovableGameObject(level),
	Enemy(level, screen) {
	load(EnemyID::Boss_Wolf);
	m_isInvincible = true;

	// Make boss hp bar appear from the start
	m_mainChar->setLastHitEnemy(this);
}

void WolfBoss::loadAttributes() {
	m_attributes.setHealth(200);
	m_attributes.resistanceIce = -20;
	m_attributes.resistancePhysical = 50;
	m_attributes.critical = 10;
	m_attributes.calculateAttributes();
}

void WolfBoss::loadSpells() {
	SpellData chopSpell = SpellData::getSpellData(SpellID::Chop);
	chopSpell.damage = 50;
	chopSpell.activeDuration = sf::seconds(1000.f);
	chopSpell.cooldown = sf::seconds(10.f);
	chopSpell.boundingBox = sf::FloatRect(0, 0, 20, 100);
	chopSpell.spellOffset = sf::Vector2f(80.f, 0.f);
	chopSpell.fightingTime = sf::seconds(1000.f);
	chopSpell.castingTime = sf::seconds(1.f);
	chopSpell.castingAnimation = GameObjectState::Casting;
	chopSpell.fightAnimation = GameObjectState::Walking;

	m_spellManager->addSpell(chopSpell);

	m_spellManager->setCurrentSpell(0); // chop
}

void WolfBoss::handleAttackInput() {
	// Cendric is too far away to charge.
	if (std::abs(m_mainChar->getPosition().y - getPosition().y) > 400.f)
		return;

	// We are doing something else
	if (getState() != GameObjectState::Idle)
		return;

	m_spellManager->setCurrentSpell(0); // charge
	
	if (getCurrentTarget() != nullptr)
		m_spellManager->executeCurrentSpell(getCurrentTarget()->getCenter());
}

void WolfBoss::update(const sf::Time& frameTime) {
	Enemy::update(frameTime);
	if (m_isDead) {
		m_ps->update(frameTime);
		updateTime(m_fadingTime, frameTime);
		updateTime(m_particleTime, frameTime);
		if (m_particleTime == sf::Time::Zero) {
			m_ps->emitRate = 0;
		}
		setSpriteColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(m_fadingTime.asSeconds() / 2.f * 255.f)), sf::seconds(1000));
	}
}

void WolfBoss::loadAnimation() {
	setBoundingBox(sf::FloatRect(0.f, 0.f, 200.f, 90.f));
	setSpriteOffset(sf::Vector2f(-50.f, -160.f));
	const sf::Texture* tex = g_resourceManager->getTexture(getSpritePath());

	Animation* walkingAnimation = new Animation(sf::seconds(0.05f));
	walkingAnimation->setSpriteSheet(tex);
	for (int i = 0; i < 13; ++i) {
		walkingAnimation->addFrame(sf::IntRect(i * 300, 0, 300, 250));
	}

	addAnimation(GameObjectState::Walking, walkingAnimation);

	Animation* idleAnimation = new Animation();
	idleAnimation->setSpriteSheet(tex);
	idleAnimation->addFrame(sf::IntRect(4 * 300, 250, 300, 250));
	idleAnimation->addFrame(sf::IntRect(5 * 300, 250, 300, 250));
	idleAnimation->addFrame(sf::IntRect(6 * 300, 250, 300, 250));
	idleAnimation->addFrame(sf::IntRect(5 * 300, 250, 300, 250));

	addAnimation(GameObjectState::Idle, idleAnimation);

	Animation* jumpingAnimation = new Animation();
	jumpingAnimation->setSpriteSheet(tex);
	jumpingAnimation->addFrame(sf::IntRect(3 * 300, 250, 300, 250));

	addAnimation(GameObjectState::Jumping, jumpingAnimation);

	Animation* deadAnimation = new Animation();
	deadAnimation->setSpriteSheet(tex);
	deadAnimation->addFrame(sf::IntRect(9 * 300, 750, 300, 250));

	addAnimation(GameObjectState::Dead, deadAnimation);

	// casting before charge attack
	Animation* castingAnimation = new Animation();
	castingAnimation->setSpriteSheet(tex);
	castingAnimation->addFrame(sf::IntRect(0 * 300, 250, 300, 250));
	castingAnimation->addFrame(sf::IntRect(1 * 300, 250, 300, 250));
	castingAnimation->addFrame(sf::IntRect(2 * 300, 250, 300, 250));
	castingAnimation->addFrame(sf::IntRect(1 * 300, 250, 300, 250));

	addAnimation(GameObjectState::Casting, castingAnimation);

	// casting before beam attack
	Animation* casting2Animation = new Animation();
	casting2Animation->setSpriteSheet(tex);
	for (int i = 0; i < 12; ++i) {
		casting2Animation->addFrame(sf::IntRect(i * 300, 500, 300, 250));
	}
	casting2Animation->setLooped(false);

	addAnimation(GameObjectState::Casting2, casting2Animation);

	// beam attack
	Animation* beamAnimation = new Animation();
	beamAnimation->setSpriteSheet(tex);
	beamAnimation->addFrame(sf::IntRect(11 * 300, 500, 300, 250));

	addAnimation(GameObjectState::Fighting2, beamAnimation);

	// casting before windgust attack
	Animation* casting3Animation = new Animation();
	casting3Animation->setSpriteSheet(tex);
	for (int i = 0; i < 4; ++i) {
		casting3Animation->addFrame(sf::IntRect(i * 300, 500, 300, 250));
	}
	casting3Animation->setLooped(false);

	addAnimation(GameObjectState::Casting3, casting3Animation);

	// windgust attack
	Animation* windgustAnimation = new Animation();
	windgustAnimation->setSpriteSheet(tex);
	windgustAnimation->addFrame(sf::IntRect(7 * 300, 250, 300, 250));

	addAnimation(GameObjectState::Fighting3, windgustAnimation);

	// trip over
	Animation* tripoverAnimation = new Animation();
	tripoverAnimation->setSpriteSheet(tex);
	for (int i = 0; i < 5; ++i) {
		tripoverAnimation->addFrame(sf::IntRect(i * 300, 750, 300, 250));
	}
	tripoverAnimation->setLooped(false);

	addAnimation(GameObjectState::TripOver, tripoverAnimation);

	// laying
	Animation* layingAnimation = new Animation();
	layingAnimation->setSpriteSheet(tex);
	layingAnimation->addFrame(sf::IntRect(4 * 300, 750, 300, 250));
	layingAnimation->addFrame(sf::IntRect(5 * 300, 750, 300, 250));
	layingAnimation->addFrame(sf::IntRect(6 * 300, 750, 300, 250));
	layingAnimation->addFrame(sf::IntRect(5 * 300, 750, 300, 250));

	addAnimation(GameObjectState::Laying, layingAnimation);

	// standup
	Animation* standupAnimation = new Animation();
	standupAnimation->setSpriteSheet(tex);
	for (int i = 8; i < 11; ++i) {
		standupAnimation->addFrame(sf::IntRect(i * 300, 750, 300, 250));
	}
	standupAnimation->setLooped(false);

	addAnimation(GameObjectState::Standup, standupAnimation);

	// initial values
	setState(GameObjectState::Idle);
	playCurrentAnimation(true);

	loadParticleSystem();
}

MovingBehavior* WolfBoss::createMovingBehavior(bool asAlly) {
	WalkingBehavior* behavior;

	behavior = new WolfBossMovingBehavior(this);
	behavior->setDistanceToAbyss(100.f);
	behavior->setApproachingDistance(10000.f);
	behavior->setMaxVelocityYDown(800.f);
	behavior->setMaxVelocityYUp(300.f);
	behavior->setMaxVelocityX(300.f);
	behavior->calculateJumpHeight();
	return behavior;
}

AttackingBehavior* WolfBoss::createAttackingBehavior(bool asAlly) {
	EnemyAttackingBehavior* behavior;
	behavior = new AggressiveBehavior(this);
	behavior->setAggroRange(10000.f);
	behavior->setAttackInput(std::bind(&WolfBoss::handleAttackInput, this));
	return behavior;
}

void WolfBoss::render(sf::RenderTarget& target) {
	Enemy::render(target);
	if (m_isDead) m_ps->render(target);
}

void WolfBoss::setDead() {
	if (m_isDead) return;
	Enemy::setDead();
	updateParticleSystemPosition();
}

int WolfBoss::getMentalStrength() const {
	return 4;
}

sf::Time WolfBoss::getConfiguredWaitingTime() const {
	return sf::Time::Zero;
}

void WolfBoss::updateParticleSystemPosition() {
	m_particleSpawner->center.x = getPosition().x + getBoundingBox()->width / 2.f;
	m_particleSpawner->center.y = getPosition().y + getBoundingBox()->height * (2.f / 3.f);
}

void WolfBoss::loadParticleSystem() {
	m_ps = new particles::TextureParticleSystem(300, g_resourceManager->getTexture(GlobalResource::TEX_PARTICLE_STAR));
	m_ps->additiveBlendMode = true;
	m_ps->emitRate = 100.f;

	// Generators
	auto spawner = m_ps->addSpawner<particles::DiskSpawner>();
	spawner->center = sf::Vector2f(getPosition().x + getBoundingBox()->width / 2.f, getPosition().y + getBoundingBox()->height / 2.f);
	spawner->radius = 20.f;
	m_particleSpawner = spawner;

	auto sizeGen = m_ps->addGenerator<particles::SizeGenerator>();
	sizeGen->minStartSize = 10.f;
	sizeGen->maxStartSize = 20.f;
	sizeGen->minEndSize = 0.f;
	sizeGen->maxEndSize = 2.f;

	auto colGen = m_ps->addGenerator<particles::ColorGenerator>();
	colGen->minStartCol = sf::Color(255, 255, 255, 255);
	colGen->maxStartCol = sf::Color(255, 255, 255, 255);
	colGen->minEndCol = sf::Color(255, 255, 255, 0);
	colGen->maxEndCol = sf::Color(255, 255, 255, 0);

	auto velGen = m_ps->addGenerator<particles::AngledVelocityGenerator>();
	velGen->minAngle = -45.f;
	velGen->maxAngle = 45.f;
	velGen->minStartSpeed = 50.f;
	velGen->maxStartSpeed = 70.f;

	auto timeGen = m_ps->addGenerator<particles::TimeGenerator>();
	timeGen->minTime = 2.f;
	timeGen->maxTime = 3.f;

	// Updaters
	m_ps->addUpdater<particles::TimeUpdater>();
	m_ps->addUpdater<particles::ColorUpdater>();
	m_ps->addUpdater<particles::EulerUpdater>();
	m_ps->addUpdater<particles::SizeUpdater>();
}

std::string WolfBoss::getSpritePath() const {
	return "res/assets/bosses/spritesheet_boss_wolfmonster.png";
}

std::string WolfBoss::getDeathSoundPath() const {
	return "res/sound/mob/cendric_death.ogg";
}


