#include "Player.h"
#include "../effect/LevelUpEffects.h"

Player::Player(std::string input_name) :
    name(input_name), 
    level(1), 
    health(10), max_health(10),
    movement(1), 
    currentXp(0), xpRequired(2), 
    is_alive(true), 
    effect_counter(0) {
    
    ;
}

void Player::printDetails() {
    std::cout << name << ": L" << level << " (" << currentXp << "/" << xpRequired << ")" << '\n';
    std::cout << "Health: " << health << '/' << max_health << '\n';
    std::cout << "Movement: " << movement << "\n\n";
}

int Player::getMovement() {
    return this->movement;
}

void Player::takeDamage(int damage) {
    this->health -= damage;
    if (this->health <= 0) {
        this->is_alive = false;
    }
}

int Player::heal() {
    int original_health = this->health;
    this->health = this->max_health;
    return this->max_health - original_health;
}

int Player::heal(int h) {
    int original_health = this->health;
    this->health += h;
    if (this->health > this->max_health) {
        this->health = this->max_health;
    }
    return this->health - original_health;
}

void Player::levelUp() {
    this->currentXp -= this->xpRequired;
    this->xpRequired *= 2;
    this->level += 1;
    this->movement += 1;
    this->applyEffect(new Effect(EffectTypes::GAIN_MAX_HEALTH, 5));
    EffectsList* effects = getEffectsListFromLevel(this->level);
    this->applyEffect(effects->chooseEffect("You have levelled up to Level 2!"));
    delete effects;
}

void Player::levelDown() {
    this->xpRequired /= 2;
    this->currentXp += this->xpRequired;
    this->level -= 1;
    this->movement -= 1;
}

void Player::increaseMaxHealth(int h) {
    this->health += h;
    this->max_health += h;
}

void Player::gainExperience(int xp) {
    currentXp += xp;
    while (this->currentXp >= this->xpRequired) {
        this->levelUp();
    } 
    while (this->currentXp < 0) {
        this->levelDown();
    }
}

bool Player::isAlive() {
    return is_alive;
}

void Player::applyEffect(Effect* e) {
    e->applyEffect(this);
    this->effect_counter += 1;
    this->appliedEffects.addEffect(e);
}

void Player::undoEffect() {
    Effect* e = appliedEffects.popEffect();
    e->undoEffect(this);
    delete e;
}