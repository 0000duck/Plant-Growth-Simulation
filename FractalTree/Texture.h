
#define GROUND_TEXTURE  0	//�������
#define WOOD_TEXTURE    1	//��������
#define SKY_TEXTURE		2	//�������
#define NUM_TEXTURES    3	//������Ŀ

#pragma once
class Texture
{
public:
	GLuint  textureObjects[NUM_TEXTURES];
	const char *szTextureFiles[NUM_TEXTURES] = { "grass.tga", "wood.tga","sky.tga" };
	Texture();
	~Texture();
	void Init();
};

