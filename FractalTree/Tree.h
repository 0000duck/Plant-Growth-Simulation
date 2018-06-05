
#include "Texture.h"
#include "gl_texture_t.h"

#pragma once
class Tree
{
private:
	int N = 5;
	float baseTall = 8;		//��ʼ�߶�
	float baseR = 6;		//��ʼ����뾶
	float R[7];			//����뾶����
	float H[7];			//��������
	float K = 0.5;			//����뾶����ڵ���뾶���ű���
	float Q = 0.5;			//����뾶���ű���
	float M = 0.65;			//�߶����ű���
	float angle = 55;		//��֦��֦�ĽǶ�
	int leaf = 9;
	GLUquadric *qObj;
	
	

public:
	Texture texture;
	Tree();
	~Tree();

	 static int img;
	 static int shape; //��������̬������ΪĬ�ϣ�ֵΪ0������ֵΪ1��

	int getN();

	float getbaseTall();

	float getk();

	float getq();

	float getm();

	void setN(int n);

	void setbaseTall(float tall);

	void setk(float k);

	void setQ(float q);

	void setM(float m);

	void setAngle(float a);

	float getAngle();

	int getleaf();

	void setleaf(int lea);

	int getbaseR();

	void setbaseR(float r);

	void setData();		//���ð뾶����͸߶�����

	void DrawTree(int n);		//���Ƹ��ݵ�������n������

	float Gauss(float min, float max);

	gl_texture_t *ReadPNGFromFile(const char *filename);

	GLuint loadPNGTexture(const char *filename);

	void GetPNGtextureInfo(int color_type, gl_texture_t *texinfo);

	void DrawTreeInit();   //��������Ȳ���
};

