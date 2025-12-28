// Copyright Glory

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"



class UWidgetComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	/* EnemyInterface begin*/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/* end EnemyInterface*/ 
	
	/* Begin Combat Interface */
	virtual int32 GetPlayerLevel() override;
	virtual void Die() override;
	/*End Combat Interface*/

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnMaxHealthChanged;
	
	UPROPERTY(BlueprintReadOnly,Category="Combat")
	bool bHitReacting = false;
	
	UPROPERTY(BlueprintReadOnly,Category="Combat")
	float BaseWalkSpeed = 250.f;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Combat")
	float LifeSpan = 5.0f;
	
	void HitReactTagChange(const FGameplayTag CallbackTag, int32 NewCount);
protected:
	virtual void BeginPlay() override;
	
	virtual void InitAbilityActorInfo() override;
	
	virtual void InitializeDefaultAttributes() const override;
	
private:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults",meta = (AllowPrivateAccess = "true"))
	int32 Level =1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults",meta = (AllowPrivateAccess = "true"))
	ECharacterClass CharacterClass = ECharacterClass::Warrior;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> HealthBar;
	

};
