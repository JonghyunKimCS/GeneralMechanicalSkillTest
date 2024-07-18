<<<<<<< HEAD
// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;

public class project1 : ModuleRules
{
	public project1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Cpp17;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "SlateCore", "Slate", "Http", "Json", "JsonUtilities" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		//PublicIncludePaths.Add(@"C:\\Unreal Projects\\cppOpt-master\\inc");
		//PublicAdditionalLibraries.Add(@"C:\\Unreal Projects\\project1\\cppOpt-master\\inc");
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

		string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/pointing/Debug"));
		string LibraryName = "pointing.lib";
		string IncludePath = ThirdPartyPath;

		string LibraryPath = ThirdPartyPath;
		PublicIncludePaths.Add(IncludePath);
		PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, LibraryName));
	}
}
=======
// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;

public class project1 : ModuleRules
{
	public project1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Cpp17;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "SlateCore", "Slate", "Http", "Json", "JsonUtilities" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		//PublicIncludePaths.Add(@"C:\\Unreal Projects\\cppOpt-master\\inc");
		//PublicAdditionalLibraries.Add(@"C:\\Unreal Projects\\project1\\cppOpt-master\\inc");
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

		string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/pointing/Debug"));
		string LibraryName = "pointing.lib";
		string IncludePath = ThirdPartyPath;

		string LibraryPath = ThirdPartyPath;
		PublicIncludePaths.Add(IncludePath);
		PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, LibraryName));
	}
}
>>>>>>> 286a07f11cee1864cde8ba04f7ca282468cb8acb
