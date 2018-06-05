#include "stdafx.h"
#include "OpenGL.h"

COpenGL::COpenGL()
	:hDC(NULL)
	,hRC(NULL)
{
}


COpenGL::~COpenGL()
{
	wglMakeCurrent(hDC, NULL);
	wglDeleteContext(hRC);
}


bool COpenGL::SetupPixelFormat(HDC hdc)
{
	hDC = hdc;

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),    // pfd�ṹ�Ĵ�С
		1,                                // �汾��
		PFD_DRAW_TO_WINDOW |              // ֧���ڴ����л�ͼ
		PFD_SUPPORT_OPENGL |              // ֧��OpenGL
		PFD_DOUBLEBUFFER,                 // ˫����ģʽ
		PFD_TYPE_RGBA,                    // RGBA ��ɫģʽ
		24,                               // 24 λ��ɫ���
		0, 0, 0, 0, 0, 0,                 // ������ɫλ
		0,                                // û�з�͸���Ȼ���
		0,                                // ������λλ
		0,                                // ���ۼӻ���
		0, 0, 0, 0,                       // �����ۼ�λ
		32,                               // 32 λ��Ȼ���   
		0,                                // ��ģ�建��
		0,                                // �޸�������
		PFD_MAIN_PLANE,                   // ����
		0,                                // ����
		0, 0, 0                           // ���Բ�,�ɼ��Ժ������ģ
	};

	int nPixelFormat;    // ���ص��ʽ
	if (!(nPixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{
		MessageBox(NULL, L"can not find proper mode", L"Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	SetPixelFormat(hDC, nPixelFormat, &pfd);
	hRC = wglCreateContext(hDC);    //����GDI��ͼ��ʹ�õ�HDC������Ӧ��HGLRC
	wglMakeCurrent(hDC, hRC);        //ʹOpenGL��ͼ��ʹ�õ�HGLRCΪ��ǰ��ͼ����

	return TRUE;
}

void COpenGL::SetupRC(void)
{
	M3DVector3f vPoints[3] = { { 0.0f, -0.4f, 0.0f },
	{ 10.0f, -0.4f, 0.0f },
	{ 5.0f, -0.4f, -5.0f } };
	
	
			  
	glClearColor(fLowLight[0], fLowLight[1], fLowLight[2], fLowLight[3]);  // ��ɫ����


	glStencilOp(GL_INCR, GL_INCR, GL_INCR);
	glClearStencil(0);
	glStencilFunc(GL_EQUAL, 0x0, 0x01);


	glCullFace(GL_BACK);              //���ö���α����ϵĹ��ա���Ӱ����ɫ���㼰����
	glFrontFace(GL_CCW);			  //��ʱ��Ϊ����
	glEnable(GL_CULL_FACE);			  //�����޳�
	glEnable(GL_DEPTH_TEST);          //��Ȳ���
	glEnable(GL_MULTISAMPLE_ARB);


	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, fLowLight);	//����ȫ�ֻ�����Ϊ��ɫ
	glLightfv(GL_LIGHT0, GL_AMBIENT, fLowLight);		//������
	glLightfv(GL_LIGHT0, GL_DIFFUSE, fLowLight);		//ɢ���
	glLightfv(GL_LIGHT0, GL_SPECULAR, fBrightLight);	//�����
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

	// ���ݵ�������������ƽ�淽��
	M3DVector4f pPlane;
	m3dGetPlaneEquation(pPlane, vPoints[0], vPoints[1], vPoints[2]);

	//����ͶӰ�����ڵ����ϻ�����Ӱ
	m3dMakePlanarShadowMatrix(mShadowMatrix, pPlane, fLightPos);


	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


	
	Tree::img = tree.loadPNGTexture("leaf.png");
	glEnable(GL_MULTISAMPLE);  //�򿪶��ز���
}

void COpenGL::ShutDownRC(void)
{
	glDeleteTextures(3, tex.textureObjects);
	
}

void COpenGL::RenderSence(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glPushMatrix();
	tree.setData();//��������

	glTranslatef(0.0f, 0.0f, -5.0f);  //��ͼ�任
	frameCamera.ApplyCameraTransform();
	glRotatef(xRot, 0.0f, 1.0f, 0.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, fLightPos);

	
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
		SG.DrawSky();
	glPopMatrix();

	SG.DrawGround();

	glDisable(GL_FOG);


	glColor3f(1.0f, 1.0f, 1.0f);
	// ����Ӱ
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_STENCIL_TEST);
	glPushMatrix();
		glMultMatrixf(mShadowMatrix);
		DrawInhabitants(1);
	glPopMatrix();
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

		DrawInhabitants(0);

	glPopMatrix();

	//glFlush();
	SwapBuffers(wglGetCurrentDC());
	//glutSwapBuffers();
}

void COpenGL::ChangeSize(int w, int h)
{
	GLfloat fAspect;

	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	fAspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(35.0f, fAspect, 1.0f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void COpenGL::DrawInhabitants(int nShadow)
{
	if (nShadow == 0)
	{
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
		glColor4f(0.0f, 0.0f, 0.0f, 0.6f);  // ��Ӱ����ɫ

	glPushMatrix();
	glTranslatef(0.0f, -0.4f, 0.0f);
	glRotatef(-90, 1.0, 0, 0);

	if (nShadow == 0)		//����ǻ����Ļ�
	{
		glMaterialfv(GL_FRONT, GL_DIFFUSE, fBrightLight);
	}
	
	
	tree.DrawTreeInit();  //����ǰ��׼������
	int n = tree.getN();
	tree.DrawTree(n);

	glMaterialfv(GL_FRONT, GL_SPECULAR, fNoLight);
	glPopMatrix();
}

void COpenGL::SpecialKeys(int key, int x, int y)
{
	float fa = frameCamera.GetOriginZ();

	if (key == VK_UP && fa > -3.0)
		frameCamera.MoveForward(0.1f);

	if (key == VK_DOWN && fa < 15.0)
		frameCamera.MoveForward(-0.1f);

	if (key == VK_LEFT)
		xRot -= 5.0f;
	if (key == VK_RIGHT)
		xRot += 5.0f;
	if (xRot > 356.0f)
		xRot = 0.0f;
	if (xRot < -1.0f)
		xRot = 355.0f;

	// �ػ�����
	//glutPostRedisplay();
	
}
