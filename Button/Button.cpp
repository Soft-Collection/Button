#include "Button.h"

Button::Button(void* instance, String name, bool isInverted, uint16_t delayUntilFirstReactionIn10MS, uint16_t delayAfterFirstReactionIn10MS, dlgOnButton onButton, dlgGetButtonState getButtonState) {
  mPeriod = new Period(this, 10, true, Button::OnPeriodExpiredStatic);
  //--------------------------------------
  mCurrentButtonState = false;
  mLastButtonState = false;
  mTimeUntilNextReaction = 0;
  //--------------------------------------
  mInstance = instance;
  mOnButton = onButton;
  mGetButtonState = getButtonState;
  //--------------------------------------
  mName = name;
  mIsInverted = isInverted;
  mDelayUntilFirstReactionIn10MS = delayUntilFirstReactionIn10MS;
  mDelayAfterFirstReactionIn10MS = delayAfterFirstReactionIn10MS;
}
Button::~Button() {
}
void Button::Check(uint32_t ticks) {
  mPeriod->Check(ticks);
}
void Button::OnPeriodExpiredStatic(void* instance) {
  Button* bt = (Button*)instance;
  if (bt != NULL) bt->OnPeriodExpired();
}
void Button::OnPeriodExpired() {
  if (!mGetButtonState) return;
  mCurrentButtonState = mGetButtonState(mName);
  if (mLastButtonState != mCurrentButtonState)  //Button state changed.
  {
    if (mCurrentButtonState)  //Just now Button Pressed.
    {
      if (mOnButton) mOnButton(mInstance, mName, true, true);
      mTimeUntilNextReaction = mDelayUntilFirstReactionIn10MS;
    } 
    else  //Just now Button Released.
    {
      if (mOnButton) mOnButton(mInstance, mName, false, true);
      mTimeUntilNextReaction = 0;
    }
    mLastButtonState = mCurrentButtonState;
  } 
  else  //Button state unchanged.
  {
    if (mCurrentButtonState)  //Button is Pressed.
    {
      if (mTimeUntilNextReaction > 0)  //Wait until next reaction.
      {
        if (mTimeUntilNextReaction == 1)  //Perform next reaction.
        {
          if (mOnButton) mOnButton(mInstance, mName, true, false);
          mTimeUntilNextReaction = mDelayAfterFirstReactionIn10MS;
        }
        mTimeUntilNextReaction--;
      }
    }
  }
}