/**
 * @file FWeapon.cpp
 * @brief Implementation file for the FWeapon class
 * @date Created: Feb 27, 2009
 * @author: Tom Stephens
 */

#include "FWeapon.h"

using namespace Frontier;

FWeapon::FWeapon() {
	m_name="NAW";
	m_fullName = "Not a Weapon";
	m_type=NONE;
	m_range=0;
	m_nDice=0;
	m_dMod=0;
	m_MPO=false;
	m_FF=false;
	m_RD=false;
	m_maxAmmo=0;
	m_ICMMod=0;
	m_currentAmmo=m_maxAmmo;
	m_damageTableMod = 0;
}

FWeapon::~FWeapon() {

}

void FWeapon::fire(FVehicle * v){

}

const int FWeapon::save(std::ostream & os) const{
	write(os, m_type);
	write(os, m_maxAmmo);
	write(os, m_currentAmmo);
	return 0;
}

int FWeapon::load(std::istream &is){
	read(is, m_maxAmmo);
	read(is, m_currentAmmo);
	return 0;
}
