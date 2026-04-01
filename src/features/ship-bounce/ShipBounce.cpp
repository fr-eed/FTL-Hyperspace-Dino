#include "ShipBounce.h"
#include "Global.h"
#include <cmath>

namespace ShipBounce
{

static bool enabled = false;

static const float BOUNCE_SPEED = 14.14f;   // 135 BPM
static const float SQUASH_AMOUNT = 0.12f;   // 12% squash/stretch

static float EasedSine(float t)
{
    float s = std::sin(t);
    return (s >= 0 ? 1.0f : -1.0f) * std::sqrt(std::abs(s));
}

static float GetScaleX()
{
    float time = G_->GetCFPS()->RunningTime;
    return 1.0f + EasedSine(time * BOUNCE_SPEED) * SQUASH_AMOUNT;
}

static float GetScaleY()
{
    float time = G_->GetCFPS()->RunningTime;
    return 1.0f - EasedSine(time * BOUNCE_SPEED) * SQUASH_AMOUNT;
}

void Toggle()
{
    enabled = !enabled;
}

void OnRenderShipPre(int shipId)
{
    if (!enabled) return;
    CSurface::GL_PushMatrix();

    auto shipGraph = ShipGraph::GetShipInfo(shipId);
    if (!shipGraph) return;

    float centerX = shipGraph->shipBox.x + shipGraph->shipBox.w / 2.0f;
    float centerY = shipGraph->shipBox.y + shipGraph->shipBox.h / 2.0f;

    CSurface::GL_Translate(centerX, centerY);
    CSurface::GL_Scale(GetScaleX(), GetScaleY(), 1.0f);
    CSurface::GL_Translate(-centerX, -centerY);
}

void OnRenderShipPost()
{
    if (!enabled) return;
    CSurface::GL_PopMatrix();
}

void OnRenderPlayerShipPre(int centerX, int centerY)
{
    if (!enabled) return;
    CSurface::GL_PushMatrix();

    float cx = static_cast<float>(centerX);
    float cy = static_cast<float>(centerY);

    CSurface::GL_Translate(cx, cy);
    CSurface::GL_Scale(GetScaleX(), GetScaleY(), 1.0f);
    CSurface::GL_Translate(-cx, -cy);
}

void OnRenderPlayerShipPost()
{
    if (!enabled) return;
    CSurface::GL_PopMatrix();
}

} // namespace ShipBounce
