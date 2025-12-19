// Copyright Glory

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHEalth.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMMC_MaxHEalth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:
	UMMC_MaxHEalth();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const  override;
	
private:
	FGameplayEffectAttributeCaptureDefinition VigorDef;
};
