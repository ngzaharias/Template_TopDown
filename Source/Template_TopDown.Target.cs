// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Template_TopDownTarget : TargetRules
{
	public Template_TopDownTarget(TargetInfo Target)
	{
		Type = TargetType.Game;
	}

	//
	// TargetRules interface.
	//

	public override void SetupBinaries
		(
			TargetInfo Target,
			ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
			ref List<string> OutExtraModuleNames
		)
	{
		OutExtraModuleNames.Add("Template_TopDown");
	}
}
