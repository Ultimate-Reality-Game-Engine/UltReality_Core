#ifndef ULTREALITY_CORE_CONFIG_RENDERER_CONFIG_H
#define ULTREALITY_CORE_CONFIG_RENDERER_CONFIG_H

#include <IRenderer_Settings.h>
#include <EventBase_t.h>

namespace UltReality::Configuration
{
	struct RendererConfig
	{
		Rendering::DisplaySettings displaySettings;
		Rendering::AntiAliasingSettings antiAliasingSettings;
		Rendering::TextureSettings textureSettings;
		Rendering::ShadowSettings shadowSettings;
		Rendering::LightingSettings lightingSettings;
		Rendering::PostProcessingSettings postProcessingSettings;
		Rendering::PerformanceSettings performanceSettings;
	};

	/// <summary>
	/// Enum class defining renderer configuration events
	/// </summary>
	enum class RendererConfigEvents
	{
		ERendererConfigChanged,
		EDisplaySettingsChanged,
		EAntiAliasingSettingsChanged,
		ETextureSettingsChanged,
		EShadowSettingsChanged,
		ELightingSettingsChanged,
		EPostProcessingSettingsChanged,
		EPerformanceSettingsChanged
	};

	/// <summary>
	/// Base event for renderer configuration events
	/// </summary>
	struct RendererConfigEvent : public Utilities::EventBase_t<RendererConfigEvents>
	{
		using EventBase_t::EventBase_t; // Inherit constructors
	};

	struct ERendererConfigChanged : public RendererConfigEvent
	{
		const RendererConfig& config;

		ERendererConfigChanged(const RendererConfig& c) : RendererConfigEvent(RendererConfigEvents::ERendererConfigChanged), config(c) {}
	};
	
	struct EDisplaySettingsChanged : public RendererConfigEvent
	{
		const Rendering::DisplaySettings& settings;

		EDisplaySettingsChanged(const Rendering::DisplaySettings& s) : RendererConfigEvent(RendererConfigEvents::EDisplaySettingsChanged), settings(s) {}
	};
	
	struct EAntiAliasingSettingsChanged : public RendererConfigEvent
	{
		const Rendering::AntiAliasingSettings& settings;

		EAntiAliasingSettingsChanged(const Rendering::AntiAliasingSettings& s) : RendererConfigEvent(RendererConfigEvents::EAntiAliasingSettingsChanged), settings(s) {}
	};

	struct ETextureSettingsChanged : public RendererConfigEvent
	{
		const Rendering::TextureSettings& settings;

		ETextureSettingsChanged(const Rendering::TextureSettings& s) : RendererConfigEvent(RendererConfigEvents::ETextureSettingsChanged), settings(s) {}
	};

	struct EShadowSettingsChanged : public RendererConfigEvent
	{
		const Rendering::ShadowSettings& settings;

		EShadowSettingsChanged(const Rendering::ShadowSettings& s) : RendererConfigEvent(RendererConfigEvents::EShadowSettingsChanged), settings(s) {}
	};

	struct ELightingSettingsChanged : public RendererConfigEvent
	{
		const Rendering::LightingSettings& settings;

		ELightingSettingsChanged(const Rendering::LightingSettings& s) : RendererConfigEvent(RendererConfigEvents::ELightingSettingsChanged), settings(s) {}
	};

	struct EPostProcessingSettingsChanged : public RendererConfigEvent
	{
		const Rendering::PostProcessingSettings& settings;

		EPostProcessingSettingsChanged(const Rendering::PostProcessingSettings& s) : RendererConfigEvent(RendererConfigEvents::EPostProcessingSettingsChanged), settings(s) {}
	};

	struct EPerformanceSettingsChanged : public RendererConfigEvent
	{
		const Rendering::PerformanceSettings& settings;

		EPerformanceSettingsChanged(const Rendering::PerformanceSettings& s) : RendererConfigEvent(RendererConfigEvents::EPerformanceSettingsChanged), settings(s) {}
	};
}

#endif // !ULTREALITY_CORE_CONFIG_RENDERER_CONFIG_H
