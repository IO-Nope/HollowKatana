#pragma once
#ifndef _ANIMATION_H
#define _ANIMATION_H

#include"util.h"
#include"timer.h"
#include"atlas.h"
#include"vector2.h"

#include<vector>
#include<functional>

class Animation
{
private:
	struct Frame
	{
		Rect rectSrc;
		IMAGE* image=nullptr;
		Frame() = default;
		~Frame() = default;
		Frame(IMAGE* image, const Rect& rectSrc) :image(image), rectSrc(rectSrc) {}
	};

public:
	enum class AnchorMode{
		Centered,
		BottomCentered
	};
private:
	Timer timer;
	Vector2 position;
	bool isLoop = true;
	size_t idxFrame = 0;
	std::vector<Frame> frameList;
	std::function<void()> onFinished;
	AnchorMode anchorMode = AnchorMode::Centered;
public:
	Animation() {
		timer.setOneShot(false);
		timer.setOnTimeOut(
			[&]() {
				idxFrame++;
				if(idxFrame>=frameList.size()){
					idxFrame = isLoop? 0 : frameList.size() - 1;
					if(!isLoop && onFinished)
						onFinished();
				}
			}
		);
	}
	~Animation() {}

	void reset() {
		idxFrame = 0;
		timer.restart();
	}
	void setAnchorMode(AnchorMode anchorMode) {
		this->anchorMode = anchorMode;
	}
	void setLoop(bool isLoop) {
		this->isLoop = isLoop;
	}
	void setPositon(const Vector2& position) {
		this->position = position;
	}
	void setInterval(float interval) {
		timer.setWaitTime(interval);
	}
	void setOnFinished(std::function<void()> onFinished) {
		this->onFinished = onFinished;
	}
	/// <summary>
	/// Œ™∂Øª≠ÃÌº”÷°£¨≤√ºÙÕº∆¨±‰≥…÷°∂Øª≠
	/// </summary>
	/// <param name="image"></param>
	/// <param name="rectSrc"></param>
	void addframe(IMAGE* image, int numH) {
		int width = image->getwidth();
		int height = image->getheight();
		int frameWidth = width / numH;
		for(int i = 0; i < numH;i++){
			Rect rectSrc;
			rectSrc.x = i * frameWidth;
			rectSrc.y = 0;
			rectSrc.w = frameWidth;
			rectSrc.h = height;
			frameList.push_back(Frame(image, rectSrc));
		}
	}
	void addframe(Atlas *atlas) {
		for (int i = 0; i < atlas->getSize(); i++) {
			IMAGE * image = atlas->getImage(i);
			int width = image->getwidth();
			int height = image->getheight();

			Rect rectSrc;
			rectSrc.x = 0;
			rectSrc.y = 0;
			rectSrc.w = width;
			rectSrc.h = height;

			frameList.push_back(Frame(image, rectSrc));
		}
	}
	void onUpdate(float delta) {
		timer.onUpdate(delta);
	}
	/// <summary>
	/// ‰÷»æ÷°∂Øª≠
	/// </summary>
	void onRender(){
		const Frame& frame = frameList[idxFrame];
		Rect rectDst;
		if (anchorMode == AnchorMode::Centered or anchorMode == AnchorMode::BottomCentered) {
			rectDst.x = (int)position.x - frame.rectSrc.w / 2;
			rectDst.y = (anchorMode == AnchorMode::Centered)
				? (int)position.y - frame.rectSrc.h / 2 : (int)position.y - frame.rectSrc.h;
			rectDst.w = frame.rectSrc.w;
			rectDst.h = frame.rectSrc.h;
		}
		putImageEx(frame.image, &rectDst, &frame.rectSrc); //‰÷»æ
	}


};
	 




#endif	// !_ANIMATION_H