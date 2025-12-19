// Copyright Glory


#include "AbilitySystem/MMC/MMC_MaxHEalth.h"

#include "IMovieSceneModule.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHEalth::UMMC_MaxHEalth()
{
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;
	
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHEalth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//从源和目标中获取GameplayTag
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float Vigor = 0.0f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluateParameters, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.0f);
	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 Level = CombatInterface->GetPlayerLevel();
	
	return (Vigor+1.f)*5.f+10.f*Level+50.f;
}