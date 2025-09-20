#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <cmath>

namespace VertexShapes
{
    class Ring : public sf::Drawable, public sf::Transformable
    {
      protected:
        void draw(sf::RenderTarget &target,
                  sf::RenderStates states) const override;

      public:
        Ring(float innerRadius, float outerRadius, unsigned int points = 64);

        void setFillColor(const sf::Color &color);
        sf::Color getFillColor() const;
        void setRadius(float innerR, float outerR);

      private:
        sf::VertexArray vertices;
        unsigned int pointCount;
        float innerRadius, outerRadius;
        sf::Color fillColor;

        void updateGeometry();
    };
} // namespace VertexShapes
