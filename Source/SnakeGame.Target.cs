// Snake Game, Copyright Adam Mambetov. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SnakeGameTarget : TargetRules
{
    public SnakeGameTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_2;

        ExtraModuleNames.AddRange(new string[] { "SnakeGame" });
    }
}
