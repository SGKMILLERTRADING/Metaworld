using UnrealBuildTool;
using System.Collections.Generic;

public class MetaworldEditorTarget : TargetRules
{
    public MetaworldEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
        ExtraModuleNames.Add("Metaworld");
    }
}
