/**
 * @file FAssaultCarrier.cpp
 * @brief Implementation file for Assault Carrier class
 * @author Tom Stephens
 * @date Created:  Feb 21, 2008
 *
 */
#include "ships/FAssaultCarrier.h"
#include <sstream>

namespace Frontier
{

FAssaultCarrier::FAssaultCarrier() {
	m_maxMR = 1;
	m_maxADF = 2;
	m_maxHP = 75;
	m_currentMR = 1;
	m_currentADF = 2;
	m_currentHP = 75;
	std::ostringstream os;
	os << "Assault Carrier " << m_ID;
	m_name = os.str();
	m_type = "AssaultCarrier";
	m_maxDCR=150;
	m_currentDCR=m_maxDCR;
	FWeapon *w = createWeapon(LB);
	m_weapons.push_back(w);
	w = createWeapon(PB);
	m_weapons.push_back(w);
	w = createWeapon(RB);
	w->setMaxAmmo(8);
	w->setCurrentAmmo(8);
	m_weapons.push_back(w);

}

FAssaultCarrier::~FAssaultCarrier(){
}

}