// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestNetworking : ModuleRules
{
	public TestNetworking(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] 
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay",
		});

		//PublicIncludePaths.AddRange(new string[] 
		//{
		//});
	}
}
