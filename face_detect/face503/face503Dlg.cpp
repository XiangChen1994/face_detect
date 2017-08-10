
// face503Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "face503.h"
#include "face503Dlg.h"
#include "afxdialogex.h"
#define random(x) (rand()%x)
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cface503Dlg �Ի���




Cface503Dlg::Cface503Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cface503Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cface503Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cface503Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_PIC, &Cface503Dlg::OnBnClickedOpenPic)
	ON_BN_CLICKED(IDC_BUTTON2, &Cface503Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Cface503Dlg ��Ϣ�������

BOOL Cface503Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cface503Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cface503Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cface503Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HRESULT Cface503Dlg::ShowPic(CDC *pDC,CString lpstrFile,int x,int y, int nScrWidth, int nScrHeight)//��ָ��·���ļ����Ŵ���
{
	IPicture  *pPic;  
	IStream   *pStm;  
	BOOL      bResult;  

	HANDLE    hFile=NULL;  
	DWORD     dwFileSize,dwByteRead;  

	//��Ӳ���е�ͼ���ļ�  
	hFile=CreateFile(lpstrFile,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);  
	if (hFile!=INVALID_HANDLE_VALUE)  
	{  
		dwFileSize=GetFileSize(hFile,NULL);//��ȡ�ļ��ֽ���  
		if(dwFileSize==0xFFFFFFFF)  
		{
			CloseHandle(hFile);
			return E_FAIL;  
		}
	}  
	else  
	{  
		return E_FAIL;  
	}  


	//����ȫ�ִ洢�ռ�  
	HGLOBAL hGlobal=GlobalAlloc(GMEM_MOVEABLE,dwFileSize);  
	if(hGlobal==NULL)  
		return E_FAIL;  

	LPVOID  pvData =GlobalLock(hGlobal);  

	if(pvData==NULL)//���������ڴ��  
	{
		GlobalFree(hGlobal);
		return E_FAIL;  
	}
	ReadFile(hFile,pvData,dwFileSize,&dwByteRead,NULL);//���ļ������ڴ滺����  
	CloseHandle(hFile);//�رմ򿪵��ļ�  

	GlobalUnlock(hGlobal);  

	CreateStreamOnHGlobal(hGlobal,TRUE,&pStm);  

	//װ��ͼ���ļ�  
	bResult=OleLoadPicture(pStm,dwFileSize,TRUE,IID_IPicture,(LPVOID*)&pPic);  
	GlobalFree(hGlobal);

	if(FAILED(bResult))  
		return E_FAIL;  

	long   hmWidth;//ͼƬ����ʵ���  
	long   hmHeight;//ͼƬ����ʵ�߶�  
	pPic->get_Width(&hmWidth);  
	pPic->get_Height(&hmHeight);  


	//��ͼ���������Ļ�ϣ��е���BitBlt��  
	bResult=pPic->Render(pDC->m_hDC,x,y,nScrWidth,nScrHeight,0,hmHeight,hmWidth,-hmHeight,NULL);  

	pPic->Release();  

	if(SUCCEEDED(bResult))  
	{  
		return   S_OK;  
	}  
	else  
	{  
		return   E_FAIL;  
	} 
}

CString lpstrFile=_T("C:\\Users\\Administrator\\Desktop\\1.bmp");

void Cface503Dlg::OnBnClickedOpenPic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDC *pDc=GetDlgItem(IDC_SHOW)->GetDC();//�õ�dc


	ShowPic(pDc,lpstrFile,0,0, 180,180);


}



void Cface503Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDC *pDc1=GetDlgItem(IDC_DETECTION)->GetDC();//�õ�dc
	IplImage *jack = cvLoadImage("C:\\Users\\Administrator\\Desktop\\1.bmp");
	IplImage *src = jack;
	IplImage *dst0 = cvCreateImage(cvGetSize(jack), jack->depth, 1);
	IplImage *dst1 = cvCreateImage(cvGetSize(jack), jack->depth, 1);
	IplImage *dst2 = cvCreateImage(cvGetSize(jack), jack->depth, 1);
	IplImage *sub0 = cvCreateImage(cvGetSize(jack), jack->depth, 1);
	IplImage *sub1 = cvCreateImage(cvGetSize(jack), jack->depth, 1);
	IplImage *sub2 = cvCreateImage(cvGetSize(jack), jack->depth, 1);
	CvScalar all[11];
	cvSplit(src, dst0, dst1, dst2, NULL);
	for (int i = 1; i <= 10; i++) 
	{
		char ch[100];
		sprintf(ch, "%d", i); 
		CString ch_new(ch);
		CString num = _T("C:\\Users\\Administrator\\Desktop\\testimg\\");
		num = num + ch_new + _T(".bmp");
		//
		int len = WideCharToMultiByte(CP_ACP, 0, num, -1, NULL, 0, NULL, NULL);
		char *num_new = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, num, -1, num_new, len, NULL, NULL);
//		delete[] ptxtTemp;
		//
		IplImage *image = cvLoadImage(num_new);
		IplImage *dst3 = cvCreateImage(cvGetSize(image), image->depth, 1);
		IplImage *dst4 = cvCreateImage(cvGetSize(image), image->depth, 1);
		IplImage *dst5 = cvCreateImage(cvGetSize(image), image->depth, 1);
		cvSplit(image, dst3, dst4, dst5, NULL);
		cvSub(dst0, dst3, sub0);
		cvSub(dst1, dst4, sub1);
		cvSub(dst2, dst5, sub2);
		IplImage * result = cvCreateImage(cvGetSize(image), image->depth, 1);
		cvAdd(sub0, sub1, result);
		cvAdd(result, sub2, result);
		CvScalar a = cvSum(result);
		all[i] = a;
		cvReleaseImage(&image);
		cvReleaseImage(&dst3);
		cvReleaseImage(&dst4);
		cvReleaseImage(&dst5);
		cvReleaseImage(&result);
	}
	CvScalar min = all[1];
	int minimum;
	int m_id;
	for (int i = 1; i <= 10; i++)
	{
		if (all[i].val[0] <= min.val[0])
		{
			minimum = i;
			min = all[i];
			m_id=i;
		}


	}
	CString s_id;
	s_id.Format(_T("%d"),m_id);
	CString filName = _T("C:\\Users\\Administrator\\Desktop\\testimg\\");
	CString result_filename=filName+ "\\" + s_id + ".bmp" ;
	ShowPic(pDc1,result_filename,0,0, 180,180);
}
