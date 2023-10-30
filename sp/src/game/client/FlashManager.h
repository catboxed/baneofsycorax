#pragma once

#include <Windows.h>
#include <TCHAR.h>
#include <Shlwapi.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <d3dx9mesh.h>
#include <ddraw.h>
#include <string>
#include <vector>
#include "IFlashDX.h"
#include "ASInterface.h"
#include <GameEventListener.h>

// This object acts as the Flash Container by loading SWF files and rendering textures
struct FlashMovie
{
private:
	int m_height, m_width, m_x, m_y;
	std::string m_path;
	bool init;

public:
	// Creates a FlashMovie container object. If Width and Height are not specified, the game window's width and height are used.
	FlashMovie(std::string SWFPath, int Width = -1, int Height = -1, int screen_x = 0, int screen_y = 0);

	// Destroys and unloads the Flash movie
	~FlashMovie();

	// Returns the flash movie absolute file path
	std::string GetPath();

	// Gets the user-defined flash movie width
	int GetWidth();

	// Gets the user-defined flash movie height
	int GetHeight();

	// Returns the x and y coordinates of the default screen position.
	std::pair<int, int> GetScreenPosition();

	// Sets the position of the movie on the screen
	void SetScreenPosition(uint x, uint y);


	// -----------------------------------------------------------------
	// The following in general should not be used by the end user.
	// -----------------------------------------------------------------

	// Resizes the FlashMovie to the specified width and height given a IFlashDXPlayer pointer. Use FlashManager's ResizeMovie instead of this.
	void ResizeMovie(int Width, int Height, IFlashDXPlayer* m_flashPlayer);
};

class FlashManager : public CGameEventListener
{
private:
	// Managment objects
	std::vector<FlashMovie> m_movieArray;
	int playingFlashFile, lastFlashIndex, w, h;
	bool recreatedTargets;
	bool enableInputProcessing;
	bool screenBlend;

	// D3D classes
	D3DXVECTOR2 Translation;
	D3DXMATRIX Mat;
	D3DXVECTOR2 Scaling;
	LPD3DXSPRITE Sprite;
	D3DSURFACE_DESC Desc;
	std::pair<int, int> currentPos;

	// Flash objects
	IFlashDX* m_flashDX;
	IFlashDXPlayer* m_flashPlayer;
	ASInterface* m_playerASI;

private:
	bool bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask);
	DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE* bMask, char* szMask);
	void* DetourFunction(BYTE* source, const BYTE* destination, const int length);

public:
	FlashManager();
	~FlashManager();

	// Adds a flash movie to the list and returns the index. Returns -1 if the renderer has not loaded completely.
	int AddFlashMovie(FlashMovie fl_movie);

	// Plays a flash movie provided an index. Use with AddFlashMovie()
	void PlayFlashMovie(int index);

	// Returns the index of the current movie that is playing, or -1 if no movie is playing.
	int GetPlayingMovieIndex();

	// Returns true if a flash movie is currently playing.
	bool IsPlayingMovie();

	// Hooks an ActionScript FSCommand with your function. That is, whenever fscommand() is called in flash, that FSCommand is registered with your c++ function.
	void HookFSCommand(std::string, void(*)(const wchar_t*));

	// Resizes a FlashMovie given the flash movie index.
	void ResizeMovie(int index, int Width, int Height);

	// Forces the playing flash movie to skip to the specified frame.
	void ChangeFrame(int frame);

	// Gets the rendered screen location of the flash movie.
	std::pair<int, int> GetCurrentPos();

	// Enables or disables input processing through the hijacked message pump. In other words, if input processing is disabled, every mouse/keyboard input
	// is sent only to Flash instead of both the game and Flash.
	void SetGameInputProcessing(bool enableInput);

	// Returns true if the game's input systems are processing.
	bool IsGameInputProcessing();

	// Unloads the flash movie and resets flash-related variables.
	void StopPlayingMovie();

	// Returns the last played movie's index
	int GetLastIndex();

	// Returns the index of the specified movie if it has already been added, or -1 if it has not
	int IsMovieInList(const char* filename);

	// Sets blend mode (true = photoshop-like Screen filter, false = opaque)
	void SetScreenBlending(bool enableScreen);

	// Returns the scale factor
	D3DXVECTOR2 GetScale();

	// -----------------------------------------------------------------
	// The following in general should not be used by the programmer.
	// -----------------------------------------------------------------

	// Returns true if the Flash manager has initialized all of its variables and has attained a pointer to the hacked D3D device
	bool HasRecreatedTargets();

	// Recreates D3D targets and assigns the d3d device pointer through the vtable hack
	bool RecreateTargets(IDirect3DDevice9* pD3DDevice);

	// Renders the flash movie onto the screen utilizing the direct 3d device pointer. Note: do not use, as it is used internally.
	void SceneDataHook();

	// Returns the d3d device pointer (in case you need it for your other projects).
	IDirect3DDevice9* GetD3DDevice();

	// Returns the IFlashDXPlayer pointer to utilize FlashDX manually.
	IFlashDXPlayer* GetFlashPlayer();

	// Fires a flash related event (either render_flash_hud or flash_hud_toggle)
	void FireGameEvent(IGameEvent* event);
};