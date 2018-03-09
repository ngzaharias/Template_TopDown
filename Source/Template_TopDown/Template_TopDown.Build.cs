// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Template_TopDown : ModuleRules
{
	public Template_TopDown(ReadOnlyTargetRules Target)
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
