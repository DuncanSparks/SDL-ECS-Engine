/*************************************************************************/
/*       Some functions in this file are adopted from Godot Engine       */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2020 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2020 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "Vector2.h"

#include <cmath>

const Vector2 Vector2::Zero = Vector2{0, 0};

Vector2::Vector2() : x{0}, y{0} {}
Vector2::Vector2(float x_, float y_) : x{x_}, y{y_} {}
Vector2::Vector2(const Vector2& rvalue) : x{rvalue.x}, y{rvalue.y} {}
Vector2& Vector2::operator=(const Vector2& rvalue) {
	if (this != &rvalue) {
		x = rvalue.x;
		y = rvalue.y;
	}

	return *this;
}

Vector2::operator Vector2I() const {
	return Vector2I{static_cast<int>(x), static_cast<int>(y)};
}


float Vector2::angle() const {
	return std::atan2(y, x);
}

void Vector2::set_rotation(float radians) {
	x = std::cos(radians);
	y = std::sin(radians);
}

float Vector2::magnitude() const {
	return std::sqrt(x * x + y * y);
}

Vector2 Vector2::normalized() const {
	float m = magnitude();
	return m == 0 ? Vector2{x, y} : Vector2{x / m, y / m};
}

float Vector2::dot(const Vector2& rvalue) const {
	return x * rvalue.x + y * rvalue.y;
}

float Vector2::cross(const Vector2& rvalue) const {
	return x * rvalue.y - y * rvalue.x;
}

float Vector2::distance_to(const Vector2& rvalue) const {
	return std::sqrt((x - rvalue.x) * (x - rvalue.x) + (y - rvalue.y) * (y - rvalue.y));
}

float Vector2::angle_to(const Vector2& rvalue) const {
	return std::atan2(y - rvalue.y, x - rvalue.x);
}

Vector2 Vector2::rotated(float by) const {
	Vector2 v;
	v.set_rotation(angle() + by);
	v *= magnitude();
	return v;
}


Vector2 Vector2::operator+(const Vector2& rvalue) const {
	return Vector2{x + rvalue.x, y + rvalue.y};
}

Vector2 Vector2::operator-(const Vector2& rvalue) const {
	return Vector2{x - rvalue.x , y - rvalue.y};
}

Vector2 Vector2::operator*(const float& rvalue) const {
	return Vector2{x * rvalue, y * rvalue};
}

Vector2 Vector2::operator/(const float& rvalue) const {
	return Vector2{x / rvalue, y / rvalue};
}


Vector2& Vector2::operator+=(const Vector2& rvalue) {
	x += rvalue.x;
	y += rvalue.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& rvalue) {
	x -= rvalue.x;
	y -= rvalue.y;
	return *this;
}

Vector2& Vector2::operator*=(const float& rvalue) {
	x *= rvalue;
	y *= rvalue;
	return *this;
}

Vector2& Vector2::operator/=(const float& rvalue) {
	x /= rvalue;
	y /= rvalue;
	return *this;
}


Vector2 Vector2::operator-() const {
	return Vector2{*this} * -1;
}


bool Vector2::operator==(const Vector2& rvalue) const {
	return x == rvalue.x && y == rvalue.y;
}

bool Vector2::operator!=(const Vector2& rvalue) const {
	return x != rvalue.x || y != rvalue.y;
}

// =====================================================================

Vector2I::Vector2I() : x{0}, y{0} {}
Vector2I::Vector2I(int x_, int y_) : x{x_}, y{y_} {}
Vector2I::Vector2I(const Vector2I& rvalue) : x{rvalue.x}, y{rvalue.y} {}
Vector2I& Vector2I::operator=(const Vector2I& rvalue) {
	if (this != &rvalue) {
		x = rvalue.x;
		y = rvalue.y;
	}

	return *this;
}

Vector2I::operator Vector2() const {
	return Vector2{static_cast<float>(x), static_cast<float>(y)};
}
