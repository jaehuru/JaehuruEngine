#pragma once

#include "Actor/AActor.h"


class AProjectTile : public AActor
{
public:
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;

private:
};

