// Copyright Glory

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "NiagaraSystem.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayAbility;
class UAbilitySystemComponent;;
class UAttributeSet;
class UGameplayEffect;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:

	AAuraCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return AttributeSet;	}
	
	/*start combat interface*/
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void Die() override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation()  override;
	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;
	virtual FTaggedMontage GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag) override;	
	virtual int32 GetMinionCount_Implementation() override;
	virtual void IncrementMinionCount_Implementation(int32 Amount) override;
	/*end combat interface*/
	
	UFUNCTION(NetMulticast, Reliable)
	virtual void MuticastHandleDeath();
	
	UPROPERTY(EditAnywhere,Category="Combat");
	TArray<FTaggedMontage> AttackMontage;
protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
	UPROPERTY(EditAnywhere,Category="Combat")
	FName WeaponTipSocketName;
	
	UPROPERTY(EditAnywhere,Category="Combat")
	FName RightHandTipSocketName;
	
	UPROPERTY(EditAnywhere,Category="Combat")
	FName LeftHandTipSocketName;
	
	UPROPERTY(EditAnywhere,Category="Combat")
	FName TailTipSocketName;
	
	bool bDead = false;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	virtual void InitAbilityActorInfo();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass, float Level) const;
	
	virtual void InitializeDefaultAttributes() const;
	
	virtual void AddCharacterAbilities();
	
	/*溶解特效*/
	void Dissolve();
	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolve(UMaterialInstanceDynamic* DynamicInstanceMaterial);
	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolve(UMaterialInstanceDynamic* DynamicInstanceMaterial);
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Combat")
	UNiagaraSystem* BloodEffect;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Combat")
	USoundBase* DeathSound;
	
	/*仆从计数*/
	int32 MinionCount = 0;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes", meta=(AllowPrivateAccess=true))
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimMontage> HitReactMontage;
};
