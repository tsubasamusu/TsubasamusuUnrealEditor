using UnrealBuildTool;

public class TsubasamusuUnrealEditor : ModuleRules
{
    public TsubasamusuUnrealEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore"
            });

        PrivateDependencyModuleNames.AddRange(new string[]
            {
                "UnrealEd",
                "GraphEditor",
                "InternationalizationSettings"
            });
    }
}