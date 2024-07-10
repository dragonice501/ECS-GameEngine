#pragma once

struct Vec2
{
    float x;
    float y;

    Vec2() : Vec2(0.0f, 0.0f) {}
    Vec2(float p) : Vec2(p, p) {}
    Vec2(float x, float y) : x(x), y(y) {}
    
    static inline const Vec2 Zero() { return Vec2(0.0f, 0.0f); }
    static inline const float Cross(const Vec2& a, const Vec2& b) { return (a.x * b.y) - (a.y * b.x); }

    ~Vec2() = default;

    Vec2& operator = (const Vec2& v);        
    bool operator == (const Vec2& v) const;  
    bool operator != (const Vec2& v) const;  

    Vec2 operator + (const Vec2& v) const;   
    Vec2 operator - (const Vec2& v) const;   
    Vec2 operator * (const float n) const;   
    Vec2 operator / (const float n) const;   
    Vec2 operator - ();                      

    Vec2& operator += (const Vec2& v);       
    Vec2& operator -= (const Vec2& v);       
    Vec2& operator *= (const float n);       
    Vec2& operator /= (const float n);       

    void Add(const Vec2& v);                 
    void Sub(const Vec2& v);                 
    void Scale(const float n);               
    void Rotate(const float degree);
    void RotateAroundPoint(const Vec2& point, const float degree);

    float Magnitude() const;         
    float MagnitudeSquared() const;  

    Vec2& Normalize();
    Vec2 UnitVector() const;
    Vec2 Normal() const;
    Vec2 ProjectOnto(const Vec2& vec2);
    Vec2 Reflect(const Vec2& plane);

    float Dot(const Vec2& v) const;
    float Cross(const Vec2& v) const;
};