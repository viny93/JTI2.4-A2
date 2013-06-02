#pragma once
//Author: Zack
class RenderObject
{
public:
	RenderObject(void);
	~RenderObject(void);
	virtual void Render();
	virtual void Update();
	virtual void processNormalKeys(unsigned char key, int x, int y);
	virtual void processSpecialKeys(int key, int xx, int yy);
	bool isAlive();
	void Kill();
private:
	bool alive;
};

