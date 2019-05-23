#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;
//ʹ��opencv�������ռ�
using namespace cv;
class Player {
public:
	Player();
	void SetPlayerConfig(string cmd);
	void SetStdWindow(HANDLE hd, HWND hwnd);
	void SetWindowConfig();
	void GetFrameFromVideo(string FileName);
	void PlayVideo();

	//���������С���û�������
	void SetPixelSize();

	//���������С
	void SetPixelSize(int size);

	//������ݵ��ı�
	void Output_to_file();

	//���ı��л�ȡ����
	void Gain_date_from_file();

	//�õ���ǰ�����С
	int Get_Myfontsize();

	//�û��趨ģʽ
	void Set();

private:
	vector<string> Frames;
	int FramesNum;
	int FrameWidth;
	int FrameHeight;
	double speed;
	double FrameRate;
	HWND MyHwnd;
	HANDLE MyHandle;
	//�����С
	int Myfontsize;

};

#endif 