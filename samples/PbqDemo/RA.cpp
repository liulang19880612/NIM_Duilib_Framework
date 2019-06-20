// PbqDemo.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "RA.h"
#include "UIThread/RAUIThread.h"


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{	// 创建主线程
    CRAUIThread thread;

	// 执行主线程循环
	thread.RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop);
	return 0;
}

