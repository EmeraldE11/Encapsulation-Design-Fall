/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#pragma once


class Velocity;        // for Position::add()
class Acceleration;    // for Position::add()
class TestPosition;    // for the unit tests
class TestLander;      // for the unit tests

/*********************************************
 * POSITION
 * A single position on the screen
 *********************************************/
class Position
{
    friend TestPosition;    // for the unit tests
    friend TestLander;      // for the unit tests

public:
    // constructors
    Position() : x(0.0), y(0.0) {}
    Position(const Position& pos) : x(pos.x), y(pos.y) {}
    Position(double x, double y);

    // getters
    double getMetersX() const { return x; }
    double getMetersY() const { return y; }
    double getX() const { return getMetersX(); }  // compatibility
    double getY() const { return getMetersY(); }
    double getPixelsX() const { return x / metersFromPixels; }
    double getPixelsY() const { return y / metersFromPixels; }
    bool operator == (const Position& rhs) const
    {
        return (x == rhs.x && y == rhs.y);
    }
    bool operator != (const Position& rhs) const
    {
        return !(*this == rhs);
    }

    // setters
    void setMetersX(double x) { this->x = x; }
    void setMetersY(double y) { this->y = y; }
    void setX(double x) { setMetersX(x); }  // compatibility
    void setY(double y) { setMetersY(y); }
    void setPixelsX(double pixelX) { this->x = pixelX * metersFromPixels; }
    void setPixelsY(double pixelY) { this->y = pixelY * metersFromPixels; }
    void addMetersX(double delta) { this->x += delta; }
    void addMetersY(double delta) { this->y += delta; }
    void addX(double delta) { addMetersX(delta); }  // compatibility
    void addY(double delta) { addMetersY(delta); }
    void addPixelsX(double deltaPixels) { this->x += deltaPixels * metersFromPixels; }
    void addPixelsY(double deltaPixels) { this->y += deltaPixels * metersFromPixels; }
    void add(const Acceleration& a, const Velocity& v, double t);
    void add(const Acceleration& a, const Velocity& v) { add(a, v, 1.0); }
    Position& operator = (const Position& rhs)
    {
        x = rhs.x;
        y = rhs.y;
        return *this;
    }

    static void setZoom(double metersPerPixel) { metersFromPixels = metersPerPixel; }
    static double getZoom() { return metersFromPixels; }

private:
    double x;           // horizontal position
    double y;           // vertical position
    static double metersFromPixels;
};

