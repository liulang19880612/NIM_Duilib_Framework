#include "stdafx.h"
#include "RAMainForm.h"

const std::wstring CRAMainForm::kClassName = L"MainForm";

CRAMainForm::CRAMainForm()
{
}


CRAMainForm::~CRAMainForm()
{
}

std::wstring CRAMainForm::GetSkinFolder()
{
	return L"basic";
}

std::wstring CRAMainForm::GetSkinFile()
{
	return L"basic.xml";
}

std::wstring CRAMainForm::GetWindowClassName() const
{
	return kClassName;
}

void CRAMainForm::InitWindow()
{
	auto btn_dropDown = dynamic_cast<ui::Button*>(FindControl(L"main_menu_select_trangle"));
	if (btn_dropDown)
	{
		btn_dropDown->AttachClick(nbase::Bind(&CRAMainForm::OnButtonClick, this, std::placeholders::_1));
	}

	AddTrayIcon();
}
bool CRAMainForm::OnButtonClick(ui::EventArgs* param)
{
	if ( param && param->pSender && param->pSender->GetName() == L"main_menu_select_trangle")
	{
		return true;
	}
	else
	{
		return false;
	}
}
LRESULT CRAMainForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}
ui::Control* CRAMainForm::CreateControl(const std::wstring& pstrClass)
{
	ui::Control* pRet = nullptr;
	if ( pstrClass.compare(L"PartitionLine")==0)
	{
		pRet =  new PartitionLine;
	}
	return pRet;
}
LRESULT CRAMainForm::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	if ( uMsg == RA_DEFWM_TRAY_ICON_SHOWTASK)
	{
		lRes = OnTrayIcon(uMsg, wParam, lParam, bHandled);
	}
	else
	{
		lRes = __super::HandleMessage(uMsg, wParam, lParam);
	}
	return lRes;
}

void CRAMainForm::AddTrayIcon() 
{
	memset(&m_trayIcon, 0, sizeof(NOTIFYICONDATA));
	m_trayIcon.cbSize = sizeof(NOTIFYICONDATA);
	m_trayIcon.hIcon = ::LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_PBQDEMO));
	m_trayIcon.hWnd = GetHWND();
	lstrcpy(m_trayIcon.szTip, _T("富人区"));
	m_trayIcon.uCallbackMessage = RA_DEFWM_TRAY_ICON_SHOWTASK;
	m_trayIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD, &m_trayIcon);
	ShowWindow(SW_HIDE);
}
LRESULT CRAMainForm::OnTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	//如果在图标中单击左键则还原
	if (lParam == WM_LBUTTONDOWN)
	{
		//删除托盘图标
		Shell_NotifyIcon(NIM_DELETE, &m_trayIcon);
		//显示主窗口
		ShowWindow(SW_SHOWNORMAL);
	}
	//如果在图标中单击右键则弹出声明式菜单
	if (lParam == WM_RBUTTONDOWN)
	{
		//获取鼠标坐标
		POINT pt; GetCursorPos(&pt);
		//右击后点别地可以清除“右击出来的菜单”
		SetForegroundWindow(m_hWnd);
		//托盘菜单    win32程序使用的是HMENU，如果是MFC程序可以使用CMenu
		HMENU hMenu;
		//生成托盘菜单
		hMenu = CreatePopupMenu();
		//添加菜单,关键在于设置的一个标识符  WM_ONCLOSE 点击后会用到
		AppendMenu(hMenu, MF_STRING, WM_ONCLOSE, _T("Exit"));
		//弹出菜单,并把用户所选菜单项的标识符返回
		int cmd = TrackPopupMenu(hMenu, TPM_RETURNCMD, pt.x, pt.y, NULL, m_hWnd, NULL);
		//如果标识符是WM_ONCLOSE则关闭
		if (cmd == WM_ONCLOSE)
		{
			m_trayIcon.hIcon = NULL;
			Shell_NotifyIcon(NIM_DELETE, &m_trayIcon);
			//退出程序
			::PostQuitMessage(0);
		}
	}
	bHandled = true;
	return 0;
}