using UnrealBuildTool;

public class NewActionsAddition : ModuleRules
{
    public NewActionsAddition(ReadOnlyTargetRules Target) : base (Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject","InputCore" });
    }
}