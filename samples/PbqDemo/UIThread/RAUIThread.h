#pragma once

//////////////////////////////////////////////////////////////////////////
//   ���̣߳�UI�̣߳���
//   liulang
//////////////////////////////////////////////////////////////////////////


class CRAUIThread : public nbase::FrameworkThread
{
public:
	CRAUIThread();
	~CRAUIThread();
private:
	/**
	* �麯������ʼ�����߳�
	* @return void	�޷���ֵ
	*/
	virtual void Init() override;

	/**
	* �麯�������߳��˳�ʱ����һЩ������
	* @return void	�޷���ֵ
	*/
	virtual void Cleanup() override;
};

