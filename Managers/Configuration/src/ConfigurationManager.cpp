#include <ConfigurationManager.h>

namespace UltReality::Configuration
{
	ConfigurationManager& ConfigurationManager::GetInstance()
	{
		static ConfigurationManager instance;
		return instance;
	}

	void ConfigurationManager::ApplyRendererConfig(const RendererConfig& config)
	{
		m_rendererConfig = config;
		
		QueueEvent(ERendererConfigChanged(config));
	}

	void ConfigurationManager::ApplyDisplaySettings(const Rendering::DisplaySettings& settings)
	{
		m_rendererConfig.displaySettings = settings;

		QueueEvent(EDisplaySettingsChanged(settings));
	}

	void ConfigurationManager::ApplyAntiAliasingSettings(const Rendering::AntiAliasingSettings& settings)
	{
		m_rendererConfig.antiAliasingSettings = settings;

		QueueEvent(EAntiAliasingSettingsChanged(settings));
	}

	void ConfigurationManager::ApplyTextureSettings(const Rendering::TextureSettings& settings)
	{
		m_rendererConfig.textureSettings = settings;

		QueueEvent(ETextureSettingsChanged(settings));
	}

	void ConfigurationManager::ApplyShadowSettings(const Rendering::ShadowSettings& settings)
	{
		m_rendererConfig.shadowSettings = settings;

		QueueEvent(EShadowSettingsChanged(settings));
	}

	void ConfigurationManager::ApplyLightingSettings(const Rendering::LightingSettings& settings)
	{
		m_rendererConfig.lightingSettings = settings;

		QueueEvent(ELightingSettingsChanged(settings));
	}

	void ConfigurationManager::ApplyPostProcessingSettings(const Rendering::PostProcessingSettings& settings)
	{
		m_rendererConfig.postProcessingSettings = settings;

		QueueEvent(EPostProcessingSettingsChanged(settings));
	}

	void ConfigurationManager::ApplyPerformanceSettings(const Rendering::PerformanceSettings& settings)
	{
		m_rendererConfig.performanceSettings = settings;

		QueueEvent(EPerformanceSettingsChanged(settings));
	}
}