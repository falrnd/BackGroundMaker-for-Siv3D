# pragma once

# include <Siv3D.hpp> // v0.6.3

namespace KeyConfig {
	constexpr auto Misc = KeyShift;
	constexpr auto NoShow = KeyQ;
}

class MakerRect {
public:
	HSV color0 = Palette::Red;
	HSV color1 = Palette::White;
	HSV color2 = Palette::Lime;
	HSV color3 = Palette::Blue;

private:
	inline static Optional<PixelShader> rectgrad{};

	struct Color4
	{
		Float4 c0, c1, c2, c3;
	};
	ConstantBuffer<Color4> cb{ {
		ColorF(color0).rgba(),
		ColorF(color1).rgba(),
		ColorF(color2).rgba(),
		ColorF(color3).rgba()
	} };

public:
	bool cbNeedUpdate = true;

	MakerRect();

	inline static const Array<String> GradOptions
	{
		U"単色",
		U"2色横グラデ",
		U"2色縦グラデ",
		U"4色グラデ",
	};
	enum GradOptions
	{
		Flat = 0,
		Horizontal = 1,
		Vertical = 2,
		Quad = 3,
	};
	size_t gradation = Flat;

private:
	auto colorPicker(const Vec2& base, HSV& color, Float4& c);

public:
	void update(const Vec2& pos);

	void drawRect() const;
};
