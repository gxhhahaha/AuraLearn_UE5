// Copyright Glory


#include "AbilitySystem/Abilities/AuraSumanAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAuraSumanAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread/MunMinions;

	TArray<FVector> SpawnLocations;
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread/2,FVector::UpVector);
	for (int i = 0; i < MunMinions; ++i)
	{
		const FVector Direction  = LeftOfSpread.RotateAngleAxis(DeltaSpread*i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction*FMath::RandRange(MinSpawnDistance,MaxSpawnDistance);
		//DrawDebugSphere(GetWorld(),ChosenSpawnLocation,15.f,12,FColor::Red,false,3.f);
		
		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit,ChosenSpawnLocation+FVector(0,0,200),ChosenSpawnLocation+FVector(0,0,-200),ECC_Visibility);
		if (Hit.bBlockingHit)
		{
			ChosenSpawnLocation = Hit.ImpactPoint;
		}
		
		SpawnLocations.Add(ChosenSpawnLocation);
	}
	
	return SpawnLocations;
}

TSubclassOf<APawn> UAuraSumanAbility::GetRandomMinionClass()
{
	const int32 Selection = FMath::RandRange(0, MinionClasses.Num()-1);
	return MinionClasses[Selection];
}
