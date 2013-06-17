#pragma once
#include "RenderObject.h"
class UnderwaterFilter :
	public RenderObject
{
public:
	UnderwaterFilter(void);
	~UnderwaterFilter(void);
	
	void Render();
	void Update();

private:
	float ratio;
};

