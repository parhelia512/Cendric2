#include "Structs/SpellBean.h"

SpellBean SpellBean::getSpellBean(SpellID id)
{
	switch (id)
	{
	case SpellID::Chop:
		return DEFAULT_CHOP;
	case SpellID::FireBall:
		return DEFAULT_FIREBALL;
	case SpellID::IceBall:
		return DEFAULT_ICEBALL;
	case SpellID::Aureola:
		return DEFAULT_AUREOLA;
	case SpellID::DivineShield:
		return DEFAULT_DIVINESHIELD;
	case SpellID::Fear:
		return DEFAULT_FEAR;
	case SpellID::AntiGravity:
		return DEFAULT_ANTIGRAVITY;
	case SpellID::WindGust:
		return DEFAULT_WINDGUST;
	case SpellID::Leech:
		return DEFAULT_LEECH;
	case SpellID::IcyAmbush:
		return DEFAULT_ICYAMBUSH;
	default:
		return EMPTY_SPELL;
	}
}