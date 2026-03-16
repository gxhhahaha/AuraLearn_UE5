// Copyright Glory

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraProjectileSpell.generated.h"

class AAuraProjectile;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class AURA_API UAuraProjectileSpell : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	/*void SpawnProjectile(const FVector& ProjectileTargetLocation);*/
	void SpawnProjectile(AActor* AttackActor, const FGameplayTag& SocketTag);
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AAuraProjectile> ProjectileClass;
	
	//弹道是否会被阻挡
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool bIsHoming;
	
	UPROPERTY()
	TObjectPtr<AActor> TargetActor;
};
