// Copyright Glory


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Aura/Public/AuraGameplayTags.h"
#include "Player/AuraPlayerController.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	APlayerController* PC = GetCurrentActorInfo()->PlayerController.Get();
	/*AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(PC);
	if (AuraPlayerController)
	{
		TargetActor = AuraPlayerController->GetLockActor();
		GEngine->AddOnScreenDebugMessage(1,5,FColor::Blue,TargetActor.GetName());
	}*/
	
}

void UAuraProjectileSpell::SpawnProjectile(AActor* AttackActor, const FGameplayTag& SocketTag)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(),SocketTag);
		FRotator Rotation = (AttackActor->GetActorLocation() - SocketLocation).Rotation();
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass,SpawnTransform, GetOwningActorFromActorInfo(),Cast<APawn>(GetOwningActorFromActorInfo()),ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		
		FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
		EffectContextHandle.SetAbility(this);
		EffectContextHandle.AddSourceObject(Projectile);
		TArray<TWeakObjectPtr<AActor>> Actors;
		Actors.Add(Projectile);
		EffectContextHandle.AddActors(Actors);
		FHitResult HitResult;
		HitResult.Location = AttackActor->GetActorLocation();
		
		EffectContextHandle.AddHitResult(HitResult);
		
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass,GetAbilityLevel(),EffectContextHandle);
		
		const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
		
		for (auto& Pair : DamageType)
		{
			const float ScaleDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaleDamage);
		}
		
		Projectile->DamageEffectSpecHandle = SpecHandle;
		Projectile->LuckActor = AttackActor;
		Projectile->bAbilityIsHoming = bIsHoming;
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}

/*void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(),FAuraGameplayTags::Get().Montage_Attack_Weapon);
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass,SpawnTransform, GetOwningActorFromActorInfo(),Cast<APawn>(GetOwningActorFromActorInfo()),ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		
		FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
		EffectContextHandle.SetAbility(this);
		EffectContextHandle.AddSourceObject(Projectile);
		TArray<TWeakObjectPtr<AActor>> Actors;
		Actors.Add(Projectile);
		EffectContextHandle.AddActors(Actors);
		FHitResult HitResult;
		HitResult.Location = ProjectileTargetLocation;
		
		EffectContextHandle.AddHitResult(HitResult);
		
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass,GetAbilityLevel(),EffectContextHandle);
		
		const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
		
		for (auto& Pair : DamageType)
		{
			const float ScaleDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaleDamage);
		}
		
		Projectile->DamageEffectSpecHandle = SpecHandle;
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}*/
