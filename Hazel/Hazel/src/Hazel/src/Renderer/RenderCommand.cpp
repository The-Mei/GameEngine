#include "Hzpch.h"

#include "Renderer/RenderCommand.h"

#include "OpenGlRendererAPI.h"

namespace Hazel
{
    RendererAPI *RenderCommand::sRendererAPI = new OpenGlRendererAPI();
}