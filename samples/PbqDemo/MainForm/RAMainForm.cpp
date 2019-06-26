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
	lstrcpy(m_trayIcon.szTip, _T("������"));
	m_trayIcon.uCallbackMessage = RA_DEFWM_TRAY_ICON_SHOWTASK;
	m_trayIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD, &m_trayIcon);
	ShowWindow(SW_HIDE);
}
LRESULT CRAMainForm::OnTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	//�����ͼ���е��������ԭ
	if (lParam == WM_LBUTTONDOWN)
	{
		//ɾ������ͼ��
		Shell_NotifyIcon(NIM_DELETE, &m_trayIcon);
		//��ʾ������
		ShowWindow(SW_SHOWNORMAL);
	}
	//�����ͼ���е����Ҽ��򵯳�����ʽ�˵�
	if (lParam == WM_RBUTTONDOWN)
	{
		//��ȡ�������
		POINT pt; GetCursorPos(&pt);
		//�һ�����ؿ���������һ������Ĳ˵���
		SetForegroundWindow(m_hWnd);
		//���̲˵�    win32����ʹ�õ���HMENU�������MFC�������ʹ��CMenu
		HMENU hMenu;
		//�������̲˵�
		hMenu = CreatePopupMenu();
		//��Ӳ˵�,�ؼ��������õ�һ����ʶ��  WM_ONCLOSE �������õ�
		AppendMenu(hMenu, MF_STRING, WM_ONCLOSE, _T("Exit"));
		//�����˵�,�����û���ѡ�˵���ı�ʶ������
		int cmd = TrackPopupMenu(hMenu, TPM_RETURNCMD, pt.x, pt.y, NULL, m_hWnd, NULL);
		//�����ʶ����WM_ONCLOSE��ر�
		if (cmd == WM_ONCLOSE)
		{
			m_trayIcon.hIcon = NULL;
			Shell_NotifyIcon(NIM_DELETE, &m_trayIcon);
			//�˳�����
			::PostQuitMessage(0);
		}
	}
	bHandled = true;
	return 0;
}