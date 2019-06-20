#pragma once

class CRAMainForm : public ui::WindowImplBase
{
public:
	CRAMainForm();
	~CRAMainForm();
public:
	/**
	* 一下三个接口是必须要覆写的接口，父类会调用这三个接口来构建窗口
	* GetSkinFolder		    接口设置你要绘制的窗口皮肤资源路径
	* GetSkinFile			接口设置你要绘制的窗口的 xml 描述文件
	* GetWindowClassName	接口设置窗口唯一的类名称
	*/
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;

	/**
	* 收到 WM_CREATE 消息时该函数会被调用，通常做一些控件初始化的操作
	*/
	virtual void InitWindow() override;

	/**
	* 收到 WM_CLOSE 消息时该函数会被调用
	*/
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	/**
	* @brief 窗口功能按钮被点击时调用
	* @param[in] param 携带的参数
	* @return 始终返回 true
	*/
	bool OnButtonClick(ui::EventArgs* param);
	static const std::wstring kClassName;
protected:
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	//定义托盘图标对象
	NOTIFYICONDATA m_trayIcon;
	//添加托盘图标(初始化)
	void AddTrayIcon();
	//处理托盘图标上的事件
	LRESULT OnTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

