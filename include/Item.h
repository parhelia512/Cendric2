#pragma once

#include "global.h"

#include "DatabaseManager.h"
#include "Structs/AttributeData.h"

#include "Beans/ItemAttributeBean.h"
#include "Beans/ItemBean.h"
#include "Beans/ItemConvertibleBean.h"
#include "Beans/ItemSpellBean.h"
#include "Beans/ItemEquipmentBean.h"
#include "Beans/ItemEquipmentLightBean.h"
#include "Beans/ItemFoodBean.h"
#include "Beans/ItemWeaponBean.h"
#include "Beans/ItemWeaponSlotBean.h"
#include "Beans/ItemDocumentPageBean.h"
#include "Beans/ItemDocumentQuestBean.h"
#include "Beans/LevelitemBean.h"
#include "Beans/LevelitemFrameBean.h"
#include "Beans/LevelitemLightBean.h"

// An item in cendrics / a npcs / a mobs inventory
class Item {
	friend class ResourceManager;
protected:
	// constructor is protected, only the resource manager can create items
	Item(const std::string& itemID);
public:
	virtual ~Item();

	const std::string& getID() const;
	ItemType getType() const;
	const sf::Vector2i& getIconTextureLocation() const;
	const AttributeData& getAttributes() const;
	const sf::Time& getFoodDuration() const;
	// the items gold value
	int getValue() const;

	// getter for levelitem values
	const LevelitemBean& getLevelitemBean() const;
	const std::vector<LevelitemFrameBean>& getFrames() const;
	const LevelitemLightBean& getLevelitemLightBean() const;

	// getter for equipment values
	const ItemEquipmentBean& getEquipmentBean() const;
	const ItemEquipmentLightBean& getEquipmentLightBean() const;

	// getter for convertible beans
	const std::vector<ItemConvertibleBean>& getConvertibleBeans() const;

	// getter for document beans
	const std::vector<ItemDocumentPageBean>& getDocumentPageBeans() const;
	const ItemDocumentQuestBean& getDocumentQuestBean() const;

	// getter for spell bean
	const ItemSpellBean& getSpellBean() const;

	// returns whether this is a valid item
	bool isValid() const;
	// returns whether this item has a food component and is valid
	bool isConsumable() const;
	// returns whether this item has a convertible component and is valid
	bool isConvertible() const;
	// returns whether this item is a spell
	bool isSpell() const;
	// returns whether this item is a weapon and is valid
	bool isWeapon() const;
	// returns whether this item has at least one page and is valid
	bool isDocument() const;
	// returns whether this item is a levelitem with frames and is valid
	bool isLevelitem() const;
	// returns whether this item is an equipment item and is valid
	bool isEquipmentItem() const;
	// returns whether this equipment item has a light attached
	bool isEquipmentLightedItem() const;
	// returns whether this equipment item has a light attached
	bool isLevelitemLightedItem() const;

	static bool isEquipmentType(ItemType type);

protected:
	ItemBean m_itemBean;
	ItemFoodBean m_itemFoodBean;
	std::vector<ItemConvertibleBean> m_itemConvertibleBeans;
	ItemSpellBean m_itemSpellBean;
	ItemEquipmentBean m_itemEquipmentBean;
	ItemEquipmentLightBean m_itemEquipmentLightBean;
	LevelitemBean m_levelItemBean;
	std::vector<LevelitemFrameBean> m_levelItemFrameBeans;
	LevelitemLightBean m_levelitemLightBean;
	AttributeData m_attributeData;
	ItemWeaponBean m_itemWeaponBean;
	std::vector<ItemWeaponSlotBean> m_itemWeaponSlotBeans;
	std::vector<ItemDocumentPageBean> m_itemDocumentPageBeans;
	ItemDocumentQuestBean m_itemDocumentQuestBean;

	void checkItem();
	void initBeans(const std::string& itemID);

	bool m_isValid = false;
	bool m_isConsumable = false;
	bool m_isDocument = false;
	bool m_isWeapon = false;
	bool m_isLevelitem = false;
	bool m_isLevelitemLighted = false;
	bool m_isEquipment = false;
	bool m_isEquipmentLighted = false;
	bool m_isConvertible = false;
	bool m_isSpell = false;
};