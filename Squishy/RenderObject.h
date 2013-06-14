#pragma once
//Author: Zack
class RenderObject
{
public:
	enum ObjectType
		{
			WORLD,
			PLAYER,
			ENEMY
		};

	//	cv::Point RenderCoordinates;

	ObjectType type;
	float RenderPositionX;
	float RenderPositionY;
	float RenderWidth;
	float RenderDepth;
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

