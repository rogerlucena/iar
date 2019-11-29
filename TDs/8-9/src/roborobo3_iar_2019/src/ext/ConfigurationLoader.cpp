#include "Config/ConfigurationLoader.h"
#include "Config/TemplateWanderConfigurationLoader.h"
#include "Config/TemplateBoidsConfigurationLoader.h"
#include "Config/TemplateRandomwalkConfigurationLoader.h"
#include "Config/TemplateEEConfigurationLoader.h"
#include "Config/TemplateVanillaEEConfigurationLoader.h"
#include "Config/TemplateMedeaConfigurationLoader.h"
#include "Config/ForagingRegionsConfigurationLoader.h"
#include "Config/TutorialConfigurationLoader.h"
#include "Config/TMEbraitenbergConfigurationLoader.h"
#include "Config/TMEdispersionConfigurationLoader.h"
#include "Config/TMEaggregationConfigurationLoader.h"
#include "Config/TMEboidsConfigurationLoader.h"
#include "Config/TMEevolutionConfigurationLoader.h"
//###DO-NOT-DELETE-THIS-LINE###TAG:INCLUDE###//


ConfigurationLoader::ConfigurationLoader()
{
	//nothing to do
}

ConfigurationLoader::~ConfigurationLoader()
{
	//nothing to do
}

ConfigurationLoader* ConfigurationLoader::make_ConfigurationLoader (std::string configurationLoaderObjectName)
{
	if (0)
	{
		// >>> Never reached
	}
#if defined PRJ_TEMPLATEWANDER || !defined MODULAR
	else if (configurationLoaderObjectName == "TemplateWanderConfigurationLoader" )
	{
		return new TemplateWanderConfigurationLoader();
	}
#endif
#if defined PRJ_TEMPLATEBOIDS || !defined MODULAR
	else if (configurationLoaderObjectName == "TemplateBoidsConfigurationLoader" )
	{
		return new TemplateBoidsConfigurationLoader();
	}
#endif
#if defined PRJ_TEMPLATERANDOMWALK || !defined MODULAR
	else if (configurationLoaderObjectName == "TemplateRandomwalkConfigurationLoader" )
	{
		return new TemplateRandomwalkConfigurationLoader();
	}
#endif
#if defined PRJ_TEMPLATEEE || !defined MODULAR
    else if (configurationLoaderObjectName == "TemplateEEConfigurationLoader" )
    {
        return new TemplateEEConfigurationLoader();
    }
#endif
#if defined PRJ_TEMPLATEVANILLAEE || !defined MODULAR
	else if (configurationLoaderObjectName == "TemplateVanillaEEConfigurationLoader" )
	{
		return new TemplateVanillaEEConfigurationLoader();
	}
#endif
#if defined PRJ_TEMPLATEMEDEA || !defined MODULAR
	else if (configurationLoaderObjectName == "TemplateMedeaConfigurationLoader" )
	{
		return new TemplateMedeaConfigurationLoader();
	}
#endif
#if defined PRJ_FORAGINGREGIONS || !defined MODULAR
	else if (configurationLoaderObjectName == "ForagingRegionsConfigurationLoader" )
	{
		return new ForagingRegionsConfigurationLoader();
	}
#endif
#if defined PRJ_TUTORIAL || !defined MODULAR
	else if (configurationLoaderObjectName == "TutorialConfigurationLoader" )
	{
		return new TutorialConfigurationLoader();
	}
#endif
#if defined PRJ_TMEBRAITENBERG || !defined MODULAR
	else if (configurationLoaderObjectName == "TMEbraitenbergConfigurationLoader" )
	{
		return new TMEbraitenbergConfigurationLoader();
	}
#endif
#if defined PRJ_TMEDISPERSION || !defined MODULAR
	else if (configurationLoaderObjectName == "TMEdispersionConfigurationLoader" )
	{
		return new TMEdispersionConfigurationLoader();
	}
#endif
#if defined PRJ_TMEAGGREGATION || !defined MODULAR
	else if (configurationLoaderObjectName == "TMEaggregationConfigurationLoader" )
	{
		return new TMEaggregationConfigurationLoader();
	}
#endif
#if defined PRJ_TMEBOIDS || !defined MODULAR
	else if (configurationLoaderObjectName == "TMEboidsConfigurationLoader" )
	{
		return new TMEboidsConfigurationLoader();
	}
#endif
#if defined PRJ_TMEEVOLUTION || !defined MODULAR
	else if (configurationLoaderObjectName == "TMEevolutionConfigurationLoader" )
	{
		return new TMEevolutionConfigurationLoader();
	}
#endif
    //###DO-NOT-DELETE-THIS-LINE###TAG:SWITCH###//
	else
	{
		return NULL;
	}

}
