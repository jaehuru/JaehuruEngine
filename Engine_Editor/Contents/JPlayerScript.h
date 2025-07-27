#pragma once

#include "Component/Script/JScript.h"

class AProjectTile;

class JPlayerScript : public JScript
{
public:
	JPlayerScript();
	~JPlayerScript();

	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;

private:
	AProjectTile* mProjTile;
};

