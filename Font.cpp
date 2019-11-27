#include "Font.h"

Font::Font(const std::string& filename, Graphics& gfx, Camera& camera, DWORD chroma)
	:
	font_sprite_(new Sprite(filename, glyph_width_, glyph_height_, 32)),
	camera_(&camera)
{
	font_sprite_->Initialize(gfx);
}

void Font::DrawTextString(const std::string& text, const Vec2<int>& pos, Graphics& gfx) const
{
	// curPos is the pos that we are drawing to on the screen
	auto curPos = pos;
	for (auto c : text)
	{
		// on a newline character, reset x position and move down by 1 glyph height
		if (c == '\n')
		{
			// carriage return
			curPos.x_ = pos.x_;
			// line feed
			curPos.y_ += glyph_height_;
			// we don't want to advance the character position right for a newline
			continue;
		}
		// only draw characters that are on the font sheet
		// start at firstChar + 1 because might as well skip ' ' as well
		else if (c >= first_char_ + 1 && c <= last_char_)
		{
			int frame_number = c - first_char_;
			Vec2<float> camera_transform = camera_->GetCameraTransform();
			font_sprite_->SetX(curPos.x_ - camera_transform.x_);
			font_sprite_->SetY(curPos.y_ - camera_transform.y_);
			font_sprite_->SetCurrentFrame(frame_number);
			font_sprite_->Draw();
		}
		// advance screen pos for next character
		curPos.x_ += glyph_width_;
	}
}