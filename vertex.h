#pragma once

struct Vec2 {
    float x, y;

    Vec2(float x, float y) : x(x), y(y) {}
    Vec2(float both) : x(both), y(both) {}
    Vec2() : x(0), y(0) {}

    Vec2 operator+(Vec2 &other) {
        return {x + other.x, y + other.y};
    }
    void operator+=(Vec2 &other) {
        x += other.x;
        y += other.y;
    }

    Vec2 operator-(Vec2 &other) {
        return {x - other.x, y - other.y};
    }
    void operator-=(Vec2 &other) {
        x -= other.x;
        y -= other.y;
    }

    Vec2 operator*(Vec2 &other) {
        return {x * other.x, y * other.y};
    }
    void operator*=(Vec2 &other) {
        x *= other.x;
        y *= other.y;
    }

    Vec2 operator/(Vec2 &other) {
        return {x / other.x, y / other.y};
    }
    void operator/=(Vec2 &other) {
        x /= other.x;
        y /= other.y;
    }

    Vec2 operator+(float other) {
        return {x + other, y + other};
    }
    void operator+=(float other) {
        x += other;
        y += other;
    }

    Vec2 operator-(float other) {
        return {x - other, y - other};
    }
    void operator-=(float other) {
        x -= other;
        y -= other;
    }

    Vec2 operator*(float other) {
        return {x * other, y * other};
    }
    void operator*=(float other) {
        x *= other;
        y *= other;
    }

    Vec2 operator/(float other) {
        return {x / other, y / other};
    }
    void operator/=(float other) {
        x /= other;
        y /= other;
    }
};

struct Vec2i {
    int x, y;

    Vec2i(int x, int y) : x(x), y(y) {}
    Vec2i(int both) : x(both), y(both) {}

    Vec2i operator+(Vec2i &other) {
        return {x + other.x, y + other.y};
    }
    void operator+=(Vec2i &other) {
        x += other.x;
        y += other.y;
    }

    Vec2i operator-(Vec2i &other) {
        return {x - other.x, y - other.y};
    }
    void operator-=(Vec2i &other) {
        x -= other.x;
        y -= other.y;
    }

    Vec2i operator*(Vec2i &other) {
        return {x * other.x, y * other.y};
    }
    void operator*=(Vec2i &other) {
        x *= other.x;
        y *= other.y;
    }

    Vec2i operator/(Vec2i &other) {
        return {x / other.x, y / other.y};
    }
    void operator/=(Vec2i &other) {
        x /= other.x;
        y /= other.y;
    }
};

struct Vec3 {
    float x, y, z;

    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vec3(float both) : x(both), y(both), z(both) {}
    Vec3(Vec2 v, float z) : x(v.x), y(v.y), z(z) {}

    Vec3 operator+(Vec3 &other) {
        return {x + other.x, y + other.y, z + other.z};
    }
    void operator+=(Vec3 &other) {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    Vec3 operator-(Vec3 &other) {
        return {x - other.x, y + other.y, z + other.z};
    }
    void operator-=(Vec3 &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

    Vec3 operator*(Vec3 &other) {
        return {x * other.x, y * other.y, z * other.z};
    }
    void operator*=(Vec3 &other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
    }

    Vec3 operator/(Vec3 &other) {
        return {x / other.x, y / other.y, z / other.z};
    }
    void operator/=(Vec3 &other) {
        x /= other.x;
        y /= other.y;
        z /= other.z;
    }
};

struct Color {
    Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
    float r, g, b, a;
};

struct Vertex {
    Vec3 pos;
    Vec2 uv;
    float r, g, b, a;
};
