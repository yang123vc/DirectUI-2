#include <Windows.h>
#include <CommCtrl.h>
#include "../DirectUI/DirectUI.h"
#include "MainHostWindow.h"
#include "MainElement.h"
#include "resource.h"
#define GetElement(x) pMain->FindDescendent(Value::CreateAtom((UCString)L#x)->GetAtom())

//#pragma comment(lib,"comctl32.lib")
#pragma comment(lib,"dui70.lib")
using namespace DirectUI;

HRESULT MainHostWindow::OnMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT*)
{
	OutputDebugString(L"OK?");
	switch (uMsg)
	{
	case WM_CREATE:MessageBox(GetHWND(), L"hello, world", L"Title", NULL); break;
	default:
		break;
	}
	return S_OK;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CoInitializeEx(NULL, 0);

	/* The first arg's valid value
	 * 7	win vista
	 * 8	win 7 (Checked)
	 * 9	win 08 r2
	 * 10	win 8
	 * 11	win 12
	 * 12	win 8.1
	 * 13	win 12 r2
	 * 14	win 10 (Checked)
	 */
	InitProcessPriv(14, NULL, 1, true);
	InitThread(3);

	//MainHostWindow* pwnd;
	MainHostWindow* pwnd;

	MainHostWindow::Create((UCString)L"HigHwindUI", (UCString)L"Direct UI Test", NULL, NULL, CW_USEDEFAULT, CW_USEDEFAULT, 644, 460, WS_EX_WINDOWEDGE, WS_OVERLAPPED | WS_CAPTION | WS_VISIBLE | WS_DLGFRAME | WS_SYSMENU, hInstance, 0, (NativeHWNDHost**)&pwnd);

	//pwnd->Initialize();

	DUIXmlParser* pParser;

	DUIXmlParser::Create(&pParser, NULL, NULL, NULL, NULL);

	// load duixml file
	pParser->EnableDesignMode(); // looks unable to do anything...
	auto hr = pParser->SetXMLFromResource(IDR_STYLE, hInstance, (HINSTANCE)hInstance);
	unsigned long Temp;
	Element* Temp2;
	Element* pMain;
	HWNDElement::Create(pwnd->GetHWND(),true,0,NULL,&Temp,(Element**)&Temp2);
	pParser->CreateElement((UCString)L"main", Temp2, NULL, NULL, (Element**)&pMain);
	pMain->SetVisible(true);
	pMain->EndDefer(Temp);
	pwnd->Host(pMain);
	pwnd->ShowWindow(SW_SHOW);

	// draw themed text
	HDC hDC = GetDC(pwnd->GetHWND());
	LPRECT rec = new RECT;
	rec->bottom = 400;
	rec->left = 10;
	rec->right = 500;
	rec->top = 10;
	int ret = DUIDrawShadowText(hDC, (UCString)L"GGGGG", -1, rec, 0, RGB(192,2,233));
	OutputDebugString(SUCCEEDED(ret)?L"OK":L"NO");
	ret = DrawText(hDC, L"GGG", -1, rec, DT_CALCRECT | DT_CENTER);

	// try to control the listView
	CCListView *list = (CCListView*)GetElement(listview);
	//list->SetBorderColor(RGB(20, 100, 180));
	//list->SetBorderGradientColor(RGB(0, 0, 0), RGB(255, 255, 255), 'a');
	//list->SetBorderThickness(2, 2, 2, 2);

	// Judge Info of pMain
	auto tx = list->GetWidth();

	StartMessagePump();

	UnInitProcessPriv(nullptr);

	CoUninitialize();

	return 0;
}