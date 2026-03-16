// Copyright Glory


#include "Actor/AuraProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Aura/Aura.h"
#include "Components/AudioComponent.h"
#include "Net/UnrealNetwork.h"


AAuraProjectile::AAuraProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 500.0f;
	ProjectileMovement->MaxSpeed = 500.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
}


void AAuraProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bAbilityIsHoming)
	{
		OnHitLuckActor();
	}
}

void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopSound,GetRootComponent());
	
	if (bAbilityIsHoming)
	{
		Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ProjectileMovement->bIsHomingProjectile = true;
		ProjectileMovement->HomingTargetComponent = LuckActor->GetRootComponent();
	}
	else
	{
		Sphere->OnComponentBeginOverlap.AddDynamic(this,&AAuraProjectile::OnSphereOverlay);
	}
	
}


void AAuraProjectile::Destroyed()
{
	if (!bHit&&!HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(),FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactEffect,GetActorLocation());
		if (LoopingSoundComponent) LoopingSoundComponent->Stop();
		bHit=true;
	}
	Super::Destroyed();
}

void AAuraProjectile::OnSphereOverlay(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((DamageEffectSpecHandle.Data.IsValid()&& DamageEffectSpecHandle.Data.Get()->GetContext().GetEffectCauser() == OtherActor) || DamageEffectSpecHandle.Data == nullptr)
	{
		return;
	}
	
	/*判断是否为友军*/
	AActor* FirstActor = DamageEffectSpecHandle.Data->GetContext().GetEffectCauser();
	if (!UAuraAbilitySystemLibrary::IsNotFriend(FirstActor,OtherActor)) return;
	
	if (!bHit)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(),FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactEffect,GetActorLocation());
		if (LoopingSoundComponent) LoopingSoundComponent->Stop();
		bHit=true;
	}
	
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}
		Destroy();
	}
	else
	{

		bHit=true;
	}
}

void AAuraProjectile::OnHitLuckActor()
{
		float Distance = FVector::Distance(GetActorLocation(),LuckActor->GetActorLocation());
		if (Distance < 10)
		{
			if (!bHit)
			{
				UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(),FRotator::ZeroRotator);
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactEffect,GetActorLocation());
				if (LoopingSoundComponent) LoopingSoundComponent->Stop();
				bHit=true;
			}
			if (HasAuthority())
			{
				if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(LuckActor))
				{
					TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
				}
				Destroy();
			}
			else
			{

				bHit=true;
			}
		}
	
}


