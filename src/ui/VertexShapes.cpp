#include <wisp/ui/VertexShapes.hpp>

namespace wisp::VertexShapes
{
    Ring::Ring(float innerRadius, float outerRadius, unsigned int points)
        : innerRadius(innerRadius)
        , outerRadius(outerRadius)
        , pointCount(points)
        , fillColor(sf::Color::White)
    {
        setOrigin({0, 0});
        vertices.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
        updateGeometry();
    }

    void Ring::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(vertices, states);
    }

    void Ring::setFillColor(const sf::Color &color)
    {
        fillColor = color;
        for(size_t i = 0; i < vertices.getVertexCount(); ++i)
        {
            vertices[i].color = fillColor;
        }
    }

    sf::Color Ring::getFillColor() const { return fillColor; }

    void Ring::setRadius(float innerR, float outerR)
    {
        innerRadius = innerR;
        outerRadius = outerR;
        updateGeometry();
    }

    void Ring::updateGeometry()
    {
        vertices.clear();
        vertices.setPrimitiveType(sf::PrimitiveType::TriangleStrip);

        for(unsigned int i = 0; i <= pointCount; ++i)
        {
            float angle = i * 2 * M_PI / pointCount;
            float cosA = std::cos(angle), sinA = std::sin(angle);

            sf::Vector2f innerPoint(innerRadius * cosA, innerRadius * sinA);
            sf::Vector2f outerPoint(outerRadius * cosA, outerRadius * sinA);

            vertices.append(sf::Vertex(innerPoint, fillColor));
            vertices.append(sf::Vertex(outerPoint, fillColor));
        }
    }
} // namespace wisp::VertexShapes
