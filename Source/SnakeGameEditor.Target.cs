// Snake Game, Copyright Adam Mambetov. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SnakeGameEditorTarget : TargetRules
{
    public SnakeGameEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_2;

        ExtraModuleNames.AddRange(new string[] { "SnakeGame" });
    }
}
