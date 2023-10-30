#include "cbase.h"
#include <GameEventListener.h>

class CFlashEnvironment : public CLogicalEntity, public CGameEventListener
{
private:
	COutputEvent m_FSOne, m_FSTwo, m_FSThree, m_FSFour;
	char* m_szFlashName;
	bool m_IsEnabled, enableScreenBlend;
	int m_xPos, m_yPos, m_Width, m_Height;

public:
	DECLARE_CLASS(CFlashEnvironment, CLogicalEntity);
	DECLARE_DATADESC();

	// Constructor
	CFlashEnvironment()
	{
		// make sure events are loaded
		gameeventmanager->LoadEventsFromFile("resource/modevents.res");

		// set defaults
		m_szFlashName = "env_flash filename not set";
		m_IsEnabled = false;
		m_xPos = 0;
		m_yPos = 0;
		m_Width = -1;
		m_Height = -1;

		// build our FSCommand table
		ListenForGameEvent("fscommand_one");
		ListenForGameEvent("fscommand_two");
		ListenForGameEvent("fscommand_three");
		ListenForGameEvent("fscommand_four");
	}

	void FireGameEvent(IGameEvent* pEvent)
	{
		if (!strcmp("fscommand_one", pEvent->GetName()))
			FSCommand1();
		else if (!strcmp("fscommand_two", pEvent->GetName()))
			FSCommand2();
		else if (!strcmp("fscommand_three", pEvent->GetName()))
			FSCommand3();
		else if (!strcmp("fscommand_four", pEvent->GetName()))
			FSCommand4();
	}

	// Output functions
	void FSCommand1();
	void FSCommand2();
	void FSCommand3();
	void FSCommand4();

	// Input functions
	void RenderFlashMovie(inputdata_t &inputData);
	void StopMovie(inputdata_t &inputData);
	void StartMovie(inputdata_t &inputData);
};

LINK_ENTITY_TO_CLASS(env_flash, CFlashEnvironment);

BEGIN_DATADESC(CFlashEnvironment)

// Stores the name of the flash movie to play
DEFINE_KEYFIELD(m_szFlashName, FIELD_STRING, "file"),

// Storage of whether or not our flash movie is "playing"
DEFINE_FIELD(m_IsEnabled, FIELD_BOOLEAN),

// X and Y position on the screen
DEFINE_KEYFIELD(m_xPos, FIELD_INTEGER, "x"),
DEFINE_KEYFIELD(m_yPos, FIELD_INTEGER, "y"),

// Width and Height
DEFINE_KEYFIELD(m_Width, FIELD_INTEGER, "width"),
DEFINE_KEYFIELD(m_Height, FIELD_INTEGER, "height"),

// Blending
DEFINE_KEYFIELD(enableScreenBlend, FIELD_BOOLEAN, "blend"),

// Links our input for rendering event
DEFINE_INPUTFUNC(FIELD_VOID, "RenderFlashMovie", RenderFlashMovie),
DEFINE_INPUTFUNC(FIELD_VOID, "StopMovie", StopMovie),
DEFINE_INPUTFUNC(FIELD_VOID, "StartMovie", StartMovie),

// Links our output member to the output name used by Hammer
DEFINE_OUTPUT(m_FSOne, "OnFSCommand1"),
DEFINE_OUTPUT(m_FSTwo, "OnFSCommand2"),
DEFINE_OUTPUT(m_FSThree, "OnFSCommand3"),
DEFINE_OUTPUT(m_FSFour, "OnFSCommand4"),

END_DATADESC()

//-----------------------------------------------------------------------------
// Purpose: Fire a network event to change rendering HUD
//-----------------------------------------------------------------------------
void CFlashEnvironment::RenderFlashMovie(inputdata_t &inputData)
{
	Msg("Starting render_flash_hud event with flash file %s", m_szFlashName);
	IGameEvent* pEvent = gameeventmanager->CreateEvent("render_flash_hud");
	pEvent->SetString("file", m_szFlashName);
	pEvent->SetInt("x", m_xPos);
	pEvent->SetInt("y", m_yPos);
	pEvent->SetInt("width", m_Width);
	pEvent->SetInt("height", m_Height);
	pEvent->SetBool("blend", enableScreenBlend);
	gameeventmanager->FireEvent(pEvent);
}

void CFlashEnvironment::StopMovie(inputdata_t &inputData)
{
	m_IsEnabled = false;
	IGameEvent* pEvent = gameeventmanager->CreateEvent("flash_hud_toggle");
	pEvent->SetBool("enable", m_IsEnabled);
	gameeventmanager->FireEvent(pEvent);
}

void CFlashEnvironment::StartMovie(inputdata_t &inputData)
{
	m_IsEnabled = true;
	IGameEvent* pEvent = gameeventmanager->CreateEvent("flash_hud_toggle");
	pEvent->SetBool("enable", m_IsEnabled);
	gameeventmanager->FireEvent(pEvent);
}

//-----------------------------------------------------------------------------
// Purpose: Fire Hammer events based on FSCommands
//-----------------------------------------------------------------------------

void CFlashEnvironment::FSCommand1()
{
	m_FSOne.FireOutput(this, this);
}

void CFlashEnvironment::FSCommand2()
{
	m_FSTwo.FireOutput(this, this);
}

void CFlashEnvironment::FSCommand3()
{
	m_FSThree.FireOutput(this, this);
}

void CFlashEnvironment::FSCommand4()
{
	m_FSFour.FireOutput(this, this);
}