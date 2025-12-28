// Copyright Glory


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializedNativeGameplayTags()
{
	/*
	 * Primary Attribute Tags
	 */
	GameplayTags.Attribute_Primary_Strength =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Strength"),FString(""));
	GameplayTags.Attribute_Primary_Intelligence =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Intelligence"),FString(""));
	GameplayTags.Attribute_Primary_Resilience =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Resilience"),FString(""));
	GameplayTags.Attribute_Primary_Vigor =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Vigor"),FString(""));
	
	/*
	 * Secondary Attribute Tags
	 */
	GameplayTags.Attribute_Secondary_Armor =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.Armor"),FString("护甲"));
	GameplayTags.Attribute_Secondary_ArmorPenetration =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.ArmorPenetration"),FString(""));
	GameplayTags.Attribute_Secondary_BlockChance=  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.BlockChance"),FString(""));
	GameplayTags.Attribute_Secondary_CriticalHitChance =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.CriticalHitChance"),FString(""));
	GameplayTags.Attribute_Secondary_CriticalHitDamage =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.CriticalHitDamage"),FString(""));
	GameplayTags.Attribute_Secondary_CriticalHitResistance =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.CriticalHitResistance"),FString(""));
	GameplayTags.Attribute_Secondary_HealthRegeneration =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.HealthRegeneration"),FString(""));
	GameplayTags.Attribute_Secondary_ManaRegeneration =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.ManaRegeneration"),FString(""));
	GameplayTags.Attribute_Secondary_MaxHealth =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MaxHealth"),FString(""));
	GameplayTags.Attribute_Secondary_MaxMana =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MaxMana"),FString(""));
	
	/*
	 * Input Tags
	 */
	GameplayTags.InputTag_LMB =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"),FString("鼠标左键"));
	GameplayTags.InputTag_RMB =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"),FString("鼠标右键"));
	GameplayTags.InputTag_1 =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"),FString("键盘1"));
	GameplayTags.InputTag_2=  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"),FString("键盘2"));
	GameplayTags.InputTag_3 =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"),FString("键盘3"));
	GameplayTags.InputTag_4 =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"),FString("键盘4"));
	GameplayTags.InputTag_5 =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.5"),FString("键盘5"));
	
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"),FString("Damage"));
	GameplayTags.Effect_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effect.HitReact"),FString("受击反馈"));
}

