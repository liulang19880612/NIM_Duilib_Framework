// PbqDemo.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "RA.h"
#include "UIThread/RAUIThread.h"


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{	// �������߳�
    CRAUIThread thread;

	// ִ�����߳�ѭ��
	thread.RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop);
	return 0;
}

