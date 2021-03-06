/**
 * @file FRocketBattery.cpp
 * @brief Implementation file for FRocketBattery class
 * @date Created: Mar 3, 2009
 * @author Tom Stephens
 */

#include "weapons/FRocketBattery.h"

namespace Frontier {

FRocketBattery::FRocketBattery() {
	m_name="RB";
	m_fullName = "Rocket Battery";
	m_type=RB;
	m_range=3;
	m_nDice=2;
	m_ICMMod=-3;
	m_damageTableMod=-10;
	m_baseToHitProb = 40;
}

FRocketBattery::~FRocketBattery() {
	// TODO Auto-generated destructor stub
}

}
