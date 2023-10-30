#include "cbase.h"

#include "FlashManager.h"

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

#include "ienginevgui.h"
#include <vgui/isurface.h>
#include <vgui/IVGui.h>
#include <vgui/IInput.h>
#include <vgui_controls/Panel.h>
#include <tier3/tier3.h>

// This will store the HWND of the game window later
HWND hwndMain;

// Some macros to simply things later

#ifndef MSGBOX_FLASH
#define MSGBOX(text) MessageBoxA(hwndMain, text, "Mutation:Source", MB_OK);
#endif

#ifndef MSGBOX_NULL
#define MSGBOXN(text) MessageBoxA(NULL, text, "Mutation:Source", MB_OK);
#endif

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp)                        ((int)(short)LOWORD(lp))
#endif

#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp)                        ((int)(short)HIWORD(lp))
#endif

// Displays a MessageBox
void msgf(char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	char str_buffer[512];
	vsprintf(str_buffer, fmt, args);
	MSGBOX(str_buffer);
	va_end(args);
}

// Hooks
HRESULT APIENTRY d3dSceneHook(LPDIRECT3DDEVICE9 pDevice);
HRESULT(APIENTRY *SceneObject)(LPDIRECT3DDEVICE9 pDevice);

// Variables for WndProc hijacking
WNDPROC OldWndProc;
void InitWinProcHook();
LRESULT CALLBACK myWndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Flash and other D3D globals; would be nice to have all these variables in one place at the top
FlashManager* g_FlashManager = NULL;
IDirect3DTexture9* g_Texture = NULL;
IDirect3DDevice9* g_pD3DDevice = NULL;

// A small helper function to convert a string to a wide string
std::wstring StringToWString(const std::string& s)
{
	std::wstring temp(s.length(), L' ');
	std::copy(s.begin(), s.end(), temp.begin());
	return temp;
}

// Flash and D3D texture related vars
const IFlashDXPlayer::ETransparencyMode transparency_mode = IFlashDXPlayer::TMODE_OPAQUE;
const int num_textures_in_rotation = 2;
IDirect3DTexture9* g_texturesRotation[num_textures_in_rotation] = { NULL };
int g_currentTexture = 0;

FlashMovie::FlashMovie(std::string SWFPath, int Width, int Height, int screen_x, int screen_y)
{
	int w, h; engine->GetScreenSize(w, h);
	if (Width == -1) Width = w;
	if (Height == -1) Height = h;

	SWFPath = SWFPath.insert(0, "\\");
	SWFPath = SWFPath.insert(0, engine->GetGameDirectory());

	char* sz = const_cast<char*>(SWFPath.c_str());

	m_width = Width;
	m_height = Height;
	m_path = SWFPath;
	m_x = screen_x;
	m_y = screen_y;

	init = false;
}

std::string FlashMovie::GetPath()
{
	return m_path;
}

int FlashMovie::GetWidth()
{
	return m_width;
}

int FlashMovie::GetHeight()
{
	return m_height;
}

FlashMovie::~FlashMovie()
{

}

std::pair<int, int> FlashMovie::GetScreenPosition()
{
	return std::pair<int, int>(m_x, m_y);
}

void FlashMovie::ResizeMovie(int Width, int Height, IFlashDXPlayer* m_flashPlayer)
{
	int w = -1, h = -1;
	engine->GetScreenSize(w, h);

	if (Width == -1) Width = w;
	if (Height == -1) Height = h;

	m_width = Width;
	m_height = Height;

	if (m_flashPlayer)
		m_flashPlayer->ResizePlayer(Width, Height);
}

void FlashMovie::SetScreenPosition(uint x, uint y)
{
	m_x = x;
	m_y = y;
}

// Don't worry about how these functions work. I wish I knew who made them-- I found them over at MPGH

bool FlashManager::bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'x' && *pData != *bMask)
			return false;
	return (*szMask) == NULL;
}

DWORD FlashManager::FindPattern(DWORD dwAddress, DWORD dwLen, BYTE* bMask, char* szMask)
{
	for (DWORD i = 0; i < dwLen; i++)
		if (bCompare((BYTE*)(dwAddress + i), bMask, szMask))
			return (DWORD)(dwAddress + i);
	return 0;
}

void* FlashManager::DetourFunction(BYTE* source, const BYTE* destination, const int length)
{
	BYTE* jmp = (BYTE*)malloc(length + 5);
	DWORD dwBack;

	VirtualProtect(source, length, PAGE_EXECUTE_READWRITE, &dwBack);

	memcpy(jmp, source, length);
	jmp += length;

	jmp[0] = 0xE9;
	*(DWORD *)(jmp + 1) = (DWORD)(source + length - jmp) - 5;

	source[0] = 0xE9;
	*(DWORD*)(source + 1) = (DWORD)(destination - source) - 5;

	for (int i = 5; i < length; i++)
	{
		source[i] = 0x90;
	}

	VirtualProtect(source, length, dwBack, &dwBack);

	return (jmp - length);
}

FlashManager::FlashManager()
{
	engine->GetScreenSize(w, h);

	// Flash init
	m_flashDX = GetFlashToDirectXInstance();
	m_flashPlayer = m_flashDX->CreatePlayer(w, h);

	if (!m_flashPlayer)
	{
		MessageBox(NULL, "Flash Player failed to initialize.", "Error", MB_OK);
		abort();
	}

	m_playerASI = new ASInterface(m_flashPlayer);

	// DirectX hack
	DWORD ES_Address;
	DWORD* vtbl = 0;
	DWORD table = FindPattern((DWORD)GetModuleHandle("d3d9.dll"), 0x128000, (PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");
	memcpy(&vtbl, (void*)(table + 2), 4);
	ES_Address = vtbl[42];
	if (ES_Address)
		SceneObject = (HRESULT(WINAPI *)(LPDIRECT3DDEVICE9 pDevice))(DetourFunction((PBYTE)ES_Address, (PBYTE)d3dSceneHook, 5));
	else
	{
		MSGBOX("Error: Could not detour D3D9 EndScene() hook which is needed for Flash initialization.");
		abort();
	}

	// Set up default matrix
	Translation.x = 0;
	Translation.y = 0;
	currentPos.first = 0;
	currentPos.second = 0;
	Scaling.x = 1.0f;
	Scaling.y = 1.0f;
	D3DXMatrixTransformation2D(&Mat, NULL, 0, &Scaling, NULL, 0, &Translation);

	// Flash manager data
	playingFlashFile = -1;
	lastFlashIndex = -1;
	recreatedTargets = false;
	screenBlend = false;

	// Flash events
	ListenForGameEvent("flash_hud_toggle");
	ListenForGameEvent("render_flash_hud");

	// WinProc hack
	enableInputProcessing = true;
	InitWinProcHook();
}

void FlashManager::FireGameEvent(IGameEvent* event)
{
	const char* eventName = event->GetName();

	if (FStrEq(eventName, "flash_hud_toggle"))
	{
		if (event->GetBool("enable"))
			PlayFlashMovie(GetLastIndex());
		else
			StopPlayingMovie();
	}
	else if (FStrEq(eventName, "render_flash_hud"))
	{
		int flashIndex = -1;
		if ((flashIndex = g_FlashManager->IsMovieInList(event->GetString("file"))) == -1)
		{
			FlashMovie renderMovie(event->GetString("file"), event->GetInt("width"), event->GetInt("height"), event->GetInt("x"), event->GetInt("y"));
			flashIndex = g_FlashManager->AddFlashMovie(renderMovie);
		}
		else
		{
			// Update the old movie parameters
			if (m_movieArray[flashIndex].GetHeight() != event->GetInt("height") || m_movieArray[flashIndex].GetWidth() != event->GetInt("width"))
				ResizeMovie(flashIndex, event->GetInt("width"), event->GetInt("height"));

			m_movieArray[flashIndex].SetScreenPosition(event->GetInt("x"), event->GetInt("y"));
		}

		SetScreenBlending(event->GetBool("blend"));

		PlayFlashMovie(flashIndex);
	}
}

bool FlashManager::RecreateTargets(IDirect3DDevice9* pD3DDevice)
{
	HRESULT hr;

	int movieIndex = GetPlayingMovieIndex();
	int newWidth = -1, newHeight = -1;

	if (movieIndex > -1)
	{
		newWidth = m_movieArray[movieIndex].GetWidth();
		newHeight = m_movieArray[movieIndex].GetHeight();
	}
	else
	{
		newWidth = w;
		newHeight = h;
	}

	hr = pD3DDevice->CreateTexture(newWidth, newHeight, 1, 0, transparency_mode ? D3DFMT_A8R8G8B8 : D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &g_Texture, NULL);
	if (FAILED(hr))
		return false;

	D3DXCreateSprite(pD3DDevice, &Sprite);
	g_pD3DDevice = pD3DDevice;

	if (m_flashPlayer)
		m_flashPlayer->ResizePlayer(newWidth, newHeight);

	for (int i = 0; i < num_textures_in_rotation; ++i)
	{
		hr = pD3DDevice->CreateTexture(newWidth, newHeight, 1, 0,
			transparency_mode ? D3DFMT_A8R8G8B8 : D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, &g_texturesRotation[i], NULL);

		if (FAILED(hr))
			return false;
	}

	recreatedTargets = true;

	return true;
}

void FlashManager::SceneDataHook()
{
	if (!HasRecreatedTargets())
	{
		assert("Tried to use SceneDataHook without initialization of texture buffer");
		return;
	}

	if (!IsPlayingMovie())
		return;

	HRESULT hr;

	// Update flash movie as necessary
	unsigned int numDirtyRects; const RECT* dirtyRects;
	if (m_flashPlayer->IsNeedUpdate(NULL, &dirtyRects, &numDirtyRects))
	{
		IDirect3DTexture9* pTexToUpdate = g_texturesRotation[g_currentTexture];
		if (++g_currentTexture == num_textures_in_rotation)
			g_currentTexture = 0;

		IDirect3DSurface9* pSrcSurface;
		hr = pTexToUpdate->GetSurfaceLevel(0, &pSrcSurface);
		assert(SUCCEEDED(hr));

		HDC surfaceDC;
		hr = pSrcSurface->GetDC(&surfaceDC);
		assert(SUCCEEDED(hr));

		// Draw flash frame
		m_flashPlayer->DrawFrame(surfaceDC);

		hr = pSrcSurface->ReleaseDC(surfaceDC);
		assert(SUCCEEDED(hr));

		// Update our GUI texture
		IDirect3DSurface9* pDestSurface;
		hr = g_Texture->GetSurfaceLevel(0, &pDestSurface);
		assert(SUCCEEDED(hr));

		for (unsigned int i = 0; i < numDirtyRects; ++i)
		{
			POINT destPoint = { dirtyRects[i].left, dirtyRects[i].top };
			hr = g_pD3DDevice->UpdateSurface(pSrcSurface, dirtyRects + i, pDestSurface, &destPoint);
			assert(SUCCEEDED(hr));
		}

		pDestSurface->Release();
		pSrcSurface->Release();
	}

	// Render our flash file
	if (g_Texture)
	{
		// Generate our new position matrix
		currentPos = m_movieArray[playingFlashFile].GetScreenPosition();
		Translation.x = currentPos.first;
		Translation.y = currentPos.second;
		g_Texture->GetLevelDesc(0, &Desc);
		Scaling.x = w / (float)m_movieArray[playingFlashFile].GetWidth() /*/ (float)Desc.Width*/;
		Scaling.y = h / (float)m_movieArray[playingFlashFile].GetHeight() /*/ (float)Desc.Height*/;
		D3DXMatrixTransformation2D(&Mat, NULL, 0, &Scaling, NULL, 0, &Translation);

		DWORD oldBlendOP, DestBlend, SrcBlend;
		if (screenBlend)
		{
			// Store old
			g_pD3DDevice->GetRenderState(D3DRS_BLENDOP, &oldBlendOP);
			g_pD3DDevice->GetRenderState(D3DRS_DESTBLEND, &DestBlend);
			g_pD3DDevice->GetRenderState(D3DRS_SRCBLEND, &SrcBlend);

			// Set new; photoshop-like Screen filter. Remove the black background
			g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
			g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		}

		// Render sprite
		Sprite->Begin(0);
		Sprite->SetTransform(&Mat);
		Sprite->Draw(g_Texture, NULL, NULL, NULL, 0xFFFFFFFF);
		Sprite->End();

		// Reset blending
		if (screenBlend)
		{
			g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, oldBlendOP);
			g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, DestBlend);
			g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, SrcBlend);
		}
	}
}

void FlashManager::PlayFlashMovie(int index)
{
	if (index >= m_movieArray.size() || index < 0)
	{
		assert("Bad index");
		return;
	}

	FlashMovie movie = m_movieArray[index];

	bool loaded = m_flashPlayer->LoadMovie(StringToWString(movie.GetPath()).c_str());
	m_flashPlayer->SetTransparencyMode(transparency_mode);
	m_flashPlayer->SetBackgroundColor(RGB(0, 0, 0));

	if (!loaded)
	{
		std::string error = "Could not load flash file: \n";
		error += m_movieArray[index].GetPath();
		MSGBOX(error.c_str());
		assert("Flash load error");
		abort();
	}

	playingFlashFile = index;
	lastFlashIndex = index;
}

void FlashManager::SetScreenBlending(bool enableScreen)
{
	screenBlend = enableScreen;
}

IDirect3DDevice9* FlashManager::GetD3DDevice()
{
	return g_pD3DDevice;
}

FlashManager::~FlashManager()
{
	delete m_playerASI;
	m_flashDX->DestroyPlayer(m_flashPlayer);
}

bool FlashManager::HasRecreatedTargets()
{
	return recreatedTargets;
}

int FlashManager::IsMovieInList(const char* filename)
{
	for (int i = 0; i < m_movieArray.size(); i++)
	{
		if (m_movieArray[i].GetPath().compare(filename) == 0)
			return i;
	}

	return -1;
}

int FlashManager::GetPlayingMovieIndex()
{
	return playingFlashFile;
}

int FlashManager::GetLastIndex()
{
	return lastFlashIndex;
}

bool FlashManager::IsPlayingMovie()
{
	return (playingFlashFile > -1);
}

int FlashManager::AddFlashMovie(FlashMovie fl_movie)
{
	m_movieArray.push_back(fl_movie);
	return m_movieArray.size() - 1;
}

void FlashManager::HookFSCommand(std::string fscommand, void(*func)(const wchar_t* args))
{
	m_playerASI->AddFSCCallback(StringToWString(fscommand), func);
}

void FlashManager::ResizeMovie(int index, int Width, int Height)
{
	if (index >= m_movieArray.size() || index < 0)
	{
		assert("Bad index");
		return;
	}

	m_movieArray[index].ResizeMovie(Width, Height, m_flashPlayer);
}

void FlashManager::ChangeFrame(int frame)
{
	if (!IsPlayingMovie())
		return;

	m_flashPlayer->CallFrame(frame);
}

IFlashDXPlayer* FlashManager::GetFlashPlayer()
{
	return m_flashPlayer;
}

std::pair<int, int> FlashManager::GetCurrentPos()
{
	return currentPos;
}

void FlashManager::SetGameInputProcessing(bool enableInput)
{
	enableInputProcessing = enableInput;
}

bool FlashManager::IsGameInputProcessing()
{
	return enableInputProcessing;
}

void FlashManager::StopPlayingMovie()
{
	m_flashPlayer->StopPlaying();
	m_flashPlayer->LoadMovie(L"NULL");
	playingFlashFile = -1;
}

D3DXVECTOR2 FlashManager::GetScale()
{
	return Scaling;
}

HRESULT APIENTRY d3dSceneHook(LPDIRECT3DDEVICE9 pDevice)
{
	if (g_FlashManager)
	{
		if (g_FlashManager->IsPlayingMovie())
		{
			if (!g_FlashManager->HasRecreatedTargets())
				g_FlashManager->RecreateTargets(pDevice);

			g_FlashManager->SceneDataHook();
		}
	}

	return SceneObject(pDevice);
}

// A method to grab the parent HWND from our DLL
BOOL CALLBACK EnumWindowProc(HWND hwnd, LPARAM lParam)
{
	HINSTANCE hinst = (HINSTANCE)GetModuleHandle(NULL);

	if ((HINSTANCE)GetWindowLongPtr(hwnd, GWL_HINSTANCE) == hinst &&
		IsWindowVisible(hwnd))
	{
		hwndMain = hwnd;
		return FALSE;
	}
	else
		return TRUE;
}

void InitWinProcHook()
{
	hwndMain = NULL;
	EnumWindows(EnumWindowProc, 0);
	if (hwndMain == NULL)
	{
		MSGBOX("Failed to find the parent HWND. Tell a programmer");
		abort();
	}

	OldWndProc = (WNDPROC)SetWindowLong(hwndMain, GWL_WNDPROC, (LONG)myWndProcHook);
}

LRESULT CALLBACK myWndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (g_FlashManager)
	{
		IFlashDXPlayer* g_flashPlayer = g_FlashManager->GetFlashPlayer();
		bool enableinputs = g_FlashManager->IsGameInputProcessing();

		if (!g_FlashManager->IsPlayingMovie())
			return CallWindowProc(OldWndProc, hWnd, message, wParam, lParam);

		int mousex = GET_X_LPARAM(lParam);
		int mousey = GET_Y_LPARAM(lParam);
		if (g_FlashManager->IsPlayingMovie())
		{
			std::pair<int, int> currentPos = g_FlashManager->GetCurrentPos();
			mousex -= currentPos.first;
			mousey -= currentPos.second;

			D3DXVECTOR2 scale = g_FlashManager->GetScale();
			mousex /= scale.x;
			mousey /= scale.y;

			if (mousex < 0) mousex = 0;
			if (mousey < 0) mousey = 0;
		}

		switch (message)
		{
		case WM_MOUSEMOVE:
			if (g_flashPlayer)
				g_flashPlayer->SetMousePos(mousex, mousey);
			return (enableinputs) ? CallWindowProc(OldWndProc, hWnd, message, wParam, lParam) : 0;

		case WM_LBUTTONDOWN:
			if (g_flashPlayer)
				g_flashPlayer->SetMouseButtonState(mousex, mousey, IFlashDXPlayer::eMouse1, true);
			return (enableinputs) ? CallWindowProc(OldWndProc, hWnd, message, wParam, lParam) : 0;

		case WM_LBUTTONUP:
			if (g_flashPlayer)
				g_flashPlayer->SetMouseButtonState(mousex, mousey, IFlashDXPlayer::eMouse1, false);
			return (enableinputs) ? CallWindowProc(OldWndProc, hWnd, message, wParam, lParam) : 0;

		case WM_KEYDOWN:
			if (g_flashPlayer)
				g_flashPlayer->SendKey(true, (int)wParam, (int)lParam);
			return (enableinputs) ? CallWindowProc(OldWndProc, hWnd, message, wParam, lParam) : 0;

		case WM_KEYUP:
			if (g_flashPlayer)
				g_flashPlayer->SendKey(false, (int)wParam, (int)lParam);
			return (enableinputs) ? CallWindowProc(OldWndProc, hWnd, message, wParam, lParam) : 0;

		case WM_CHAR:
			if (g_flashPlayer)
				g_flashPlayer->SendChar((int)wParam, (int)lParam);
			return (enableinputs) ? CallWindowProc(OldWndProc, hWnd, message, wParam, lParam) : 0;

		case WM_SIZE:
			if (g_flashPlayer)
			{

			}
			return (enableinputs) ? CallWindowProc(OldWndProc, hWnd, message, wParam, lParam) : 0;

		case WM_SETCURSOR:
			if (g_flashPlayer)
			{
				static bool restoreCursor = true;
				if (LOWORD(lParam) != HTCLIENT)
					restoreCursor = true;

				if (restoreCursor)
				{
					restoreCursor = false;
					break;
				}
				return (enableinputs) ? CallWindowProc(OldWndProc, hWnd, message, wParam, lParam) : 1;
			}
			break;
		default:
			break;
		}
	}

	return CallWindowProc(OldWndProc, hWnd, message, wParam, lParam);
}