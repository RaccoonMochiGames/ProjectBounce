// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProjectBounce_init() {}
	PROJECTBOUNCE_API UFunction* Z_Construct_UDelegateFunction_ProjectBounce_OnPickUp__DelegateSignature();
	PROJECTBOUNCE_API UFunction* Z_Construct_UDelegateFunction_ProjectBounce_OnUseItem__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_ProjectBounce;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_ProjectBounce()
	{
		if (!Z_Registration_Info_UPackage__Script_ProjectBounce.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_ProjectBounce_OnPickUp__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_ProjectBounce_OnUseItem__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/ProjectBounce",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x90216907,
				0x9857A23B,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_ProjectBounce.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_ProjectBounce.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_ProjectBounce(Z_Construct_UPackage__Script_ProjectBounce, TEXT("/Script/ProjectBounce"), Z_Registration_Info_UPackage__Script_ProjectBounce, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x90216907, 0x9857A23B));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
