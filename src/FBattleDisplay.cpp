/**
 * @file FBattleDispaly.cpp
 * @brief Implementation file for BattleDispaly class
 * @author Tom Stephens
 * @date Created:  Jul 11, 2008
 *
 */

//#include "FBattleDisplay.h"
#include "Frontier.h"
#include "FBattleScreen.h"
#include <wx/wx.h>

#define ICON_SIZE 50
#define BORDER 5
#define ZOOM_SIZE 30
const int leftOffset=BORDER+ZOOM_SIZE;

namespace Frontier {

FBattleDisplay::FBattleDisplay(wxWindow * parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString &name)
		: wxPanel( parent, id, pos, size, style, name ) {

	m_parent = (FBattleScreen *)parent;
	m_loaded = false;
	m_first = true;
	//set a blank sizer
	m_fgSizer1 = new wxFlexGridSizer( 1, 3, 0, 0 );

	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	wxColour black(wxT("#000000"));// black
	SetBackgroundColour(black);
	SetMinSize( wxSize( -1,120 ) );

	m_zoomImage.LoadFile("../data/zoom.png");

	/// set up the set speed controls
	m_fgSizer1 = new wxFlexGridSizer( 1, 3, 0, 0 );
	m_fgSizer1->SetFlexibleDirection( wxBOTH );
	m_fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	m_fgSizer1->Add( 50, 0, 1, wxEXPAND, 5 );
	m_spinCtrl1 = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 40,-1 ), wxSP_ARROW_KEYS, 0, 55, 10 );
	m_spinCtrl1->SetMaxSize( wxSize( 40,-1 ) );
	m_fgSizer1->Add( m_spinCtrl1, 0, wxALIGN_CENTER|wxALL, 5 );
	m_button1 = new wxButton( this, wxID_ANY, wxT("Set Speed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_fgSizer1->Add( m_button1, 0, wxALL, 5 );
	m_fgSizer1->Layout();
	m_fgSizer1->Hide(m_button1,true);
	m_fgSizer1->Hide(m_spinCtrl1,true);

	this->Connect(wxEVT_PAINT, wxPaintEventHandler(FBattleDisplay::onPaint));
	this->Connect( wxEVT_LEFT_UP, wxMouseEventHandler(FBattleDisplay::onLeftUp ),NULL,this);

}

FBattleDisplay::~FBattleDisplay() {
}

void FBattleDisplay::draw(wxDC &dc){
//	wxBitmap b("../icons/ufo.png");
//	dc.DrawBitmap(b, 5, 5);
	wxColour black(wxT("#000000"));// black
	dc.SetBackground(wxBrush(black));
	dc.DrawBitmap(wxBitmap(m_zoomImage),0,0);
	switch (m_parent->getState()){
	case BS_SetupPlanet:
		if (m_parent->getControlState()){
			drawPlacePlanet(dc);
		} else {
			drawPlanetChoices(dc);
		}
		break;
	case BS_SetupStation:
		drawPlaceStation(dc);
		break;
	case BS_SetupDefendFleet:
	case BS_SetupAttackFleet:
		if (m_parent->getControlState()){
			drawPlaceShip(dc);
		} else {
			if (m_parent->getPhase()==NONE){
				drawShipChoices(dc);
			} else {
				drawGetSpeed(dc);
			}
		}
		break;
	default:
		break;
	}

}
void FBattleDisplay::onPaint(wxPaintEvent & event){
//	std::cerr << "in FBattleDispaly::onPaint()" << std::endl;
	wxPaintDC dc(this);
	draw(dc);
}

void FBattleDisplay::onLeftUp(wxMouseEvent & event) {
//	wxCoord x,y;
//	event.GetPosition(&x,&y);
//	std::cerr << "The x and y positions of the click are " << x << ", " << y << std::endl;
	if (event.GetX() < ZOOM_SIZE){
		zoomMap(event);
	}
	switch (m_parent->getState()){
	case BS_SetupPlanet:
		if (m_parent->getControlState()==false){
			makePlanetChoice(event);
		}
		break;
	case BS_SetupDefendFleet:
	case BS_SetupAttackFleet:
		if (m_parent->getControlState()==false && m_parent->getPhase()==NONE){
			makeShipChoice(event);
		}
		break;
	default:
		break;
	}
	event.Skip();
}

void FBattleDisplay::drawPlanetChoices (wxDC &dc){
	wxColour white(wxT("#FFFFFF"));
	for (unsigned int i=0; i< m_imageList.size(); i++){
//		std::cerr << "Drawing planet " << i << std::endl;
		wxBitmap b (m_imageList[i].Scale(ICON_SIZE,ICON_SIZE));
		dc.DrawBitmap(b,ZOOM_SIZE+BORDER+i*ICON_SIZE,BORDER);
	}
	dc.SetTextForeground(white);
	dc.SetFont(wxFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL));
	dc.DrawText("Please select an icon to use for the planet.",leftOffset,2*BORDER+ICON_SIZE);

}

void FBattleDisplay::makePlanetChoice(wxMouseEvent & event){
	wxCoord x,y;
	event.GetPosition(&x,&y);
	int xp = (x-leftOffset)/ICON_SIZE;
	int yp = (y-BORDER)/ICON_SIZE;
	if ( y>=BORDER && yp == 0){  // there is only one row in this case
		if ( x>=leftOffset && xp < (int)(m_imageList.size() )) { // make sure we actually hit an icon
			m_parent->setPlanet(xp);  // set the index
			m_parent->toggleControlState();
			wxClientDC dc(this);
			Refresh();
//			std::cerr << "The selection position is (" << xp << "," << yp << ")" << std::endl;
		}
	}
}

void FBattleDisplay::drawPlacePlanet(wxDC &dc){
	wxColour white(wxT("#FFFFFF"));
	dc.SetTextForeground(white);
	dc.SetFont(wxFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL));
	dc.DrawText("Select the map hex where you would like to place the planet.",leftOffset,BORDER);

}

void FBattleDisplay::drawPlaceShip(wxDC &dc){
	wxColour white(wxT("#FFFFFF"));
	dc.SetTextForeground(white);
	dc.SetFont(wxFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL));
	std::string txt = "Select the map hex where you would like to place the ship.\n";
	txt += "Click once to place the ship and then move the mouse to select the\n";
	txt += "desired heading and click again to finalize placement.";
	dc.DrawText(txt,leftOffset,BORDER);

}

void FBattleDisplay::drawPlaceStation(wxDC &dc){
	wxColour white(wxT("#FFFFFF"));
	dc.SetTextForeground(white);
	dc.SetFont(wxFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL));
	dc.DrawText(std::string("Select the map hex where you would like to place the station.") +
			"\nIt must be adjacent to the planet.",leftOffset,BORDER);

}

void FBattleDisplay::drawShipChoices (wxDC &dc){
	wxColour white(wxT("#FFFFFF"));
	if (!m_loaded) {
		m_vList = m_parent->getShipList();
		m_loaded = true;
		m_parent->setDone(false);
	}
	for (unsigned int i=0; i< m_vList.size(); i++){
		if (m_vList[i]!=NULL){
		const wxImage *iptr = m_vList[i]->getIcon();
		wxImage im = iptr->Scale(ICON_SIZE,ICON_SIZE);
		wxBitmap b(im);
		dc.DrawBitmap(b,leftOffset+i*ICON_SIZE,BORDER);
		}
	}
	dc.SetTextForeground(white);
	dc.SetFont(wxFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL));
	dc.DrawText("Please select a ship to place on the map.",leftOffset,2*BORDER+ICON_SIZE);

}

void FBattleDisplay::zoomMap(wxMouseEvent & event){
	double rate = 1.5;  // rate of zoom per click
	if (event.GetY()<44) {
		m_parent->setScale(rate);
	} else if (event.GetY()>76){
		m_parent->setScale(1/rate);
	}
}

void FBattleDisplay::makeShipChoice(wxMouseEvent & event){
	static unsigned int count = 0;
	wxCoord x,y;
	event.GetPosition(&x,&y);
	int xp = (x-leftOffset)/ICON_SIZE;
	int yp = (y-BORDER)/ICON_SIZE;
	VehicleList vList = m_parent->getShipList();
	if ( y>=BORDER && yp == 0){  // there is only one row in this case
		if ( x>=leftOffset && xp < (int)(vList.size()) && m_vList[xp]!=NULL) { // make sure we actually hit an icon
			count++;
			m_parent->setShip(vList[xp]);  // set the index
			m_parent->toggleControlState();
			m_vList[xp]=NULL;
			wxClientDC dc(this);
			Refresh();
//			std::cerr << "The selection position is (" << xp << "," << yp << ")" << std::endl;
			if (count == m_vList.size()){
				count = 0;
				m_parent->setDone(true);
				m_loaded = false;
			}
		}
	}
}

void FBattleDisplay::drawGetSpeed(wxDC &dc){
	wxColour white(wxT("#FFFFFF"));

	if (m_first){
		this->SetSizer( m_fgSizer1 );
		m_fgSizer1->Show(m_spinCtrl1,true);
		m_fgSizer1->Show(m_button1,true);
		this->Layout();
		// Connect Events
		m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FBattleDisplay::onSetSpeed ), NULL, this );
		m_first = false;
//		Update();
	}

	dc.SetTextForeground(white);
	dc.SetFont(wxFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL));
	dc.DrawText("Please choose an initial speed for the ship.\nPress the 'Set Speed' button when done"
			,leftOffset,2*BORDER+ICON_SIZE);

}

void FBattleDisplay::onSetSpeed( wxCommandEvent& event ){
	// disconnect the button
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FBattleDisplay::onSetSpeed ), NULL, this );
	m_parent->getShip()->setSpeed(m_spinCtrl1->GetValue());
	// clear the old objects
	m_fgSizer1->Hide(m_button1,true);
	m_fgSizer1->Hide(m_spinCtrl1,true);

	m_first = true;
	m_parent->setPhase(NONE);
	if(m_parent->getDone()){
		if(m_parent->getState()==BS_SetupDefendFleet){
			m_parent->setState(BS_SetupAttackFleet);
		} else {
			m_parent->setState(BS_Battle);
		}
		m_parent->toggleSide();
	}
	event.Skip();
}

}