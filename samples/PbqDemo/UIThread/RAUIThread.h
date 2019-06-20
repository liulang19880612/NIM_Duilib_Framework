#pragma once

//////////////////////////////////////////////////////////////////////////
//   主线程（UI线程）类
//   liulang
//////////////////////////////////////////////////////////////////////////


class CRAUIThread : public nbase::FrameworkThread
{
public:
	CRAUIThread();
	~CRAUIThread();
private:
	/**
	* 虚函数，初始化主线程
	* @return void	无返回值
	*/
	virtual void Init() override;

	/**
	* 虚函数，主线程退出时，做一些清理工作
	* @return void	无返回值
	*/
	virtual void Cleanup() override;
};

