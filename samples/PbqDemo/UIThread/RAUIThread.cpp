#include "stdafx.h"
#include "RAUIThread.h"
#include "../MainForm/RAMainForm.h"

CRAUIThread::CRAUIThread() : nbase::FrameworkThread("UIMainThread")
{
}


CRAUIThread::~CRAUIThread()
{

}


void CRAUIThread::Init()
{
	nbase::ThreadManager::RegisterThread(kThreadUI);

	// ��ȡ��Դ·������ʼ��ȫ�ֲ���
	std::wstring theme_dir = QPath::GetAppPath();
#ifdef _DEBUG
	// Debug ģʽ��ʹ�ñ����ļ�����Ϊ��Դ
	// Ĭ��Ƥ��ʹ�� resources\\themes\\default
	// Ĭ������ʹ�� resources\\lang\\zh_CN
	// �����޸���ָ�� Startup �����������
	ui::GlobalManager::Startup(theme_dir + L"resources\\", ui::CreateControlCallback(), false);
#else
	// Release ģʽ��ʹ����Դ�е�ѹ������Ϊ��Դ
	// ��Դ�����뵽��Դ�б����Ϊ THEME����Դ����Ϊ IDR_THEME
	// �����Դʹ�õ��Ǳ��ص� zip �ļ�������Դ�е� zip ѹ����
	// ����ʹ�� OpenResZip ��һ�����غ����򿪱��ص���Դѹ����
	ui::GlobalManager::OpenResZip(MAKEINTRESOURCE(IDR_THEME), L"THEME", "");
	// ui::GlobalManager::OpenResZip(L"resources.zip", "");
	ui::GlobalManager::Startup(L"resources\\", ui::CreateControlCallback(), false);
#endif

	// ����һ��Ĭ�ϴ�����Ӱ�ľ��д���
	CRAMainForm* window = new CRAMainForm();
	window->Create(NULL, CRAMainForm::kClassName.c_str(), WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
	window->CenterWindow();
	window->ShowWindow();
}

void CRAUIThread::Cleanup()
{
	ui::GlobalManager::Shutdown();
	SetThreadWasQuitProperly(true);
	nbase::ThreadManager::UnregisterThread();
}