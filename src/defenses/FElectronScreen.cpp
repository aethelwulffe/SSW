/**
 * @file FReflectiveHull.h
 * @brief Implementation file for FReflectiveHull class
 * @date Created: Feb 16, 2010
 * @author Tom Stephens
 */

#include "defenses/FElectronScreen.h"

namespace Frontier {

FElectronScreen::FElectronScreen() {
	m_name="ES";
	m_fullName = "Electron Screen";
	m_type=ES;
	m_maxAmmo=0;
	m_currentAmmo=m_maxAmmo;
	m_isDamaged = false;

}

FElectronScreen::~FElectronScreen() {
	// TODO Auto-generated destructor stub
}

}
