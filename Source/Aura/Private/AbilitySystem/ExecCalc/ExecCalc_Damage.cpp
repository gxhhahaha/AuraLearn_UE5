// Copyright Glory


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Fire);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Lightning);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Arcane);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Physical);
	
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target , false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration,Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitChance,Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitDamage,Source, false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Fire,Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Lightning,Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Arcane,Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Physical,Target, false);
		
		const FAuraGameplayTags& Tags = FAuraGameplayTags::Get();
		
		TagsToCaptureDefs.Add(Tags.Attribute_Secondary_Armor, ArmorDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Secondary_BlockChance, BlockChanceDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Secondary_ArmorPenetration, ArmorPenetrationDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Secondary_CriticalHitChance, CriticalHitChanceDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Secondary_CriticalHitDamage, CriticalHitDamageDef);
		
		TagsToCaptureDefs.Add(Tags.Attribute_Resistance_Fire, Resistance_FireDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Resistance_Lightning, Resistance_LightningDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Resistance_Arcane, Resistance_ArcaneDef);
		TagsToCaptureDefs.Add(Tags.Attribute_Resistance_Physical, Resistance_PhysicalDef);
		
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_FireDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_LightningDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_ArcaneDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_PhysicalDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	
	AActor* SourceAvatarActor = SourceASC? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatarActor = TargetASC? TargetASC->GetAvatarActor() : nullptr;
	
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatarActor);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatarActor);
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float Damage = 0.0f;
	for ( auto& Pair : FAuraGameplayTags::Get().DamageTypesToResistances)
	{
		const FGameplayTag DamageTypeTag = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;
		
		checkf(AuraDamageStatics().TagsToCaptureDefs.Contains(ResistanceTag), TEXT("TagsToCaptureDefs 不包含标签 [%s]"), *ResistanceTag.ToString());
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = AuraDamageStatics().TagsToCaptureDefs[ResistanceTag];
		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key, false);
		float ResistanceValue = 0.0f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluateParameters, ResistanceValue);
		DamageTypeValue *= (1-(ResistanceValue/(ResistanceValue+20)));
		
		Damage+=DamageTypeValue;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
	}
	
	//敌人miss几率
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluateParameters, TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.0f);
	
	const bool bBlock = FMath::RandRange(1,100)<=TargetBlockChance;
	Damage = bBlock ? 0: Damage;
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	if (!bBlock)
	{
		//护甲穿透
		float SourceArmorPenetration = 0.0f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluateParameters,SourceArmorPenetration);
		//敌人护甲
		float TargetArmor = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluateParameters, TargetArmor);
		TargetArmor = TargetArmor*(1-(SourceArmorPenetration/(SourceArmorPenetration+10)));
		TargetArmor = FMath::Max<float>(TargetArmor, 0.0f);
		//暴击率
		float SourceCriticalHitChance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvaluateParameters, SourceCriticalHitChance);
		//暴击伤害
		float SourceCriticalHitDamage = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, EvaluateParameters, SourceCriticalHitDamage);
		bool bCritHit = FMath::RandRange(1,100)<=SourceCriticalHitChance*2;
		Damage = bCritHit? Damage*SourceCriticalHitDamage : Damage;
	
		Damage *= (1.f - (TargetArmor/(TargetArmor+50)));
		UAuraAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCritHit);
	}
	UAuraAbilitySystemLibrary::SetIsBlockHit(EffectContextHandle, bBlock);
	
	
	//读取GameMode中的CharacterClassInfo
	/*UCharacterClassInfo* ClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatarActor);	
	FRealCurve* ArmorPenetrationCurve = ClassInfo->DamageCalculationCoefficient->FindCurve(FName("ArmorPenetration"), FString(""));
	float SArmP = ArmorPenetrationCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	float TArmP = ArmorPenetrationCurve->Eval(TargetCombatInterface->GetPlayerLevel());*/
	
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
