#include "GameStructures.h"

namespace Gigahrush {
	Item::Item(int _ID, std::string _name, std::string _description, std::string _useDescription, bool _canSpawn) :
		ID(_ID),
		name(_name),
		description(_description),
		useDescription(_useDescription),
		canSpawn(_canSpawn) {}
	Item::~Item() {}

	Component::Component(int _ID, std::string _name, std::string _description, std::string _useDescription, bool _canSpawn) :
		Item(_ID,_name,_description,_useDescription,_canSpawn) {}

	Weapon::Weapon(int _ID, std::string _name, std::string _description, std::string _useDescription, bool _canSpawn) :
		Item(_ID, _name, _description, _useDescription, _canSpawn) {}

	Food::Food(int _ID, std::string _name, std::string _description, std::string _useDescription, bool _canSpawn) :
		Item(_ID, _name, _description, _useDescription, _canSpawn) {}

	HealingItem::HealingItem(int _ID, std::string _name, std::string _description, std::string _useDescription, bool _canSpawn) :
		Item(_ID, _name, _description, _useDescription, _canSpawn) {}

	std::string Item::use(Player& ply) {
		return std::string("Вы использовали предмет!");
	}

	std::string Component::use(Player& ply) {
		return std::string("Вы не можете использовать компонент!");
	}

	std::string Weapon::use(Player& ply) {
		return std::string("Вы экипировали оружие!");
	}

	std::string Food::use(Player& ply) {
		return std::string("Вы сьели еду!");
	}

	std::string HealingItem::use(Player& ply) {
		return std::string("Вы вылечились!");
	}

	Enemy::Enemy(int _ID, std::string _name, std::string _description, std::vector<std::string> _replics, unsigned short int _health, unsigned short int _attack, std::vector<std::unique_ptr<Item>>&& _loot) :
		ID(_ID),
		name(_name),
		description(_description),
		replics(_replics),
		health(_health),
		attack(_attack),
		loot(std::move(_loot)) {}
	Enemy::~Enemy() {}

}