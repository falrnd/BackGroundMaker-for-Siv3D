# include "MakerRect.hpp"

MakerRect::MakerRect() {
	//when optional(not shader) is empty 
	if (not rectgrad.has_value())
	{
		rectgrad = HLSL{ U"RectGradation.hlsl", U"PS" };
	}
}

auto MakerRect::colorPicker(const Vec2& base, HSV& color, Float4& c) {
	if (SimpleGUI::ColorPicker(color, base))
	{
		c = static_cast<Float4>(ColorF(color).rgba());
		cbNeedUpdate |= true;
	}
	return SimpleGUI::ColorPickerRegion(base);
}

void MakerRect::update(const Vec2& pos) {
	Vec2 c0Base = pos;

	if (KeyConfig::Misc.pressed())
	{
		c0Base = SimpleGUI::HorizontalRadioButtonsRegion(GradOptions, pos).bl() + Vec2{ 0,1 };
		SimpleGUI::HorizontalRadioButtons(gradation, GradOptions, pos);
	}

	auto c0Region = colorPicker(c0Base, color0, cb->c0);

	if (gradation != Flat)
	{
		const auto c1Region = colorPicker(c0Region.tr() + Vec2{ 1,0 }, color1, cb->c1);
		if (gradation == Quad)
		{
			const auto c2Region = colorPicker(c1Region.tr() + Vec2{ 1,0 }, color2, cb->c2);
			const auto c3Region = colorPicker(c2Region.tr() + Vec2{ 1,0 }, color3, cb->c3);
			if (cbNeedUpdate) {
				cbNeedUpdate = false;
				Graphics2D::SetPSConstantBuffer(1, cb);
			}
		}
	}
}

void MakerRect::drawRect() const {
	Rect rect{ Scene::Size() };

	switch (gradation)
	{
	case Flat:
		rect.draw(color0);
		break;
	case Horizontal:
		rect.draw(Arg::left = color0, Arg::right = color1);
		break;
	case Vertical:
		rect.draw(Arg::top = color0, Arg::bottom = color1);
		break;
	case Quad:
		//when shader(not optional) is loaded
		if (not rectgrad->isEmpty())
		{
			const ScopedCustomShader2D shader{ *rectgrad };
			Rect(Scene::Size())(Texture{}).draw();
		}
		else
		{
			//rect.draw({ color1,color2,color3,color4 });
			const ColorF centerColor = (
				color0.toColorF() +
				color1.toColorF() +
				color2.toColorF() +
				color3.toColorF()) * 0.25;

			Triangle{ rect.tl(), rect.tr(), rect.center() }.draw(color0, color1, centerColor);
			Triangle{ rect.tr(), rect.br(), rect.center() }.draw(color1, color2, centerColor);
			Triangle{ rect.br(), rect.bl(), rect.center() }.draw(color2, color3, centerColor);
			Triangle{ rect.bl(), rect.tl(), rect.center() }.draw(color3, color0, centerColor);
		}
		break;

	default:
		std::terminate();
	}
}
