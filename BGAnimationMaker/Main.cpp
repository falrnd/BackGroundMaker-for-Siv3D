# include <Siv3D.hpp> // OpenSiv3D v0.6.3

# include "MakerRect.hpp"

void Main()
{
	Window::SetStyle(WindowStyle::Sizable);

	MakerRect makerRect{};

	while (System::Update())
	{
		makerRect.drawRect();

		if (not KeyConfig::NoShow.pressed()) {
			SimpleGUI::Headline(U"詳細設定:Shift 非表示:Q", { 3,3 });
			makerRect.update({ 3,46 });
		}
	}
}
