#ifndef Button_h
#define Button_h

#include <Arduino.h>
#include "Period.h"

class Button {
public:
  typedef void (*dlgOnButton)(void* instance, String name, bool pressed, bool firstTime);
  typedef bool (*dlgGetButtonState)(String name);
public:
  Button(void* instance, String name, bool isInverted, uint16_t delayUntilFirstReactionIn10MS, uint16_t delayAfterFirstReactionIn10MS, dlgOnButton onButton, dlgGetButtonState getButtonState);
  virtual ~Button();
  void Check(uint32_t ticks);
private:
  static void OnPeriodExpiredStatic(void* instance);
  void OnPeriodExpired();
private:
  Period* mPeriod;
  //--------------------------------------
  bool mCurrentButtonState;
  bool mLastButtonState;
  uint16_t mTimeUntilNextReaction;
  //--------------------------------------
  void* mInstance;
  dlgOnButton mOnButton;
  dlgGetButtonState mGetButtonState;
  //--------------------------------------
  String mName;
  bool mIsInverted;
  uint16_t mDelayUntilFirstReactionIn10MS;
  uint16_t mDelayAfterFirstReactionIn10MS;
};

#endif  //Button_h