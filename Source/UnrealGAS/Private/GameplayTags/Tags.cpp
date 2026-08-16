#include "GameplayTags/Tags.h"

namespace Tags
{
	namespace AbilityTags
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "Tags.AbilityTags.Primary", "Tag for primary ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "Tags.AbilityTags.Secondary", "Tag for secondary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, "Tags.AbilityTags.Tertiary", "Tag for Tertiary Ability");

		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "Tags.Abilities.ActivateOnGiven", "Tag for on activating on giv en abilities");
	}

	namespace Events
	{
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "Tags.Events.Enemy.HitReact", "Tag for enemy hit react event");
		}
	}
}