#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

class FTsubasamusuUnrealEditor : public IModuleInterface
{
public:
	virtual void StartupModule() override;

public:
	virtual void ShutdownModule() override;
};