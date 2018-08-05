#pragma once

using namespace DirectUI;
class MainHostWindow :
	public NativeHWNDHost
{
public:

	MainHostWindow()
	{
		
	}

	~MainHostWindow()
	{
	}
	HRESULT OnMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT *);
};

