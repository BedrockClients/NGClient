#include "ImmediateGui.h"

ImmediateGui HImGui;

ComponentInfo::ComponentInfo(int id)
	: id(id) {
}

ButtonInfo::ButtonInfo(int id, vec2 pos, bool centered)
	: ComponentInfo(id), pos(pos), centered(centered) {
}

void ButtonInfo::calculateSize(const char* txt) {
	std::string str(txt);
	this->size = {DrawUtils::getTextWidth(&str), DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight()};
}

bool ButtonInfo::isInSelectableSurface(vec2 mouse) {
	vec4 surface = getSelectableSurface();
	return surface.contains(&mouse);
}

vec4 ButtonInfo::getSelectableSurface() {
	if (centered) {
		return {this->pos.x - padding - this->size.x / 2,
				this->pos.y - padding - this->size.y / 2,
				this->pos.x + padding + this->size.x / 2,
				this->pos.y + padding + this->size.y / 2};
	} else {
		return {this->pos.x - padding,
				this->pos.y - padding,
				this->pos.x + padding + this->size.x,
				this->pos.y + padding + this->size.y};
	}
}

void ButtonInfo::draw(vec2 mousePos, const char* label) {
	calculateSize(label);
	auto surface = getSelectableSurface();
	vec2 textPos = pos;
	std::string str(label);
	if (centered) {
		textPos.x -= DrawUtils::getTextWidth(&str) / 2;
		textPos.y -= DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2;
	}

	DrawUtils::drawText(textPos, &str, MC_Color());
	if (isInSelectableSurface(mousePos)) {  // Mouse hovering over us
		DrawUtils::fillRectangle(surface, MC_Color(15, 15, 15), 0.8);
		DrawUtils::drawRectangle(surface, MC_Color(0, 0, 255), 0.8);
		this->canClickB = true;
	} else {
		DrawUtils::fillRectangle(surface, MC_Color(0, 0, 0), 1);
		DrawUtils::drawRectangle(surface, MC_Color(0, 0, 255), 1);
		this->canClickB = false;
	}
}

void ImmediateGui::onMouseClickUpdate(int key, bool isDown) {
	switch (key) {
	case 1:  // Left Click
		this->leftMb.nextIsDown = true;
		break;
	case 2:  // Right Click
		this->rightMb.nextIsDown = true;
		break;
	}
}

void ImmediateGui::startFrame() {
	vec2 windowSize = g_Data.getClientInstance()->getGuiData()->windowSize;
	vec2 windowSizeReal = g_Data.getClientInstance()->getGuiData()->windowSizeReal;
	this->mousePos = *g_Data.getClientInstance()->getMousePos();
	this->mousePos = this->mousePos.div(windowSizeReal);
	this->mousePos = this->mousePos.mul(windowSize);

	this->leftMb.update();
	this->rightMb.update();

	if (g_Data.getClientInstance()->getMouseGrabbed()) {
		this->leftMb.isClicked = false;
		this->rightMb.isClicked = false;
	}
}

void ImmediateGui::endFrame() {
	this->leftMb.isClicked = false;
	this->rightMb.isClicked = false;
}

bool ImmediateGui::Button(const char* label, vec2 pos, bool centered) {
	auto id = Utils::getCrcHash(label);
	if (this->components.find(id) == this->components.end()) {  // Create new button
		this->components[id] = std::make_shared<ButtonInfo>(id, pos, centered);
	}
	auto comp = this->components[id];
	auto button = dynamic_cast<ButtonInfo*>(comp.get());

	button->updatePos(pos);
	button->draw(this->mousePos, label);
	if (button->canClick() && g_Data.isLeftClickDown()) {  // Click
		g_Data.hidController->leftClickDown = false;
		return true;
	}

	return false;
}
