#pragma once

#include "Component/Script/JScript.h"

class JCollider;

class JProjectTileScript : public JScript
{
public:
	JProjectTileScript();
	virtual ~JProjectTileScript();

	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;

	void OnCollisionEnter(JCollider* other) override;
	void OnCollisionStay(JCollider* other) override;
	void OnCollisionExit(JCollider* other) override;

private:

};
