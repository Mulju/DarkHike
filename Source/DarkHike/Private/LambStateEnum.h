#pragma once

#include "CoreMinimal.h"

UENUM(DisplayName= "Lamb State")
enum State
{
    Grazing,
    Following,
    Moving,
    Waiting,
    Sacrificing
};
