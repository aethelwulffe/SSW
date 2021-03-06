/**
 * @file FMinelayerTest.cpp
 * @brief Implementation file for the FMinelayerTest class
 * @author Tom Stephens
 * @date Created: Jun 23, 2009
 */

#include "FMinelayerTest.h"

namespace FrontierTests {
using namespace Frontier;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( FMinelayerTest );

void FMinelayerTest::setUp(){
	m_v1 = createShip("Minelayer");
}

void FMinelayerTest::tearDown(){
	delete m_v1;
}

void FMinelayerTest::testConstructor(){
	CPPUNIT_ASSERT( m_v1->getMaxADF() == 1);
	CPPUNIT_ASSERT( m_v1->getADF() == 1);
	CPPUNIT_ASSERT( m_v1->getMaxMR() == 2);
	CPPUNIT_ASSERT( m_v1->getMR() == 2);
	CPPUNIT_ASSERT( m_v1->getMaxDCR() == 75);
	CPPUNIT_ASSERT( m_v1->getDCR() == 75);
	CPPUNIT_ASSERT( m_v1->getMaxHP() == 50);
	CPPUNIT_ASSERT( m_v1->getHP() == 50);
	CPPUNIT_ASSERT( m_v1->getHeading() == 0);
	CPPUNIT_ASSERT( m_v1->getIcon() != NULL);
	unsigned int id = m_v1->getID();
	CPPUNIT_ASSERT( id >= 0);
	std::ostringstream os;
	os << "Minelayer " << id;
	CPPUNIT_ASSERT( m_v1->getName() == os.str());
	CPPUNIT_ASSERT( m_v1->getOwner() == 0);
	CPPUNIT_ASSERT( m_v1->getSpeed() == 0);
	CPPUNIT_ASSERT( m_v1->getType() == "Minelayer");
	CPPUNIT_ASSERT( m_v1->getWeaponCount() == 4);
	CPPUNIT_ASSERT( m_v1->getWeaponString() == "LB  LB  SM(x4)  M(x20)  ");

	FMinelayer v;
}

}
