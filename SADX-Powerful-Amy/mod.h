#pragma once

extern HelperFunctions HelperFunctionsGlobal;
void ReadConfig(const char* path, const HelperFunctions& helperFunctions);

extern Buttons BounceButton;
extern Buttons LightDashButton;
extern Buttons SpinDashButton;
extern bool isHomingAttack;
extern Buttons HammerAttackButton;

void ActionRemap_Config(const IniFile* config);
void init_ActionRemap();

#define TRAMPOLINE(name) ((decltype(name##_r)*)name##_t->Target())

void init_Helper();

constexpr int amyAnimcount = 4;
extern AnimData NewAmyAnimData[102 + amyAnimcount];
Buttons GetHammerAttackButton();

enum AmyActions {
	Act_Amy_Init,
	Act_Amy_Stand,
	Act_Amy_Walk,
	Act_Amy_Path1,
	Act_Amy_DashSpeedPanel,
	Act_Amy_Jump,
	Act_Amy_Spring,
	Act_Amy_Launch,
	Act_Amy_Fall,
	Act_Amy_Brake,
	Act_Amy_Push,
	Act_Amy_Damage,
	Act_Amy_Back,
	Act_Amy_ObjectControl,
	Act_Amy_Knocked,
	Act_Amy_Handle,
	Act_Amy_Balance,
	Act_Amy_BarrelOn,
	Act_Amy_BarrelOff,
	Act_Amy_HammerAttack,
	Act_Amy_HammerSpin,
	Act_Amy_HammerJump,
	Act_Amy_AirHammerAttack,
	Act_Amy_PickObject,
	Act_Amy_PutObject,
	Act_Amy_HoldObject,
	Act_Amy_ThrowObject,
	Act_Amy_WalkObject,
	Act_Amy_Throw,
	Act_Amy_BrakeObject,
	Act_Amy_FallObject,
	Act_Amy_JumpObject,
	Act_Amy_SpringObject,
	Act_Amy_LaunchObject,
	Act_Amy_Pull,
	Act_Amy_AirThrow,
	Act_Amy_ShakeTree,
	Act_Amy_Shaken,
	Act_Amy_MonkeyBar,
	Act_Amy_MonkeyBarMove,
	Act_Amy_Ladder,
	Act_Amy_LadderMove,
	Act_Amy_JumpPanel,
	Act_Amy_JumpPanelOn,
	Act_Amy_Captured,
	Act_Amy_Event,
	Act_Amy_Drown,
	Act_Amy_Death,
	Act_Amy_BumperCar,
	Act_Amy_PetStart,
	Act_Amy_Pet,
	Act_Amy_PetSop,
	Act_Amy_Whistle,
	Act_Amy_Debug,

	//new tricks
	Act_Amy_HammerProp,
	Act_Amy_TailsGrab,
	// Custom Ones

	Act_Amy_SpinDash = 60,
	Act_Amy_Rolling,
	Act_Amy_HomingAttack,
	Act_Amy_Bounce,
	Act_Amy_BounceUp,
	Act_Amy_LightDash,
	Act_Amy_HammerAttackR,
	Act_Amy_SpinR,
};

enum AmyAnimations {
	Anm_Amy_Stand,
	Anm_Amy_Jump = 14,
	Anm_Amy_Fall = 18,
	Anm_Amy_Brake = 20,
	Anm_Amy_HangHook = 55,
	Anm_Amy_HammerSpinAttack = 90,
	Anm_Amy_DizzyStand,
	Anm_Amy_DizzyWalk,
	Anm_Amy_HammerSomerTrickA = 95,
	Anm_Amy_HammerSomerTrickB,
	Anm_Amy_HammerSomerTrickC,

	//custom
	Anm_Amy_SpinDash = 102,
	Anm_Amy_Rolling,
	Anm_Amy_SpinBall
};

void init_AmyHacks();
void Load_AmyNewMDlAnim();
void InitSA2AnimHack(AnimThing* animinfo);
void Init_AmyNewAnim();
void init_BirdHack();

enum AmyCustomSound {
	Snd_HomingAttack = 821,
	Snd_SpinDash,
	Snd_SpinDashRelease
};