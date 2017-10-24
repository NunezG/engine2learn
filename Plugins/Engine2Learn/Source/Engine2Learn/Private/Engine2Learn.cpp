// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Engine2Learn.h"

#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#include "PropertyEditorModule.h"

#include "DucanduSettings.h"
#include "E2LObserver.h"

#define LOCTEXT_NAMESPACE "FEngine2LearnModule"

void FEngine2LearnModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		// Create the new category
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

		SettingsContainer->DescribeCategory("Ducandu",
			LOCTEXT("RuntimeWDCategoryName", "Ducandu"),
			LOCTEXT("RuntimeWDCategoryDescription", "Ducandu Project"));

		// Register the settings
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Ducandu", "General",
			LOCTEXT("RuntimeGeneralSettingsName", "General"),
			LOCTEXT("RuntimeGeneralSettingsDescription", "General Options"),
			GetMutableDefault<UDucanduSettings>()
		);
	}

	if (FPropertyEditorModule *PropertyModule = FModuleManager::GetModulePtr<FPropertyEditorModule>("PropertyEditor"))
	{

		//Custom detail views
		PropertyModule->RegisterCustomPropertyTypeLayout("E2LObservedProperty", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FE2LObservedPropertyDetails::MakeInstance));
	}
}

void FEngine2LearnModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Ducandu", "General");
	}

	if (FPropertyEditorModule *PropertyModule = FModuleManager::GetModulePtr<FPropertyEditorModule>("PropertyEditor"))
	{
		PropertyModule->UnregisterCustomPropertyTypeLayout("E2LObservedProperty");
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEngine2LearnModule, Engine2Learn)