// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProjectBounce/ProjectBounceGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProjectBounceGameMode() {}
// Cross Module References
	PROJECTBOUNCE_API UClass* Z_Construct_UClass_AProjectBounceGameMode_NoRegister();
	PROJECTBOUNCE_API UClass* Z_Construct_UClass_AProjectBounceGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_ProjectBounce();
// End Cross Module References
	void AProjectBounceGameMode::StaticRegisterNativesAProjectBounceGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AProjectBounceGameMode);
	UClass* Z_Construct_UClass_AProjectBounceGameMode_NoRegister()
	{
		return AProjectBounceGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AProjectBounceGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AProjectBounceGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_ProjectBounce,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AProjectBounceGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "ProjectBounceGameMode.h" },
		{ "ModuleRelativePath", "ProjectBounceGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AProjectBounceGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProjectBounceGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AProjectBounceGameMode_Statics::ClassParams = {
		&AProjectBounceGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AProjectBounceGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AProjectBounceGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AProjectBounceGameMode()
	{
		if (!Z_Registration_Info_UClass_AProjectBounceGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AProjectBounceGameMode.OuterSingleton, Z_Construct_UClass_AProjectBounceGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AProjectBounceGameMode.OuterSingleton;
	}
	template<> PROJECTBOUNCE_API UClass* StaticClass<AProjectBounceGameMode>()
	{
		return AProjectBounceGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AProjectBounceGameMode);
	struct Z_CompiledInDeferFile_FID_ProjectBounce_Source_ProjectBounce_ProjectBounceGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ProjectBounce_Source_ProjectBounce_ProjectBounceGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AProjectBounceGameMode, AProjectBounceGameMode::StaticClass, TEXT("AProjectBounceGameMode"), &Z_Registration_Info_UClass_AProjectBounceGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AProjectBounceGameMode), 3988178674U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ProjectBounce_Source_ProjectBounce_ProjectBounceGameMode_h_2429984705(TEXT("/Script/ProjectBounce"),
		Z_CompiledInDeferFile_FID_ProjectBounce_Source_ProjectBounce_ProjectBounceGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ProjectBounce_Source_ProjectBounce_ProjectBounceGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
