#pragma once
#ifndef _VECTOR_ESP_
#define _VECTOR_ESP_
#include<Windows.h>
#include <math.h>
#include <numbers>
#include <cmath>
#include <vector>
#include <map>
struct view_matrix_t 
{
	float* operator[ ](int index) {
		return matrix[index];
	}

	float matrix[4][4]; // 0x00
};

namespace DATA
{
	extern view_matrix_t ViewMatrix;
	extern int windowWidth;
	extern int windowHeight;
	extern std::vector<std::pair<int, int>> BoneMap;
}
struct Vector3
{
	// constructor
	constexpr Vector3(
		const float x = 0.f,
		const float y = 0.f,
		const float z = 0.f) noexcept :
		x(x), y(y), z(z) {
	}

	// operator overloads
	constexpr const Vector3& operator-(const Vector3& other) const noexcept
	{
		return Vector3{ x - other.x, y - other.y, z - other.z };
	}

	constexpr const Vector3& operator+(const Vector3& other) const noexcept
	{
		return Vector3{ x + other.x, y + other.y, z + other.z };
	}

	constexpr const Vector3& operator/(const float factor) const noexcept
	{
		return Vector3{ x / factor, y / factor, z / factor };
	}

	constexpr const Vector3& operator*(const float factor) const noexcept
	{
		return Vector3{ x * factor, y * factor, z * factor };
	}

	constexpr const bool operator>(const Vector3& other) const noexcept {
		return x > other.x && y > other.y && z > other.z;
	}

	constexpr const bool operator>=(const Vector3& other) const noexcept {
		return x >= other.x && y >= other.y && z >= other.z;
	}

	constexpr const bool operator<(const Vector3& other) const noexcept {
		return x < other.x && y < other.y && z < other.z;
	}

	constexpr const bool operator<=(const Vector3& other) const noexcept {
		return x <= other.x && y <= other.y && z <= other.z;
	}

	// utils
	constexpr const Vector3& ToAngle() const noexcept
	{
		return Vector3{
			std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>),
			std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>),
			0.0f };
	}

	float length() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	float length2d() const {
		return std::sqrt(x * x + y * y);
	}

	constexpr const bool IsZero() const noexcept
	{
		return x == 0.f && y == 0.f && z == 0.f;
	}

	float calculate_distance(const Vector3& point) const {
		float dx = point.x - x;
		float dy = point.y - y;
		float dz = point.z - z;

		return std::sqrt(dx * dx + dy * dy + dz * dz);
	}

	// struct data
	float x, y, z;
};
#endif

namespace Module
{
	uintptr_t GetBase(LPCSTR namemodule);
}

namespace Camera
{
	view_matrix_t GetViewMatrix(LPCSTR namemodule);
	Vector3 WorldToScreen(Vector3* v);
	uintptr_t GetYViewAngles(LPCSTR namemodule);
	uintptr_t GetXViewAngles(LPCSTR namemodule);
	Vector3 GetLastClipCameraPos(uintptr_t Pawn);
}


namespace UPlayer
{
	int GetTeamID(uintptr_t Pawn);
	Vector3 GetLocaltion(uintptr_t Pawn);
	int GetHealth(uintptr_t Pawn);
	uintptr_t GetBoneArray(uintptr_t Pawn);
	Vector3 GetPostionBone(uintptr_t Pawn, int BoneIndex);
}
namespace Entity
{
	uintptr_t GetLocalPlayer(LPCSTR namemodule);
	uintptr_t GetPawn(uintptr_t Entity);
	uintptr_t GetpCSPlayerPawn(LPCSTR namemodule, uintptr_t Entity);
	uintptr_t GetEntityList(LPCSTR namemodule);
	std::vector<uintptr_t> GetListPlayer(LPCSTR namemodule);
}