#include "pch.h"
#include "Player.h"
using namespace std;
using namespace cv;

//���캯������ʼ����ֵ
Player::Player()
{
	FramesNum = 0;
	FrameWidth = 800;
	FrameHeight = 450;
	speed = 1.0;
	FrameRate = 30.0;
}


//�õ����
void Player::SetStdWindow(HANDLE hd, HWND hwnd)
{
	MyHandle = hd;
	MyHwnd = hwnd;
}


//������������ļ������û�У��ʹ���һ��
void Player::Output_to_file()
{
	ofstream file_txt;
	file_txt.open("set.txt", std::ios::out);
	file_txt << Myfontsize << endl;
	file_txt << speed << endl;
	file_txt << FrameHeight << endl;
	file_txt << FrameWidth << endl;
	file_txt << file << endl;
	file_txt.close();
}

//���ļ��л�ȡ���������
void Player::Gain_date_from_file()
{
	const int Number_of_int_data = 4;
	//��������洢����
	int data[Number_of_int_data];
	ifstream file_txt;
	try {
		file_txt.open("set.txt");
	}
	catch (Exception) {
		cout << "�Ҳ���set.txt�ļ������������б����򲢽��г�ʼ��" << endl;
		return;
	}
	//��ȡ��������
	for (int i = 0; i<Number_of_int_data; i++) {
		file_txt >> data[i];
	}
	string file_info;
	file_txt>>file_info;

	//��ֵ����player����
	Myfontsize = data[0];
	speed = data[1];
	FrameHeight = data[2];
	FrameWidth = data[3];

	file = file_info;
	//���ﲻ�����������ڶ�ȡÿһ֡��ʱ���и���Ϣ��ʾ
	cout << endl;
	cout << "�ļ���Ϣ��" << file << endl;
	cout << "�����С:" << Myfontsize << endl;
	cout << "�����ٶ�:" << speed << endl;
	cout << "��Ƶ�߶ȣ�" << FrameHeight << endl;
	cout << "��Ƶ��ȣ�" << FrameWidth << endl;
	
	file_txt.close();

}

//�õ������С
int Player::Get_Myfontsize()
{
	return Myfontsize;
}

//���������
void Player::Set()
{
	double key = 1;
	cout << "�Ƿ���Ҫ���г�ʼ��������1���г�ʼ�����������ã�����ʹ����һ�ε�����" << endl;
	cout << "ע�⣬����ǵ�һ��ʹ�øó��򣬱����ʼ����" << endl;
	cin >> key;
	system("cls");
	if (key == 1) {
		Input_file();
		Set_speed();
		SetPixelSize();
		Set_frame_width();
		Set_frame_height();
		Output_to_file();
	}
	else {
		Gain_date_from_file();
	}

}

//�����ļ���Ϣ
void Player::Input_file()
{
	cout << "��һ�����������ļ�·�����ļ�����" << endl;
	cout << "��ʾ����򵥵ķ�ʽ�ǽ���Ƶ����ͬһ·����Ȼ��ֱ�������ļ�����ʹ�����·����" << endl;
	cout << "������Ҫ������������·��������·����" << endl;
	cout << "�����������ļ�·�����ļ�����";
	cin >> file;
	system("cls");

}

//�õ��ļ���Ϣ
string Player::Get_file_info()
{
	return file;
}

//���ò����ٶ�
void Player::Set_speed()
{
	double sp;
	cout << "��������Ƶ�Ĳ����ٶȣ���������0.5-2.0��һ�����֣�" << endl;
	cin >> sp;
	while (sp > 2 || sp < 0.5) {
		cout << "����������������룺";
		cin >> sp;
	}
	speed = sp;
}

//���ò����ٶȣ���������
void Player::Set_speed(double sp)
{
	speed = sp;
}

//���ز����ٶ�
double Player::Get_speed()
{
	return speed;
}

//����ÿһ֡�Ŀ��
void Player::Set_frame_width()
{
	int w;
	cout << "����������Ҫ����Ƶ��ȣ�";
	cin >> w;
	cout << endl;
	FrameWidth = w;
}

//����ÿһ֡�ĸ߶�
void Player::Set_frame_height()
{
	int h;
	cout << "����������Ҫ����Ƶ�߶ȣ�";
	cin >> h;
	cout << endl;
	FrameHeight = h;
	system("cls");
}

//����ÿһ֡�Ŀ�ȣ���������
void Player::Set_frame_width(int w)
{
	FrameWidth = w;
}

//����ÿһ֡�ĸ߶ȣ���������
void Player::Set_frame_height(int h)
{
	FrameHeight = h;
}

//����֡�Ŀ��
int Player::Get_frame_width()
{
	return FrameWidth;
}

//����֡�ĸ߶�
int Player::Get_frame_height()
{
	return FrameHeight;
}

//���ÿ���̨��Ϣ��ȫ����
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

//����Ƶ�л�ȡÿһ֡�����Ҵ������洢���ַ���������
void Player::GetFrameFromVideo()
{
	//ͨ���ļ���������Ƶ������·�������·����
	VideoCapture vc;
	try {
		vc.open(file);
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


	//�������Ϊ���ɼ�,1��ʾ����ȣ�false��ʾ���ɼ�
	_CONSOLE_CURSOR_INFO cf = { 1,false };


	//ʹ��vector����������ÿһ֡
	//+3��Ϊ������
	vector<string> allframe(FramesNum + 3);

	//��¼��ʼʱ��
	double start = GetTickCount64();

	//������
	int framediff = 0, j, k;

	//����洢һ֡���ַ���
	string output = "";

	//����һ����ֵ���ַ���
	string sign[2] = { " ","#" };

	//CAP_PROP_POS_AVI_RATIO����Ƶ���λ��,0~1��һ��ֵ
	//����дһ����Ϊ������ 
	//������forѭ�����ڶ�ȡ��Ƶÿһ֡������ŵ������
	for (int i = 0; i < FramesNum && vc.get(CAP_PROP_POS_AVI_RATIO) < (1 - 10E-6); i++) {
		Mat frameGray, frameOut;
		//�������Ϊ���ɼ�
		SetConsoleCursorInfo(MyHandle, &cf);

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
		cout << "��ǰ��ȡ֡����" << i;

		//����fps(��ȡʱ��fps)
		if (GetTickCount64() - start >= 1000) {
			cout << "  fps��" << i - framediff;
			framediff = i + 1;
			start = GetTickCount64();
		}
	}
	Frames = allframe;
}

//ʹ����֡�㷨���з�ӳ��ԭ��ÿ�뻮��Ϊ��ʮ��Σ����������һ֡����ʱ�䣬����ͣ����ֱ����һ��
void Player::PlayVideo()
{
	//����
	system("cls");

	//Ӧ����������
	SetPixelSize(Get_Myfontsize());

	//ȫ��
	SetWindowConfig();

	//���嵱ǰ֡��
	int framediff = 0, totalFrameNum = FramesNum, start = 0,startDisplay=0,
		span = round(1000/(FrameRate*speed))-2,delay=0;

	//�����ƣ��趨����СΪ1�����ɼ�
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
		//֡���
		if(delay<span)
		Sleep(span-delay);


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

//���������С�������ص㣩
void Player::SetPixelSize()
{
	cout << "���������������С��" << endl;
	int size;
	cin >> size;
	Myfontsize = size;
	system("cls");
}

//�������壨���ص㣩��С����������
void Player::SetPixelSize(int size)
{
	Myfontsize = size;
	WCHAR myFont[] = TEXT("Arial");
	_CONSOLE_FONT_INFOEX fontinfo = { sizeof(CONSOLE_FONT_INFOEX) ,
	1,
	{Myfontsize,Myfontsize},
	TMPF_FIXED_PITCH,
	400,
	*myFont };
	SetCurrentConsoleFontEx(MyHandle, false, &fontinfo);
}
