#ifndef ULTREALITY_CORE_CONFIGURATION_MANAGER_H
#define ULTREALITY_CORE_CONFIGURATION_MANAGER_H

#include <EventSource_t.h>

#include <RendererConfig.h>

namespace UltReality::Configuration
{
	/// <summary>
	/// Singleton class that manages the configuration of the application
	/// </summary>
	class ConfigurationManager : public Utilities::EventSource_t<RendererConfigEvent>
	{
	private:
		RendererConfig m_rendererConfig;

		ConfigurationManager() = default;
		~ConfigurationManager() = default;

	public:
		static ConfigurationManager& GetInstance();

		void ApplyRendererConfig(const RendererConfig& config);
		void ApplyDisplaySettings(const Rendering::DisplaySettings& settings);
		void ApplyAntiAliasingSettings(const Rendering::AntiAliasingSettings& settings);
		void ApplyTextureSettings(const Rendering::TextureSettings& settings);
		void ApplyShadowSettings(const Rendering::ShadowSettings& settings);
		void ApplyLightingSettings(const Rendering::LightingSettings& settings);
		void ApplyPostProcessingSettings(const Rendering::PostProcessingSettings& settings);
		void ApplyPerformanceSettings(const Rendering::PerformanceSettings& settings);

		ConfigurationManager(const ConfigurationManager&) = delete;
		ConfigurationManager& operator=(const ConfigurationManager&) = delete;

		ConfigurationManager(ConfigurationManager&&) = delete;
		ConfigurationManager& operator=(ConfigurationManager&&) = delete;
	};
}

#endif // !ULTREALITY_CORE_CONFIGURATION_MANAGER_H
