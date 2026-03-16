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
	
	/*
	 * Damage Types
	 */
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Fire"),FString("火焰伤害"));
	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Lightning"),FString("雷电伤害"));
	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Arcane"),FString("法术伤害"));
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Physical"),FString("物理伤害"));
	
	/*
	 * Resistance
	 */
	GameplayTags.Attribute_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Resistance.Fire"),FString("火焰抗性"));
	GameplayTags.Attribute_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Resistance.Lightning"),FString("雷电抗性"));
	GameplayTags.Attribute_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Resistance.Arcane"),FString("法术抗性"));
	GameplayTags.Attribute_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Resistance.Physical"),FString("物理伤抗性"));
	
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire,GameplayTags.Attribute_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning,GameplayTags.Attribute_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane,GameplayTags.Attribute_Resistance_Arcane);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical,GameplayTags.Attribute_Resistance_Physical);
	
	/*
	 * Effects
	 */
	GameplayTags.Effect_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effect.HitReact"),FString("受击反馈"));
	
	/*
	 * Abilities
	 */
	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack"),FString("Attack Ability Tag"));
	GameplayTags.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Summon"),FString("Summon Ability Tag"));
	
	/*
	 * Combat Socket
	 */
	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Weapon"),FString("Weapon"));
	GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.RightHand"),FString("RightHand"));
	GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.LeftHand"),FString("LeftHand"));
	GameplayTags.CombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Tail"),FString("Tail"));
	
	/*
	 * Montage Attack
	 */
	GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.1"),FString("Montage Tags"));
	GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.2"),FString("Montage Tags"));
	GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.3"),FString("Montage Tags"));
	GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.4"),FString("Montage Tags"));
}

