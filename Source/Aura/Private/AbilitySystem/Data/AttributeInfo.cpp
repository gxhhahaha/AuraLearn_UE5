// Copyright Glory


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& tag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo& info : AttributeInformation)
	{
		if (info.AttributeTag.MatchesTagExact(tag))
		{
			return info;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("找不到 [%s] 的信息"), *tag.ToString());
	}
	return FAuraAttributeInfo();
}
