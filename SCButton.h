#ifndef SCButton_h
#define SCButton_h

#include <Arduino.h>
#include <SCPeriod.h>

class SCButton {
public:
  typedef void (*dlgOnButton)(void* instance, String name, bool pressed, bool firstTime);
  typedef bool (*dlgGetButtonState)(String name);
public:
  SCButton(void* instance, String name, bool isInverted, uint16_t delayUntilFirstReactionIn10MS, uint16_t delayAfterFirstReactionIn10MS, dlgOnButton onButton, dlgGetButtonState getButtonState);
  virtual ~SCButton();
  void Check();
private:
  static void OnPeriodExpiredStatic(void* instance);
  void OnPeriodExpired();
private:
  SCPeriod* mPeriod;
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

#endif  //SCButton_h