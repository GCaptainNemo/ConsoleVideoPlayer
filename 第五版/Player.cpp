#include "pch.h"
#include "Player.h"
using namespace std;
using namespace cv;
Player::Player()
{
	FramesNum = 0;
	FrameWidth = 1920;
	FrameHeight = 1080;
	speed = 1.0;
	FrameRate = 30.0;
}

void Player::SetPlayerConfig(string cmd)
{
	string filename=cmd;
	double sp;
	//������������
	for (int i = 0; i < cmd.length(); i++) {
		if (cmd[i] == ' ') {
			filename = cmd.substr(0, i);
			try { sp = stod(cmd.substr(i)); speed = sp; }
			catch (exception) {
				cout << "�������Ƶ��������";
				speed = 1.0;
			}
			break;
		}
	}
	GetFrameFromVideo(filename);
}

void Player::SetStdWindow(HANDLE hd, HWND hwnd)
{
	MyHandle = hd;
	MyHwnd = hwnd;
}

void Player::SetPixelSize(int size)
{
	Myfontsize = size;
	WCHAR myFont[] = TEXT("Arial");
	_CONSOLE_FONT_INFOEX fontinfo = { sizeof(CONSOLE_FONT_INFOEX) ,1,{Myfontsize,Myfontsize},TMPF_FIXED_PITCH,400, *myFont };
	SetCurrentConsoleFontEx(MyHandle, false, &fontinfo);
}

void Player::Output_to_file()
{
	ofstream file;
	file.open("set.txt", std::ios::out);
	file << Myfontsize << endl;
	file.close();
}

void Player::Gain_date_from_file()
{
	//��������洢����
	int data[10];
	ifstream file;
	file.open("set.txt");
	//��ȡ��������
	for (int i = 0; !file.eof(); i++) {
		file >> data[i];
	}
	Myfontsize = data[0];
	cout << "Size:" << Myfontsize << endl;
	file.close();

}

int Player::Get_Myfontsize()
{
	return Myfontsize;
}

void Player::Set()
{
	double key = 1;
	cout << "�Ƿ���Ҫ�������ã�����1�������ã�����ʹ��Ĭ������" << endl;
	cin >> key;
	if (key == 1) {
		SetPixelSize();
		Output_to_file();
	}
	else {
		Gain_date_from_file();
		SetPixelSize(Get_Myfontsize());
	}

}

void Player::SetWindowConfig()
{
	//�õ���Ļ����
	int screen_width = GetSystemMetrics(SM_CXSCREEN);

	//�õ���Ļ���
	int screen_length = GetSystemMetrics(SM_CYSCREEN);

	//��ȡhwnd�Ĵ�����Ϣ��GWL_STYLE��ȡ���ڷ����Ϣ
	//ע�⣺������һ�������ƴ���010101010101011�ȵȹ�32λ���ɵģ�ÿһλ����һ������
	LONG  l_Winstyle = GetWindowLong(MyHwnd, GWL_STYLE);

	//��������
	SetWindowLong(MyHwnd, GWL_STYLE, (l_Winstyle | WS_POPUP | WS_MAXIMIZE));

	//��������
	SetWindowPos(MyHwnd, HWND_TOP, 0, 0, screen_width, screen_length, 0);
}

void Player::GetFrameFromVideo(string FileName)
{
	//ͨ���ļ���������Ƶ������·�������·����
	VideoCapture vc;
	try {
		vc.open(FileName);
	}
	catch (Exception) {
		cout << "��Ƶ·����ʽ�������Ƶ������" << endl;
		return;
	}

	//������ҪԤ�����֡
	Mat frameRaw;

	//�����Ƶ��֡��
	//CAP_PROP_FRAME_COUNT��opencv�궨���ץȡ֡������
	FramesNum = vc.get(CAP_PROP_FRAME_COUNT);

	//��ȡ֡��
	FrameRate = vc.get(CAP_PROP_FPS);

	//�õ�����̨�������ʹ�ÿ���̨����
	//˵����ǰ�õĿ���̨���ĸ�
	//HANDLE temp_hd = MyHandle;



	//�������Ϊ���ɼ�,1��ʾ����ȣ�false��ʾ���ɼ�
	_CONSOLE_CURSOR_INFO cf = { 1,false };


	//ʹ��vector����������ÿһ֡
	//+3��Ϊ������
	vector<string> allframe(FramesNum + 3);

	//��¼��ʼʱ��
	double start = GetTickCount64();

	//������
	int framediff = 0, width = FrameWidth = 800, height = FrameHeight = 450, j, k;
	string output = "";
	string sign[2] = { " ","#" };
	//CAP_PROP_POS_AVI_RATIO����Ƶ���λ��,0~1��һ��ֵ
	//����дһ����Ϊ������ 
	//������forѭ�����ڶ�ȡ��Ƶÿһ֡������ŵ������
	for (int i = 0; i < FramesNum && vc.get(CAP_PROP_POS_AVI_RATIO) < (1 - 10E-6); i++) {
		Mat frameGray, frameOut;
		//�������Ϊ���ɼ�
		SetConsoleCursorInfo(MyHandle, &cf);

		//����Ҷ�ֵ���󣬺��������

		//�����һ֡�������δ��ù������ȡ��һ֡
		vc >> frameRaw;

		//����ǰRGB֡ת��Ϊ�Ҷ�ͼ��
		cvtColor(frameRaw, frameGray, 7);

		//��С�ߴ�
		resize(frameGray, frameOut, Size(FrameWidth, FrameHeight));


		//��ȡ������ַ���
		for (j = 0; j < FrameHeight; j++) {
			for (k = 0; k < FrameWidth; k++) {

				//��ֵ����ʾ���أ��Ҷȴ���127����ʾ
				output += sign[frameOut.at<bool>(j, k) / 127];
			}
			output += "\n";
		}
		allframe[i] = output;
		output = "";

		//��ʾ��ǰ�����ڼ���֡�ˣ���ȡʱ�ĵڼ�֡��
		//SetConsoleCursorPosition�����������frame������ʾ֡������λ��
		SetConsoleCursorPosition(MyHandle, { 0,0 });
		cout << "frame��" << i;

		//����fps(��ȡʱ��fps)
		if (GetTickCount64() - start >= 1000) {
			cout << "  fps��" << i - framediff;
			framediff = i + 1;
			start = GetTickCount64();
		}
	}
	Frames = allframe;
}

void Player::PlayVideo()
{
	//����
	system("cls");

	//���嵱ǰ֡��
	int framediff = 0, totalFrameNum = FramesNum, start = 0,startDisplay=0,
		span = round(1000/(FrameRate*speed))-2,delay=0;
	_CONSOLE_CURSOR_INFO cf = { 1,false };
	startDisplay = GetTickCount64();
	for (int i = 0; i < totalFrameNum; i++) {
		//ȷ��ÿһ֡����ʾ��궼���ɼ�
		
		SetConsoleCursorInfo(MyHandle, &cf);

		//�ѹ��λ�ö����ڣ�0,0��λ�ã�����ʵ������Ч��
		SetConsoleCursorPosition(MyHandle, { 0,0 });
		//�������
		
		cout << Frames[i] << endl;
		delay = (GetTickCount64() - startDisplay);
		//cout << delay;
		//֡���
		if(delay<span)
		Sleep(span-delay);
		//cout << delay  ;


		//չʾĿǰ��֡��������֡��
		if (GetTickCount64() - start >= 1000) {
			string temp = "frame��" + to_string(i) + "  fps��" + to_string(i - framediff)+" delay:"+to_string(delay);
			SetConsoleTitleA(temp.c_str());
			framediff = i + 1;
			start = GetTickCount64();


		}
		startDisplay = GetTickCount64();
	}
}

void Player::SetPixelSize()
{
	cout << "Please enter the size of the font:" << endl;
	int size;
	cin >> size;
	Myfontsize = size;
	WCHAR myFont[] = TEXT("Arial");
	_CONSOLE_FONT_INFOEX fontinfo = { sizeof(CONSOLE_FONT_INFOEX) ,1,{Myfontsize,Myfontsize},TMPF_FIXED_PITCH,400, *myFont };
	SetCurrentConsoleFontEx(MyHandle, false, &fontinfo);
}
