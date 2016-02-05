#include "MovableGameObject.h"

MovableGameObject::MovableGameObject() : AnimatedGameObject() {
	m_relativeVelocity.x = 0.f;
	m_relativeVelocity.y = 0.f;
}

void MovableGameObject::update(const sf::Time& frameTime) {
	sf::Vector2f position;
	calculateNextPosition(frameTime, position);
	setPosition(position);
	calculateNextVelocity(frameTime, m_velocity);
	AnimatedGameObject::update(frameTime);
	m_relativeVelocity = sf::Vector2f();
}

void MovableGameObject::calculateNextPosition(const sf::Time& frameTime, sf::Vector2f& nextPos) const {
	sf::Vector2f position = getPosition();
	sf::Vector2f nextVel;
	calculateNextVelocity(frameTime, nextVel);
	nextPos.x = position.x + (nextVel.x + m_relativeVelocity.x) * frameTime.asSeconds();
	nextPos.y = position.y + (nextVel.y + m_relativeVelocity.y) * frameTime.asSeconds();
}

void MovableGameObject::calculateUnboundedVelocity(const sf::Time& frameTime, sf::Vector2f& nextVel) const {
	nextVel.x = (m_velocity.x + m_acceleration.x * frameTime.asSeconds());
	nextVel.y = (m_velocity.y + m_acceleration.y * frameTime.asSeconds());
}

void MovableGameObject::boundVelocity(sf::Vector2f& vel) const {
	// check bounds
	if (vel.x > getConfiguredMaxVelocityX()) vel.x = getConfiguredMaxVelocityX();
	if (vel.x < -getConfiguredMaxVelocityX()) vel.x = -getConfiguredMaxVelocityX();
	if (vel.y > getConfiguredMaxVelocityYDown()) vel.y = getConfiguredMaxVelocityYDown();
	if (vel.y < -getConfiguredMaxVelocityYUp()) vel.y = -getConfiguredMaxVelocityYUp();
}

void MovableGameObject::calculateNextVelocity(const sf::Time& frameTime, sf::Vector2f& nextVel) const {
	calculateUnboundedVelocity(frameTime, nextVel);
	boundVelocity(nextVel);
}

void MovableGameObject::setAcceleration(const sf::Vector2f& acceleration) {
	m_acceleration = acceleration;
}

void MovableGameObject::setAccelerationX(float accelerationX) {
	m_acceleration.x = accelerationX;
}

void MovableGameObject::setAccelerationY(float accelerationY) {
	m_acceleration.y = accelerationY;
}

void MovableGameObject::addAccelerationX(float accelerationX) {
	m_acceleration.x += accelerationX;
}

void MovableGameObject::addAccelerationY(float accelerationY) {
	m_acceleration.y += accelerationY;
}

void MovableGameObject::setVelocity(const sf::Vector2f& velocity) {
	m_velocity = velocity;
}

void MovableGameObject::setVelocityX(float velocityX) {
	m_velocity.x = velocityX;
}

void MovableGameObject::setVelocityY(float velocityY) {
	m_velocity.y = velocityY;
}

void MovableGameObject::setRelativeVelocity(const sf::Vector2f& relVel) {
	m_relativeVelocity = relVel;
}

float MovableGameObject::getConfiguredMaxVelocityX() const {
	return 1000.0f;
}

float MovableGameObject::getConfiguredMaxVelocityYUp() const {
	return 1000.0f;
}

float MovableGameObject::getConfiguredMaxVelocityYDown() const {
	return 1000.0f;
}

const sf::Vector2f& MovableGameObject::getVelocity() const {
	return m_velocity;
}

const sf::Vector2f& MovableGameObject::getAcceleration() const {
	return m_acceleration;
}