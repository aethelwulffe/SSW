/**
 * @file FBattleBoard.h
 * @brief Header file for BattleBoard class
 * @author Tom Stephens
 * @date Created:  Jul 11, 2008
 *
 */

#ifndef __FBattleBoard__
#define __FBattleBoard__

#include <wx/scrolwin.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/frame.h>

#include "Frontier.h"
#include "strategic/FFleet.h"
#include "core/FPoint.h"
#include "core/FHexPath.h"
#include "core/FHexMap.h"

#include <map>

#define MR_TURN 		1
#define GRAVITY_TURN 	2

namespace Frontier {
class FBattleScreen;

/// data structure to hold information about each hex on the map
typedef struct {
	/// point object to hold coordinate of hex center
	FPoint pos;
	/// List of ships in hex
	VehicleList ships;
} hexData;

/// data structure to hold information about the movements of a ship during a turn.
typedef struct {
	/// flag for whether or not the ship has moved yet this turn
	bool hasMoved;
	/// list of waypoint hexes along the ship's path
	PointList waypoints;
	/// list of turns made at the waypoints
	std::vector<int> turns;
	/// list of hexes ship has moved through
	std::vector<FPoint> movedHexes;
	/// ship's final speed
	int speed;
	/// ship's starting heading
	int startHeading;
	/// ship's final heading
	int finalHeading;
	/// ship's current heading
	int curHeading;
	/// number of hexes it has currently moved
	int nMoved;
	/// flag for whether or not the ship had a turn due to gravity
//	bool gravityTurn;
	/// location gravity turn occurred as key and direction as value
	std::map <FPoint,int> gravityTurns;
	/// direction ship turned due to gravity
//	int gravityTurnDirection;
	/// Ship's path this turn
	FHexPath path;
} turnData;

/**
 * @brief Class for the Main tactical combat board
 *
 * This class implements the code for the FBattleBoard, the main
 * board used for the tactical combat game..
 *
 * @author Tom Stephens
 * @date Created:  Jul 11, 2008
 * @date Last Modified:  Mar 18, 2011
 */
class FBattleBoard : public wxScrolledWindow
{
public:
	/**
	 * @brief FBattleBoard constructor
	 *
	 * @author Tom Stephens
	 * @date Created:  Jul 11, 2008
	 * @date Last Modified:  Mar 30, 2009
	 */
	FBattleBoard(wxWindow * parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxHSCROLL|wxRAISED_BORDER|wxVSCROLL, const wxString &name = "BattleBoard" );
	/// Default destructor
	~FBattleBoard();

	void draw(wxDC &dc);
	void onPaint(wxPaintEvent & event);
	void onLeftUp(wxMouseEvent & event);

	/// sets the options for the planet icons
	void setPlanetImages(ImageList iList) { m_planetImages = iList; }
	/// sets the new scale for the map;
	void setScale(double factor);

	/**
	 * @brief Resets the turn information data
	 *
	 * This method clears and resets the m_turnInfo structure to hold information
	 * for the currently moving player.
	 *
	 * @author Tom Stephens
	 * @date Created:  Dec 03, 2008
	 * @date Last Modified:  Feb 18, 2011
	 */
	void resetMoveData();

	/**
	 * @brief Finalize movement phase
	 *
	 * This method iterates over the ships and updates their current status
	 * to reflect their movement.  It also marks them destroyed and removes
	 * them from play if they move off the map or run into a planet.
	 *
	 * @author Tom Stephens
	 * @date Created:  Feb 8, 2009
	 * @date Last Modified:  Mar 18, 2011
	 */
	void finalizeMove();

	/**
	 * @brief Computes the Weapons range hexes
	 *
	 * This method determines the hexes the currently selected weapon can
	 * fire at.
	 *
	 * @author Tom Stephens
	 * @date Created:  Apr 20, 2009
	 * @date Last Modified:  Apr 20, 2009
	 */
	void computeWeaponRange();

	/**
	 * @brief Removes a ship from the game map
	 *
	 * This method is currently very brute force.  It runs over all the hexes
	 * on the map and for hexes with ships looks at each ship to see if its ID
	 * matches the one passed in.  If so, it is removed from the list.
	 *
	 * @param id The ID of the ship to remove
	 *
	 * @author Tom Stephens
	 * @date Created:  Apr 30, 2009
	 * @date Last Modified:  Apr 30, 2009
	 */
	void removeShipFromGame(unsigned int id);

	/**
	 * @ brief Returns a list of vehicles in the hex containing the specified ship
	 *
	 * This method searches over the map and locates the hex that contains
	 * the specified ship, once found it returns the list of all ships in that hex.
	 *
	 * @param v the vehicle to locate
	 *
	 * @author Tom Stephens
	 * @date Created:  Apr 22, 2010
	 * @date Last Modified:  Apr 22, 2010
	 */
	VehicleList * getShipList(FVehicle * v);

protected:
	/// parent window
	FBattleScreen * m_parent;
	/// Scale of the map to draw
	double m_scale;
	/// Size of a hex across the flats (based on scale)
	int m_size;
	/// size of blank border around the map (based on scale)
	int m_trim;
	/// half the width across the flats (based on size)
	double m_d;
	/// one quarter of the height of the hex (based on size)
	double m_a;
	/// number of columns
	int m_nCol;
	/// number of rows
	int m_nRow;
	/// total width of map
	int m_width;
	/// total height of map
	int m_height;
	/// array of hex data for map
	hexData m_hexData[100][100];
	/// Flag for whether planet is present or not
	bool m_drawPlanet;
	/// position of planet
	FPoint m_planetPosition;
	/// list of possible planet images to display
	ImageList m_planetImages;
	/// planet index to draw
	int m_planetChoice;
	/// flag for whether or not we are setting the rotation of a placed ship
	bool m_setRotation;
	/// m_hexData entry for hex containing currently selected ship
	FPoint m_shipPos;
	/// list of hexes to highlight for movement
	std::vector<FPoint> m_movementHexes;
	/// list of hexes to highlight for left turn
	std::vector<FPoint> m_leftHexes;
	/// list of hexes to highlight for right turn
	std::vector<FPoint> m_rightHexes;
	/// flag for whether or not to draw the current ship's available path
	bool m_drawRoute;
	/// number of hexes moved
	int m_moved;
	/// list of turn data elements for each ship stored with the FVehicle ID value as the key
	std::map<unsigned int, turnData> m_turnInfo;
	/// set to contain valid target hexes for selected weapon
	PointSet m_targetHexes;
	/// set to contain valid target hexes for head on shot bonus
	PointSet m_headOnHexes;
	/// position on map to turn ship due to gravity
	/// location gravity turn occurred as key and direction as value
	std::map <FPoint,int> m_gravityTurns;
	// direction to turn ship due to gravity
//	int m_gravityTurnDirection;
	/// flag indicating that one gravity turn has already been made for this pass
	bool m_gravityTurnFlag;
	/// pointer to masking screen icon image
	wxImage * m_maskingScreenIcon;
	/// set of hexes with mines
	PointSet m_minedHexList;
	/// list of mined hexes triggered and their targets.
	FHexMap m_mineTargetList;
	/// player id of mine owner
	unsigned int m_mineOwner;


	/**
	 * @brief Draws the grid background
	 *
	 * This method draws the map grid background.  It takes into account the size of
	 * the buffer region around the map, the size of the hexes and the magnification and
	 * draws the grid and rescales the window appropriately.  It also takes into account
	 * the scrolled position of the map within the window.
	 *
	 * @param dc The device context to write to
	 *
	 * @author Tom Stephens
	 * @date Created:  Jul 19, 2008
	 * @date Last Modified:  Jul 30, 2008
	 */
	void drawGrid(wxDC &dc);

	/**
	 * @brief Sets all the map sizes based on the provided scale
	 *
	 * This method updates the scale of the map and updates all the drawing
	 * size constants based on the new scale. The scale is a simple ratio with
	 * a scale of 1.0 corresponding to hexes 50 pixels across the flats.
	 *
	 * @param scale  The new scale for the map
	 *
	 * @author Tom Stephens
	 * @date Created:  July 30, 2008
	 * @date last Modified:  July 30, 2008
	 */
	void setConstants(double scale);

	/**
	 * @brief Computes the centers of all the hexes
	 *
	 * This method uses the stored values for the various map scales to compute
	 * the center point of each hex on the map.
	 *
	 * @author Tom Stephens
	 * @date Created:  July 30, 2008
	 * @date last Modified:  Mar 30, 2009
	 */
	void computeCenters();

	/**
	 * @brief returns the array coordinates of the selected hex
	 *
	 * Using the mouse coordinates of the click and the scaling constants,
	 * this method determines the hex that was selected on the map.  It first
	 * estimates a small range of hexes to check and then computes the exact
	 * distance from the mouse click position to the center of each of those
	 * hexes.  The closest hex center is the one we want.
	 *
	 * If the mouse is clicked outside the hex grid the method returns false
	 * and the hex numbers are set to -1.  Otherwise the method returns true
	 * and the hex numbers correspond to the indices in the array of the
	 * selected hex
	 *
	 * @param x The x position of the mouse click
	 * @param y The y position of the mouse click
	 * @param a The x hex number
	 * @param b the y hex number
	 *
	 * @author Tom Stephens
	 * @date Created:  July 30, 2008
	 * @date last Modified:  Mar 30, 2009
	 */
	bool getHex(int x, int y, int &a, int &b);

	/**
	 * @brief Draws an object centered on the specified hex
	 *
	 * This method takes the specified object and draws it scaled and centered
	 * in the specified hex
	 *
	 * @param img The icon to be drawn
	 * @param p FPoint object containing the hex array coordinates to draw at
	 * @param rot The rotation of the image in hexsides relative to east
	 *
	 * @author Tom Stephens
	 * @date Created:  July 30, 2008
	 * @date Last Modified:  Mar 30, 2009
	 */
	void drawCenteredOnHex(wxImage img, FPoint p, int rot = 0);

	/**
	 * @brief Draws ships on map
	 *
	 * This method runs through all the hexes and if there are any ships
	 * there draws them on the map
	 *
	 * @author Tom Stephens
	 * @date Created:  Oct 13, 2008
	 * @date Last Modified:  Mar 30, 2009
	 */
	void drawShips();

	/**
	 * @brief Compute the heading value for the give mouse event
	 *
	 * This method compares the location of the mouse event to the location of the
	 * center of the hex the ship is in and determines the value to be stored as the heading
	 * of the currently selected ship.
	 *
	 * @param event The mouse event with the pointer coordinates
	 *
	 * @author Tom Stephens
	 * @date Created:  Oct 13, 2008
	 * @date Last Modified:  Mar 30, 2009
	 */
	int computeHeading(wxMouseEvent &event);

	/**
	 * @brief Handles responses to motions of the mouse
	 *
	 * When placing ships, this method updates the rotation of the currently selected ship as
	 * you move the mouse around to select it's initial rotation.
	 *
	 * @param event The mouse event with the pointer coordinates
	 *
	 * @author Tom Stephens
	 * @date Created:  Oct 13, 2008
	 * @date Last Modified:  Oct 13, 2008
	 */
	void onMotion(wxMouseEvent & event);

	/**
	 * @brief selects a vessel based on the clicked hex
	 *
	 * This method looks at the hex clicked and sets the current ship to the ship in
	 * the selected hex.  If more than one ship is in the hex a selection of choices
	 * is drawn
	 *
	 * @param event The mouse click event that triggered the call
	 *
	 * @author Tom Stephens
	 * @date Created:  Nov 1, 2008
	 * @date Last Modified:  Mar 18, 2011
	 */
	void selectVessel(wxMouseEvent &event);

	/**
	 * @brief Draws the current ships route
	 *
	 * This routine cycles over the m_movementHexes and m_ADFHexes vectors and highlights the appropriate
	 * hexes on the map
	 *
	 * @param dc The device context to draw on
	 *
	 * @author Tom Stephens
	 * @date Created:  Nov 21, 2008
	 * @date Last Modified:  Feb 13, 2009
	 */
	void drawRoute(wxDC &dc);

	/**
	 * @brief Sets the initial route for the selected ship
	 *
	 * This method fills in the m_movementHexes and m_ADFHexes vectors
	 * for the selected ship with a straight line going forward from
	 * it's current position.
	 *
	 * @author Tom Stephens
	 * @date Created:  Nov 21, 2008
	 * @date Last Modified:  Feb 20, 2011
	 */
	void setInitialRoute();

	/**
	 * @brief Checks to see if the selected hex in along the valid paths
	 *
	 * This method checks to see if the selected hex is on the current ships
	 * valid path and if it has any available MR.  If so, it draws the
	 * available paths for the ship.
	 *
	 * @param event The mouse event with the coordinates
	 *
	 * @author Tom Stephens
	 * @date Created:  Nov 30, 2008
	 * @date Last Modified:  Feb 20, 2011
	 */
	void checkForTurn(wxMouseEvent &event);

	/**
	 * @brief Highlights the hexes in the specified list
	 *
	 * This method iterates over the list of passed in hexes and highlights them
	 * approrpriately based on whether or not the ship has to move that far or
	 * it falls within the ADF range of the ship.
	 *
	 * @param dc The device context to draw on
	 * @param list The list of hexes to higlight
	 * @param count The number of hexes on the path already drawn
	 *
	 * @author Tom Stephens
	 * @date Created:  Dec 7, 2008
	 * @date Last Modified:  Apr 15, 2009
	 */
	void drawRouteHexes(wxDC &dc, PointList list, int count=1);

	/**
	 * @brief Runs through a list of hexes to see if the current one is there
	 *
	 * This method runs through a list of hexes and checks its coordinates against
	 * a reference hex position.  If it is found, the method returns true.  If it is
	 * not found it returns false.  It also returns the position in the list of the
	 * matching hex
	 *
	 * @param list The list of hexes to check
	 * @param ref The reference hex to check against
	 * @param count The position in the list where the match occured
	 *
	 * @author Tom Stephens
	 * @date Creatd:  Dec 24, 2008
	 * @date Last Modified:  Mar 30, 2009
	 */
	bool findHexInList(PointList list, FPoint ref, int &count);

	/**
	 * @brief draws a line connecting the hexes in the specified list
	 *
	 * This method iterates over the list of passed in hexes and highlights them
	 * approrpriately based on whether or not the ship has to move that far or
	 * it falls within the ADF range of the ship.
	 *
	 * @param dc The device context to draw on
	 * @param list The list of hexes to higlight
	 * @param current  Flag for whether or not you are drawing the movement for the currently selected ship or not
	 *
	 * @author Tom Stephens
	 * @date Created:  Feb 8, 2009
	 * @date Last Modified:  Feb 18, 2011
	 */
	void drawMovedHexes(wxDC &dc, PointList list, bool current=false);

	/**
	 * @brief Compute the remaining moves for the current ship
	 *
	 * @param start the hex to start computing from
	 *
	 * @author Tom Stephens
	 * @date Created:  Feb 8, 2009
	 * @date Last Modified:  Feb 18, 2011
	 */
	void computeRemainingMoves(FPoint start);

	/**
	 * @brief Checks to see if all the ships are done moving
	 *
	 * This method iterates through all the current players ships and checks to see
	 * if they have moved at least the minimum distance required by their current
	 * speed and ADF or if they have moved off the map or are running into a planet.
	 *
	 * @author Tom Stephens
	 * @date Created:  Feb 8, 2009
	 * @date Last Modified:  Feb 18, 2011
	 */
	void checkMoveStatus();

	/**
	 * @brief Turns ship and keeps heading value in proper range
	 *
	 * @param heading The ships inital heading
	 * @param turn The turn direction (-1 left, 1 right)
	 *
	 * @author Tom Stephens
	 * @date Created:  Feb 13, 2009
	 * @date Last Modified:  Feb 13, 2009
	 */
	int turnShip(int & heading, int turn);

	/**
	 * @brief Draws a box on the screen with a list of ships to choose from
	 *
	 * This method draws a box on the screen that lists all the ships in the
	 * supplied Vehicle list.  Once one of the ship names are selected, it
	 * returns a pointer to the specified ship.
	 *
	 * @param v The currently selected vehicle
	 * @param list The list of ships to display.
	 *
	 * @author Tom Stephens
	 * @date Created:  Feb 13, 2009
	 * @date Last Modified:  Apr 20, 2009
	 */
	FVehicle * pickShip(const FVehicle *v, const VehicleList & list);

	/**
	 * @brief Draws weapon range hexes on map
	 *
	 * This method determines whether the weapon is forward firing or not
	 * and calls the appropriate method to draw the range hexes
	 *
	 * @param dc The device context to draw on
	 *
	 * @author Tom Stephens
	 * @date Created:  Apr 15, 2009
	 * @date Last Modified:  Apr 15, 2009
	 */
	void drawWeaponRange(wxDC &dc);

	/**
	 * @brief Computes weapon range hexes on map for FF weapons
	 *
	 * This method determines which hexes are in the forward
	 * firing range of the weapon and highlights them on the map
	 * It emphasizes the hexes that get the +10 direct fire bonus.
	 *
	 * @param pos The position to compute the range from.  Defaults to m_shipPos
	 * @param tList The list of target points to fill in.  This defaults to m_targetHexes
	 * @param hList The list of head on target points to fill in.  This defaults to m_headOnHexes
	 * @param heading The heading to compute the range from
	 *
	 * @author Tom Stephens
	 * @date Created:  Apr 15, 2009
	 * @date Last Modified:  Apr 26, 2009
	 */
	void computeFFRange(FPoint &pos, PointSet & tList, PointSet & hList, int heading = -1);

	/**
	 * @brief Computes weapon range hexes on map for battery weapons
	 *
	 * This method highlights all the hexes on the map where the
	 * the battery weapon can fire.
	 *
	 * @param pos The position to compute the range from.  Defaults to m_shipPos
	 * @param tList The list of target points to fill in  This defaults to m_targetHexes
	 *
	 * @author Tom Stephens
	 * @date Created:  Apr 15, 2009
	 * @date Last Modified:  Apr 28, 2009
	 */
	void computeBatteryRange(FPoint &pos, PointSet & tList);

	/**
	 * @brief Draws a shaded hex on the map
	 *
	 * This method shades in the hex at the specified point with the specified color.
	 * It currently uses a hashed pattern for the fill.
	 *
	 * @param dc The device context to write to
	 * @param c The color to use for the fill
	 * @param p The position of the hex to fill in.
	 *
	 * @param dc The device context to draw on
	 *
	 * @author Tom Stephens
	 * @date Created:  Apr 15, 2009
	 * @date Last Modified:  Apr 15, 2009
	 */
	void drawShadedHex(wxDC& dc, wxColour c, FPoint p);

	/**
	 * @brief Draws the name of the target of the current weapon
	 *
	 * This draws the name of the target of theh current weapon in a small
	 * box in the top left corner of the screen.
	 *
	 * @param dc The device context to draw on
	 *
	 * @author Tom Stephens
	 * @date Created:  Apr 20, 2009
	 * @date Last Modified:  Apr 20, 2009
	 */
	void drawTarget(wxDC &dc);

	/**
	 * @brief Sets the target and range if the selected vessel is a valid target
	 *
	 * This method determines if the selected vessel is a valid target for the
	 * selected weapon.  If so it assigns the target vessel and range to the selected
	 * weapon.  If not, it does nothing.
	 *
	 * If the non-moving player is targeting, it loops over the selected vessels
	 * movement path to find the point it passed closest to the firing vessel.
	 *
	 * If the moving player is targeting, it loops over the moving vessel's path
	 * and computes the range for the weapon at each position and looks to see
	 * if the target is in range.
	 *
	 * In both cases, it stores the closest range for the target
	 *
	 * @param v Pointer to the selected target vessel object
	 * @param p the hex coordinate of the selected target
	 *
	 * @author Tom Stephens
	 * @date Created:  Apr 24, 2009
	 * @date Last Modified:  Feb 20, 2011
	 */
	void setIfValidTarget(FVehicle *v, FPoint p);

	/**
	 * @brief computes the full range of targets for a moved ship's weapon
	 *
	 * This method loops over the path of a moved ships and computes the hexes
	 * that the selected weapon can fire into over the course of it's entire move.
	 *
	 * @author Tom Stephens
	 * @date Created:  May 4, 2009
	 * @date Last Modified:  Feb 20, 2011
	 */
	void computeMovedWeaponRange();

	/**
	 * @brief Checks to see if hex is a planet position
	 *
	 * This method treats a collision in the physics sense, either a
	 * head on collision or a near miss that deflects the path of the ship
	 * involved i the "collision".  It either returns a bad hex if there
	 * would be a head on collision or appropriately turns the ship for a
	 * near miss.
	 *
	 * @param currentHex The hex to check
	 * @param currentHeading The current heading of the ship
	 *
	 * @author Tom Stephens
	 * @date Created:  May 11, 2009
	 * @date Last Modified:  Feb 18, 2011
	 */
	void checkForPlanetCollision(FPoint & currentHex, int & currentHeading);

	/**
	 * @brief computes movement along a heading
	 *
	 * This method computes the movement path for a given starting point and
	 * heading taking into account any planets and their gravity along the way
	 *
	 * @param list The list to store the movement hexes in
	 * @param hex The starting hex
	 * @param heading The heading of the ship
	 *
	 * @author Tom Stephens
	 * @date Create:  May 13, 2009
	 * @date Last Modified:  Feb 18, 2011
	 */
	void computePath(PointList &list, FPoint hex, int heading);

	/**
	 * @brief Determines turn direction caused by a planet
	 *
	 * This method determines which direction the ship should turn when
	 * it passes close to a planet
	 *
	 * @param currentHex The current hex of the ship
	 * @param currentHeading The heading of the ship
	 *
	 * @author Tom Stephens
	 * @date Create:  May 14, 2009
	 * @date Last Modified:  Feb 18, 2011
	 */
	int getPlanetTurnDirection(FPoint currentHex, int currentHeading);

	/**
	 * @brief updated path for forced turns
	 *
	 * This method updates the movement information properly for ships
	 * that are forced to turn due to navigation hit damage.
	 *
	 * @param ship The ship that is moving
	 * @param curHeading The heading of the ship
	 * @param current The current hex of the ship
	 *
	 * @author Tom Stephens
	 * @date Create:  Feb 15, 2011
	 * @date Last Modified:  Feb 18, 2011
	 */
	int forceTurn(FVehicle * ship, int curHeading, FPoint current);

	/**
	 * @brief
	 *
	 *
	 *
	 * @param v The currently selected vehicle
	 * @param list The list of ships to display.
	 *
	 * @author Tom Stephens
	 * @date Created:  Feb 13, 2009
	 * @date Last Modified:  Feb 20, 2011
	 */
	FVehicle * pickTarget(const FVehicle *v, const VehicleList & list);

	/**
	 * @brief Highlights all the hexes with mines
	 *
	 * This method loops over the list of mined hexes and highlights
	 * them for identification
	 *
	 * @param dc The device context to draw on
	 *
	 * @author Tom Stephens
	 * @date Created:  Mar 14, 2011
	 * @date Last Modified:  Mar 18, 2011
	 */
	void drawMinedHexes(wxDC &dc);


	/**
	 * @brief Handles placement of mines on map
	 *
	 * This method checkes the selected hex to determine if a
	 * mine is currently in that hex.  If not, one is added.  if a mine
	 * is already there, nothing is done
	 *
	 * @param h The hex to add the mine to.
	 *
	 * @author Tom Stephens
	 * @date Created:  Mar 14, 2011
	 * @date Last Modified:  Mar 14, 2011
	 */
	void placeMine(FPoint h);

	/**
	 * @brief Check to see if you can place a mine in the specified hex
	 *
	 * This method checks to see if the passed in hex is in the path traveled
	 * by the selected ship.  If it is, it is considered 'minable' and will
	 * allow mines to be placed there.
	 *
	 * @param hex The hex to check
	 *
	 * @author Tom Stephens
	 * @date Created:  Mar 18, 2011
	 * @date Last Modified:  Mar 18, 2011
	 */
	bool isHexMinable(FPoint hex);

	/**
	 * @brief Check to see if a ship hit a mine
	 *
	 * This method checks the path of the moving ship to see if it passed through
	 * a mined hex.  If so, the ship is added to a list of ships damaged by mines
	 * along with the hex that the mine was in.  These lists will be used to allow
	 * ICM's to be applied to defense against the mines
	 *
	 * @param v Pointer to the ship object we are checking.
	 *
	 * @author Tom Stephens
	 * @date Created:  Mar 18, 2011
	 * @date Last Modified:  Mar 18, 2011
	 */
	void checkForMines(FVehicle * v);
	/**
	 * @brief Apply damage to any ships that passed through mines
	 *
	 * This method visits each hex that had ships trigger mines and applies
	 * the damage from those mines after first allowing the moving player
	 * to apply ICM's towards the mine's chance to hit.
	 *
	 * All damage from the mines are immediately applied to the ships that
	 * triggered them.
	 *
	 * @author Tom Stephens
	 * @date Created:  Mar 18, 2011
	 * @date Last Modified:  Mar 24, 2011
	 */
	void applyMineDamage();
};

}

#endif //__FBattleBoard__
