// Copyright Glory


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	//复制开启
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	
	/*
	 * 鼠标光标检测的几种结果
	 * A. LastActor == null && ThisActor==null
	 *		-不需要处理
	 * B. LastActor == null && ThisActor is valid
	 *		-ThisActor 设置高亮显示
	 * C. LastActor is valid && ThisActor is valid && ThisActor==LastActor
	 *		-光标指向同一个目标，不需要处理
	 * D. LastActor is valid && ThisActor is valid && ThisActor!=LastActor
	 *		-光标切换目标，LastActor取消高亮，ThisActor设置高亮
	 * E.LastActor is valid && ThisActor == null
	 *		-LastActor 取消高亮显示
	 */
	if (LastActor==nullptr)
	{
		if (ThisActor)
		{
			// Case B
			ThisActor->HighlightActor();
		}
		else
		{
			// CaseA
		}
	}
	else
	{
		if (ThisActor==nullptr)
		{
			// CaseE
			LastActor->UnHighlightActor();
		}
		else if (LastActor!=ThisActor)
		{
			// Case D
			LastActor->UnHighlightActor();
			ThisActor->HighlightActor();
		}
		else
		{
			// Case C
		}
	}
}
void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	check(AuraContext);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext,0);
	}
	
	
	bShowMouseCursor = true;
	DefaultMouseCursor=EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent> (InputComponent);
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f,Rotation.Yaw,0.0f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if (APawn* ControllerPawn =  GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}



