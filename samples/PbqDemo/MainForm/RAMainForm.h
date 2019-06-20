#pragma once

class CRAMainForm : public ui::WindowImplBase
{
public:
	CRAMainForm();
	~CRAMainForm();
public:
	/**
	* һ�������ӿ��Ǳ���Ҫ��д�Ľӿڣ����������������ӿ�����������
	* GetSkinFolder		    �ӿ�������Ҫ���ƵĴ���Ƥ����Դ·��
	* GetSkinFile			�ӿ�������Ҫ���ƵĴ��ڵ� xml �����ļ�
	* GetWindowClassName	�ӿ����ô���Ψһ��������
	*/
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;

	/**
	* �յ� WM_CREATE ��Ϣʱ�ú����ᱻ���ã�ͨ����һЩ�ؼ���ʼ���Ĳ���
	*/
	virtual void InitWindow() override;

	/**
	* �յ� WM_CLOSE ��Ϣʱ�ú����ᱻ����
	*/
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	/**
	* @brief ���ڹ��ܰ�ť�����ʱ����
	* @param[in] param Я���Ĳ���
	* @return ʼ�շ��� true
	*/
	bool OnButtonClick(ui::EventArgs* param);
	static const std::wstring kClassName;
protected:
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	//��������ͼ�����
	NOTIFYICONDATA m_trayIcon;
	//�������ͼ��(��ʼ��)
	void AddTrayIcon();
	//��������ͼ���ϵ��¼�
	LRESULT OnTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

