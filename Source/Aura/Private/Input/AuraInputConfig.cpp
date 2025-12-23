// Copyright Glory


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{
	for (const auto& InputAction : AbilityInputActions)
	{
		if (InputAction.InputAction&&InputAction.InputTag == InputTag)
		{
			return InputAction.InputAction;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("在[%s]中找不到[%s]对应的InputAction"),*GetNameSafe(this),*InputTag.ToString());
	}
	return nullptr;
}
