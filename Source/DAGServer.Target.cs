using UnrealBuildTool;
using System.Collections.Generic;

public class DAGServerTarget : TargetRules
{
    public DAGServerTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Server;
        DefaultBuildSettings = BuildSettingsVersion.V2;

        ExtraModuleNames.Add("DAG");
    }
}
