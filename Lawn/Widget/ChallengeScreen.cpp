#include "GameButton.h"
#include "../../LawnApp.h"
#include "../System/Music.h"
#include "ChallengeScreen.h"
#include "../../Resources.h"
#include "../ToolTipWidget.h"
#include "../System/PlayerInfo.h"
#include "../../Sexy.TodLib/TodDebug.h"
#include "../../Sexy.TodLib/TodFoley.h"
#include "../../Sexy.TodLib/TodCommon.h"
#include "../../SexyAppFramework/Debug.h"
#include "../../Sexy.TodLib/TodStringFile.h"
#include "../../SexyAppFramework/WidgetManager.h"
#include "../../SexyAppFramework/Slider.h"
#include "../../GameConstants.h"

const Rect cChallengeRect = Rect(0, 91 + BOARD_OFFSET_Y, BOARD_WIDTH, 480);
const int cButtonHeight = 118;

ChallengeDefinition gChallengeDefs[NUM_CHALLENGE_MODES] = {
	{ GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_1,              0,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    0,  0,  _S("[SURVIVAL_DAY_NORMAL]") },
	{ GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_2,              1,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    0,  1,  _S("[SURVIVAL_NIGHT_NORMAL]") },
	{ GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_3,              2,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    0,  2,  _S("[SURVIVAL_POOL_NORMAL]") },
	{ GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_4,              3,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    0,  3,  _S("[SURVIVAL_FOG_NORMAL]") },
	{ GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_5,              4,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    0,  4,  _S("[SURVIVAL_ROOF_NORMAL]") },
	{ GameMode::GAMEMODE_SURVIVAL_HARD_STAGE_1,                5,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    1,  0,  _S("[SURVIVAL_DAY_HARD]") },
	{ GameMode::GAMEMODE_SURVIVAL_HARD_STAGE_2,                6,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    1,  1,  _S("[SURVIVAL_NIGHT_HARD]") },
	{ GameMode::GAMEMODE_SURVIVAL_HARD_STAGE_3,                7,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    1,  2,  _S("[SURVIVAL_POOL_HARD]") },
	{ GameMode::GAMEMODE_SURVIVAL_HARD_STAGE_4,                8,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    1,  3,  _S("[SURVIVAL_FOG_HARD]") },
	{ GameMode::GAMEMODE_SURVIVAL_HARD_STAGE_5,                9,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    1,  4,  _S("[SURVIVAL_ROOF_HARD]") },
	{ GameMode::GAMEMODE_SURVIVAL_ENDLESS_STAGE_1,             10,  ChallengePage::CHALLENGE_PAGE_LIMBO,       3,  0,  _S("[SURVIVAL_DAY_ENDLESS]") },
	{ GameMode::GAMEMODE_SURVIVAL_ENDLESS_STAGE_2,             10,  ChallengePage::CHALLENGE_PAGE_LIMBO,       3,  1,  _S("[SURVIVAL_NIGHT_ENDLESS]") },
	{ GameMode::GAMEMODE_SURVIVAL_ENDLESS_STAGE_3,             10,  ChallengePage::CHALLENGE_PAGE_SURVIVAL,    2,  2,  _S("[SURVIVAL_POOL_ENDLESS]") },
	{ GameMode::GAMEMODE_SURVIVAL_ENDLESS_STAGE_4,             10,  ChallengePage::CHALLENGE_PAGE_LIMBO,       3,  2,  _S("[SURVIVAL_FOG_ENDLESS]") },
	{ GameMode::GAMEMODE_SURVIVAL_ENDLESS_STAGE_5,             10,  ChallengePage::CHALLENGE_PAGE_LIMBO,       3,  3,  _S("[SURVIVAL_ROOF_ENDLESS]") },
	{ GameMode::GAMEMODE_CHALLENGE_WAR_AND_PEAS,               0,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   0,  0,  _S("[WAR_AND_PEAS]") },
	{ GameMode::GAMEMODE_CHALLENGE_WALLNUT_BOWLING,            6,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   0,  1,  _S("[WALL_NUT_BOWLING]") },
	{ GameMode::GAMEMODE_CHALLENGE_SLOT_MACHINE,               2,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   0,  2,  _S("[SLOT_MACHINE]") },
	{ GameMode::GAMEMODE_CHALLENGE_RAINING_SEEDS,              3,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   0,  3,  _S("[ITS_RAINING_SEEDS]") },
	{ GameMode::GAMEMODE_CHALLENGE_BEGHOULED,                  1,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   0,  4,  _S("[BEGHOULED]") },
	{ GameMode::GAMEMODE_CHALLENGE_INVISIGHOUL,                8,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   1,  0,  _S("[INVISIGHOUL]") },
	{ GameMode::GAMEMODE_CHALLENGE_SEEING_STARS,               5,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   1,  1,  _S("[SEEING_STARS]") },
	{ GameMode::GAMEMODE_CHALLENGE_ZOMBIQUARIUM,               7,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   1,  2,  _S("[ZOMBIQUARIUM]") },
	{ GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST,            20,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   1,  3,  _S("[BEGHOULED_TWIST]") },
	{ GameMode::GAMEMODE_CHALLENGE_LITTLE_TROUBLE,             12,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   1,  4,  _S("[LITTLE_TROUBLE]") },
	{ GameMode::GAMEMODE_CHALLENGE_PORTAL_COMBAT,              15,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   2,  0,  _S("[PORTAL_COMBAT]") },
	{ GameMode::GAMEMODE_CHALLENGE_COLUMN,                     4,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   2,  1,  _S("[COLUMN_AS_YOU_SEE_EM]") },
	{ GameMode::GAMEMODE_CHALLENGE_BOBSLED_BONANZA,            17,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   2,  2,  _S("[BOBSLED_BONANZA]") },
	{ GameMode::GAMEMODE_CHALLENGE_SPEED,                      18,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   2,  3,  _S("[ZOMBIES_ON_SPEED]") },
	{ GameMode::GAMEMODE_CHALLENGE_WHACK_A_ZOMBIE,             16,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   2,  4,  _S("[WHACK_A_ZOMBIE]") },
	{ GameMode::GAMEMODE_CHALLENGE_LAST_STAND,                 21,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   3,  0,  _S("[LAST_STAND]") },
	{ GameMode::GAMEMODE_CHALLENGE_WAR_AND_PEAS_2,             0,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   3,  1,  _S("[WAR_AND_PEAS_2]") },
	{ GameMode::GAMEMODE_CHALLENGE_WALLNUT_BOWLING_2,          6,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   3,  2,  _S("[WALL_NUT_BOWLING_EXTREME]") },
	{ GameMode::GAMEMODE_CHALLENGE_POGO_PARTY,                 14,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   3,  3,  _S("[POGO_PARTY]") },
	{ GameMode::GAMEMODE_CHALLENGE_FINAL_BOSS,                 19,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   3,  4,  _S("[FINAL_BOSS]") },
	{ GameMode::GAMEMODE_CHALLENGE_ART_CHALLENGE_WALLNUT,      0,   ChallengePage::CHALLENGE_PAGE_LIMBO,       0,  0,  _S("[ART_CHALLENGE_WALL_NUT]") },
	{ GameMode::GAMEMODE_CHALLENGE_SUNNY_DAY,                  1,   ChallengePage::CHALLENGE_PAGE_LIMBO,       0,  1,  _S("[SUNNY_DAY]") },
	{ GameMode::GAMEMODE_CHALLENGE_RESODDED,                   2,   ChallengePage::CHALLENGE_PAGE_LIMBO,       0,  2,  _S("[UNSODDED]") },
	{ GameMode::GAMEMODE_CHALLENGE_BIG_TIME,                   3,   ChallengePage::CHALLENGE_PAGE_LIMBO,       0,  3,  _S("[BIG_TIME]") },
	{ GameMode::GAMEMODE_CHALLENGE_ART_CHALLENGE_SUNFLOWER,    4,   ChallengePage::CHALLENGE_PAGE_LIMBO,       0,  4,  _S("[ART_CHALLENGE_SUNFLOWER]") },
	{ GameMode::GAMEMODE_CHALLENGE_AIR_RAID,                   5,   ChallengePage::CHALLENGE_PAGE_LIMBO,       1,  0,  _S("[AIR_RAID]") },
	{ GameMode::GAMEMODE_CHALLENGE_ICE,                        6,   ChallengePage::CHALLENGE_PAGE_LIMBO,       1,  1,  _S("[ICE_LEVEL]") },
	{ GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN,                 7,   ChallengePage::CHALLENGE_PAGE_LIMBO,       1,  2,  _S("[ZEN_GARDEN]") },
	{ GameMode::GAMEMODE_CHALLENGE_HIGH_GRAVITY,               8,   ChallengePage::CHALLENGE_PAGE_LIMBO,       1,  3,  _S("[HIGH_GRAVITY]") },
	{ GameMode::GAMEMODE_CHALLENGE_GRAVE_DANGER,               11,  ChallengePage::CHALLENGE_PAGE_LIMBO,       1,  4,  _S("[GRAVE_DANGER]") },
	{ GameMode::GAMEMODE_CHALLENGE_SHOVEL,                     10,  ChallengePage::CHALLENGE_PAGE_LIMBO,       2,  0,  _S("[CAN_YOU_DIG_IT]") },
	{ GameMode::GAMEMODE_CHALLENGE_STORMY_NIGHT,               13,  ChallengePage::CHALLENGE_PAGE_LIMBO,       2,  1,  _S("[DARK_STORMY_NIGHT]") },
	{ GameMode::GAMEMODE_CHALLENGE_BUNGEE_BLITZ,               9,   ChallengePage::CHALLENGE_PAGE_LIMBO,       2,  2,  _S("[BUNGEE_BLITZ]") },
	{ GameMode::GAMEMODE_CHALLENGE_SQUIRREL,                   10,  ChallengePage::CHALLENGE_PAGE_LIMBO,       2,  3,  _S("Squirrel") },
	{ GameMode::GAMEMODE_TREE_OF_WISDOM,                       10,  ChallengePage::CHALLENGE_PAGE_LIMBO,       2,  4,  _S("Tree Of Wisdom") },
	{ GameMode::GAMEMODE_SCARY_POTTER_1,                       10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      0,  0,  _S("[SCARY_POTTER_1]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_2,                       10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      0,  1,  _S("[SCARY_POTTER_2]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_3,                       10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      0,  2,  _S("[SCARY_POTTER_3]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_4,                       10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      0,  3,  _S("[SCARY_POTTER_4]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_5,                       10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      0,  4,  _S("[SCARY_POTTER_5]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_6,                       10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      1,  0,  _S("[SCARY_POTTER_6]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_7,                       10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      1,  1,  _S("[SCARY_POTTER_7]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_8,                       10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      1,  2,  _S("[SCARY_POTTER_8]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_9,                       10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      1,  3,  _S("[SCARY_POTTER_9]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_ENDLESS,                 10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      1,  4,  _S("[SCARY_POTTER_ENDLESS]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_1,                    11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      2,  0,  _S("[I_ZOMBIE_1]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_2,                    11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      2,  1,  _S("[I_ZOMBIE_2]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_3,                    11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      2,  2,  _S("[I_ZOMBIE_3]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_4,                    11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      2,  3,  _S("[I_ZOMBIE_4]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_5,                    11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      2,  4,  _S("[I_ZOMBIE_5]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_6,                    11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      3,  0,  _S("[I_ZOMBIE_6]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_7,                    11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      3,  1,  _S("[I_ZOMBIE_7]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_8,                    11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      3,  2,  _S("[I_ZOMBIE_8]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_9,                    11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      3,  3,  _S("[I_ZOMBIE_9]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS,              11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      3,  4,  _S("[I_ZOMBIE_ENDLESS]") },
	{ GameMode::GAMEMODE_UPSELL,                               10,  ChallengePage::CHALLENGE_PAGE_LIMBO,       3,  4,  _S("Upsell") },
	{ GameMode::GAMEMODE_INTRO,                                10,  ChallengePage::CHALLENGE_PAGE_LIMBO,       2,  3,  _S("Intro") }
};

ChallengeScreen::ChallengeScreen(LawnApp* theApp, ChallengePage thePage)
{
	mLockShakeX = 0;
	mLockShakeY = 0;
	mScrollAmount = 0;
	mScrollPosition = 0;
	mMaxScrollPosition = 0;

	mPageIndex = thePage;
	mApp = theApp;
	mClip = false;
	mCheatEnableChallenges = false;
	mUnlockState = UNLOCK_OFF;
	mUnlockChallengeIndex = -1;
	mUnlockStateCounter = 0;
	TodLoadResources("DelayLoad_ChallengeScreen");

	mBackButton = MakeNewButton(ChallengeScreen::ChallengeScreen_Back, this, _S("[BACK_TO_MENU]"), nullptr, Sexy::IMAGE_SEEDCHOOSER_BUTTON2, 
		Sexy::IMAGE_SEEDCHOOSER_BUTTON2_GLOW, Sexy::IMAGE_SEEDCHOOSER_BUTTON2_GLOW);
	mBackButton->mTextDownOffsetX = 1;
	mBackButton->mTextDownOffsetY = 1;
	mBackButton->mColors[ButtonWidget::COLOR_LABEL] = Color(42, 42, 90);
	mBackButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color(42, 42, 90);
	mBackButton->Resize(18 + BOARD_OFFSET_X, 568 + BOARD_OFFSET_Y, 111, 26);

	mChallengesButton = MakeNewButton(ChallengeScreen::ChallengeScreen_Selector, this, _S("Page Selection"), nullptr, Sexy::IMAGE_SEEDCHOOSER_BUTTON2,
		Sexy::IMAGE_SEEDCHOOSER_BUTTON2_GLOW, Sexy::IMAGE_SEEDCHOOSER_BUTTON2_GLOW);
	mChallengesButton->mTextDownOffsetX = 1;
	mChallengesButton->mTextDownOffsetY = 1;
	mChallengesButton->mColors[ButtonWidget::COLOR_LABEL] = Color(42, 42, 90);
	mChallengesButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color(42, 42, 90);
	int aWidth = 111;
	mChallengesButton->Resize(618 + BOARD_OFFSET_X + (aWidth / 2), 568 + BOARD_OFFSET_Y, aWidth, 26);

	for (int aChallengeMode = 0; aChallengeMode < NUM_CHALLENGE_MODES; aChallengeMode++)
	{
		ChallengeDefinition& aChlDef = GetChallengeDefinition(aChallengeMode);
		ButtonWidget* aChallengeButton = new ButtonWidget(ChallengeScreen::ChallengeScreen_Mode + aChallengeMode, this);
		mChallengeButtons[aChallengeMode] = aChallengeButton;
		aChallengeButton->mDoFinger = true;
		aChallengeButton->mFrameNoDraw = true;
		if (aChlDef.mPage == CHALLENGE_PAGE_CHALLENGE || aChlDef.mPage == CHALLENGE_PAGE_LIMBO || aChlDef.mPage == CHALLENGE_PAGE_PUZZLE)
			aChallengeButton->Resize(38 + aChlDef.mCol * 155 + BOARD_OFFSET_X, 93 + aChlDef.mRow * 119 + BOARD_OFFSET_Y, 104, 115);
		else
			aChallengeButton->Resize(38 + aChlDef.mCol * 155 + BOARD_OFFSET_X, 125 + aChlDef.mRow * 145 + BOARD_OFFSET_Y, 104, 115);
		if (MoreTrophiesNeeded(aChallengeMode))
		{
			aChallengeButton->mDoFinger = false;
			aChallengeButton->mDisabled = true;
		}
	}

	mToolTip = new ToolTipWidget();
	mToolTip->mCenter = true;
	mToolTip->mVisible = false;
	UpdateButtons();
	
	if (mApp->mGameMode != GAMEMODE_UPSELL || mApp->mGameScene != SCENE_LEVEL_INTRO)
		mApp->mMusic->MakeSureMusicIsPlaying(MUSIC_TUNE_CHOOSE_YOUR_SEEDS);

	bool aIsIZombie = false;
	if (mPageIndex == CHALLENGE_PAGE_SURVIVAL && mApp->mPlayerInfo->mHasNewSurvival)
	{
		SetUnlockChallengeIndex(mPageIndex, false);
		mApp->mPlayerInfo->mHasNewSurvival = false;
	}
	else if (mPageIndex == CHALLENGE_PAGE_CHALLENGE && mApp->mPlayerInfo->mHasNewMiniGame)
	{
		SetUnlockChallengeIndex(mPageIndex, false);
		mApp->mPlayerInfo->mHasNewMiniGame = false;
	}
	else if (mPageIndex == CHALLENGE_PAGE_PUZZLE)
	{
		if (mApp->mPlayerInfo->mHasNewScaryPotter)
		{
			SetUnlockChallengeIndex(mPageIndex, false);
			mApp->mPlayerInfo->mHasNewScaryPotter = false;
		}
		else if (mApp->mPlayerInfo->mHasNewIZombie)
		{
			SetUnlockChallengeIndex(mPageIndex, true);
			mApp->mPlayerInfo->mHasNewIZombie = false;
		}
	}

	mSlider = new Slider(IMAGE_OPTIONS_SLIDERSLOT_PLANT, IMAGE_OPTIONS_SLIDERKNOB_PLANT, 0, this);
	mSlider->SetValue(max(0.0, min(mMaxScrollPosition, mScrollPosition)));
	mSlider->mHorizontal = false;
	mSlider->Resize(775 + BOARD_ADDITIONAL_WIDTH, cChallengeRect.mY, 20, cChallengeRect.mHeight);
	mSlider->mThumbOffsetX = -5;

	mApp->mDetails = "In the Challenge Screen";
}

void ChallengeScreen::SliderVal(int theId, double theVal)
{
	switch (theId)
	{
	case 0:
		mScrollPosition = theVal * mMaxScrollPosition;
		break;
	}
}

ChallengeScreen::~ChallengeScreen()
{
	delete mBackButton;
	delete mChallengesButton;
	for (ButtonWidget* aChallengeButton : mChallengeButtons) delete aChallengeButton;
	delete mToolTip;
	delete mSlider;
	mApp->UpdateDiscordState();
}

ChallengeDefinition& GetChallengeDefinition(int theChallengeMode)
{
	TOD_ASSERT(theChallengeMode >= 0 && theChallengeMode < NUM_CHALLENGE_MODES);

	ChallengeDefinition& aDef = gChallengeDefs[theChallengeMode];
	TOD_ASSERT(aDef.mChallengeMode == theChallengeMode + GAMEMODE_SURVIVAL_NORMAL_STAGE_1);

	return gChallengeDefs[theChallengeMode];
}

bool ChallengeScreen::IsScaryPotterLevel(GameMode theGameMode)
{
	return theGameMode >= GAMEMODE_SCARY_POTTER_1 && theGameMode <= GAMEMODE_SCARY_POTTER_ENDLESS;
}

bool ChallengeScreen::IsIZombieLevel(GameMode theGameMode)
{
	return theGameMode >= GAMEMODE_PUZZLE_I_ZOMBIE_1 && theGameMode <= GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS;
}

void ChallengeScreen::SetUnlockChallengeIndex(ChallengePage thePage, bool theIsIZombie)
{
	mUnlockState = UNLOCK_SHAKING;
	mUnlockStateCounter = 100;
	mUnlockChallengeIndex = 0;
	for (int aChallengeMode = 0; aChallengeMode < NUM_CHALLENGE_MODES; aChallengeMode++)
	{
		ChallengeDefinition& aDef = GetChallengeDefinition(aChallengeMode);
		if (aDef.mPage == thePage)
		{
			if (thePage != CHALLENGE_PAGE_PUZZLE || (!theIsIZombie && IsScaryPotterLevel(aDef.mChallengeMode)) || (theIsIZombie && IsIZombieLevel(aDef.mChallengeMode)))
			{
				if (AccomplishmentsNeeded(aChallengeMode) <= 0)
				{
					mUnlockChallengeIndex = aChallengeMode;
				}
			}
		}
	}
}

int ChallengeScreen::MoreTrophiesNeeded(int theChallengeIndex)
{
	ChallengeDefinition& aDef = GetChallengeDefinition(theChallengeIndex);
	if (mApp->mGameMode == GAMEMODE_UPSELL && mApp->mGameScene == SCENE_LEVEL_INTRO)
	{
		return aDef.mChallengeMode == GAMEMODE_CHALLENGE_FINAL_BOSS ? 1 : 0;
	}
	
	if (mApp->IsTrialStageLocked())
	{
		if (mPageIndex == CHALLENGE_PAGE_PUZZLE && aDef.mChallengeMode >= GAMEMODE_SCARY_POTTER_4)
		{
			return aDef.mChallengeMode == GAMEMODE_SCARY_POTTER_4 ? 1 : 2;
		}
		else if (mPageIndex == CHALLENGE_PAGE_CHALLENGE && aDef.mChallengeMode >= GAMEMODE_CHALLENGE_RAINING_SEEDS)
		{
			return aDef.mChallengeMode == GAMEMODE_CHALLENGE_RAINING_SEEDS ? 1 : 2;
		}
		else if (mPageIndex == CHALLENGE_PAGE_SURVIVAL && aDef.mChallengeMode >= GAMEMODE_SURVIVAL_NORMAL_STAGE_4)
		{
			return aDef.mChallengeMode == GAMEMODE_SURVIVAL_NORMAL_STAGE_4 ? 1 : 2;
		}
	}

	if (aDef.mPage == CHALLENGE_PAGE_PUZZLE)
	{
		if (IsScaryPotterLevel(aDef.mChallengeMode))
		{
			int aLevelsCompleted = 0;
			for (ChallengeDefinition& aSPDef : gChallengeDefs)
			{
				if (IsScaryPotterLevel(aSPDef.mChallengeMode) && mApp->HasBeatenChallenge(aSPDef.mChallengeMode))
				{
					aLevelsCompleted++;
				}
			}

			if (aDef.mChallengeMode < GAMEMODE_SCARY_POTTER_4 || mApp->HasFinishedAdventure() || aLevelsCompleted < 3)
			{
				return ClampInt(aDef.mChallengeMode - GAMEMODE_SCARY_POTTER_1 - aLevelsCompleted, 0, 9);
			}
			else
			{
				return aDef.mChallengeMode == GAMEMODE_SCARY_POTTER_4 ? 1 : 2;
			}
		}
		else if (IsIZombieLevel(aDef.mChallengeMode))
		{
			int aLevelsCompleted = 0;
			for (ChallengeDefinition& aIZDef : gChallengeDefs)
			{
				if (IsIZombieLevel(aIZDef.mChallengeMode) && mApp->HasBeatenChallenge(aIZDef.mChallengeMode))
				{
					aLevelsCompleted++;
				}
			}

			if (aDef.mChallengeMode < GAMEMODE_PUZZLE_I_ZOMBIE_4 || mApp->HasFinishedAdventure() || aLevelsCompleted < 3)
			{
				return ClampInt(aDef.mChallengeMode - GAMEMODE_PUZZLE_I_ZOMBIE_1 - aLevelsCompleted, 0, 9);
			}
			else
			{
				return aDef.mChallengeMode == GAMEMODE_PUZZLE_I_ZOMBIE_4 ? 1 : 2;
			}
		}
	}
	else
	{
		int aIdxInPage = aDef.mRow * 5 + aDef.mCol;
		if ((aDef.mPage == CHALLENGE_PAGE_CHALLENGE || aDef.mPage == CHALLENGE_PAGE_SURVIVAL) && !mApp->HasFinishedAdventure())
		{
			return aIdxInPage < 3 ? 0 : aIdxInPage == 3 ? 1 : 2;
		}
		else
		{
			int aNumTrophies = mApp->GetNumTrophies(aDef.mPage);
			if (aDef.mPage == CHALLENGE_PAGE_LIMBO)
			{
				return 0;
			}
			if (mApp->IsSurvivalEndless(aDef.mChallengeMode))
			{
				return 10 - aNumTrophies;
			}
			if (aDef.mPage == CHALLENGE_PAGE_SURVIVAL || aDef.mPage == CHALLENGE_PAGE_CHALLENGE)
			{
				aNumTrophies += 3;
			}
			else
			{
				TOD_ASSERT();
			}

			return aIdxInPage >= aNumTrophies ? aIdxInPage - aNumTrophies + 1 : 0;
		}
	}
}

bool ChallengeScreen::ShowPageButtons()
{
	return mApp->mTodCheatKeys && mPageIndex != CHALLENGE_PAGE_SURVIVAL && mPageIndex != CHALLENGE_PAGE_PUZZLE;
}

void ChallengeScreen::UpdateButtons()
{
	for (int aChallengeMode = 0; aChallengeMode < NUM_CHALLENGE_MODES; aChallengeMode++)
		mChallengeButtons[aChallengeMode]->mVisible = GetChallengeDefinition(aChallengeMode).mPage == mPageIndex;
}

int ChallengeScreen::AccomplishmentsNeeded(int theChallengeIndex)
{
	int aTrophiesNeeded = MoreTrophiesNeeded(theChallengeIndex);
	GameMode aGameMode = GetChallengeDefinition(theChallengeIndex).mChallengeMode;
	if (mApp->IsSurvivalEndless(aGameMode) && aTrophiesNeeded <= 3 && mApp->GetNumTrophies(CHALLENGE_PAGE_SURVIVAL) < 10 &&
		mApp->HasFinishedAdventure() && !mApp->IsTrialStageLocked()) aTrophiesNeeded = 1;
	return mCheatEnableChallenges ? 0 : aTrophiesNeeded;
}

void ChallengeScreen::DrawButton(Graphics* g, int theChallengeIndex)
{
	ButtonWidget* aChallengeButton = mChallengeButtons[theChallengeIndex];
	if (aChallengeButton->mVisible)
	{
		aChallengeButton->mMouseVisible = cChallengeRect.Contains(mWidgetManager->mLastMouseX, mWidgetManager->mLastMouseY);
		ChallengeDefinition& aDef = GetChallengeDefinition(theChallengeIndex);
		aChallengeButton->mX = 38 + aDef.mCol * 155 + BOARD_ADDITIONAL_WIDTH;
		mButtonStartYOffset = cChallengeRect.mY + (aDef.mPage == CHALLENGE_PAGE_SURVIVAL ? 34 : 2);
		mButtonYOffset = cButtonHeight + (aDef.mPage == CHALLENGE_PAGE_SURVIVAL ? 30 : 2);
		aChallengeButton->mY = mButtonStartYOffset + aDef.mRow * mButtonYOffset - mScrollPosition;
		int aPosX = aChallengeButton->mX;
		int aPosY = aChallengeButton->mY;
		if (aChallengeButton->mIsDown)
		{
			aPosX++;
			aPosY++;
		}

		if (AccomplishmentsNeeded(theChallengeIndex) <= 1)
		{
			if (aChallengeButton->mDisabled)
			{
				g->SetColor(Color(92, 92, 92));
				g->SetColorizeImages(true);
			}
			if (theChallengeIndex == mUnlockChallengeIndex)
			{
				if (mUnlockState == UNLOCK_SHAKING)
				{
					g->SetColor(Color(92, 92, 92));
				}
				else if (mUnlockState == UNLOCK_FADING)
				{
					int aColor = TodAnimateCurve(50, 25, mUnlockStateCounter, 92, 255, CURVE_LINEAR);
					g->SetColor(Color(aColor, aColor, aColor));
				}
				g->SetColorizeImages(true);
			}
			g->SetClipRect(cChallengeRect);
			g->SetScale(0.5f, 0.5f, aPosX + 13, aPosY + 4);
			if (mPageIndex == CHALLENGE_PAGE_SURVIVAL)
			{
				g->DrawImageCel(Sexy::IMAGE_SURVIVAL_THUMBNAILS, aPosX + 13, aPosY + 4, aDef.mChallengeIconIndex);
			}
			else
			{
				g->DrawImageCel(Sexy::IMAGE_CHALLENGE_THUMBNAILS, aPosX + 13, aPosY + 4, aDef.mChallengeIconIndex);
			}
			g->SetScale(1.0f, 1.0f, aPosX + 13, aPosY + 4);

			bool aHighLight = aChallengeButton->mIsOver && theChallengeIndex != mUnlockChallengeIndex;
			g->SetColorizeImages(false);
			g->DrawImage(aHighLight ? Sexy::IMAGE_CHALLENGE_WINDOW : Sexy::IMAGE_CHALLENGE_WINDOW_HIGHLIGHT, aPosX - 6, aPosY - 2);

			Color aTextColor = aHighLight ? Color(250, 40, 40) : Color(42, 42, 90);
			SexyString aName = TodStringTranslate(aDef.mChallengeName);
			if (aChallengeButton->mDisabled || (theChallengeIndex == mUnlockChallengeIndex && mUnlockState == UNLOCK_SHAKING))
			{
				aName = _S("?");
			}

			int aNameLen = aName.size();
			TodDrawStringWrapped(g, aName, Rect(aPosX + 6, aPosY + 74, 94, 33), Sexy::FONT_BRIANNETOD12, aTextColor, DS_ALIGN_CENTER_VERTICAL_MIDDLE);

			int aRecord = mApp->mPlayerInfo->mChallengeRecords[theChallengeIndex];
			if (theChallengeIndex == mUnlockChallengeIndex)
			{
				Image* aLockImage = Sexy::IMAGE_LOCK;
				if (mUnlockState == UNLOCK_FADING)
				{
					aLockImage = Sexy::IMAGE_LOCK_OPEN;
					g->SetColor(Color(255, 255, 255, TodAnimateCurve(25, 0, mUnlockStateCounter, 255, 0, CURVE_LINEAR)));
					g->SetColorizeImages(true);
				}
				TodDrawImageScaledF(g, aLockImage, aPosX + 24 + mLockShakeX, aPosY + 9 + mLockShakeY, 0.7f, 0.7f);
				g->SetColorizeImages(false);
			}
			else if (aRecord > 0)
			{
				if (mApp->HasBeatenChallenge(aDef.mChallengeMode))
				{
					g->DrawImage(Sexy::IMAGE_MINIGAME_TROPHY, aPosX - 6, aPosY - 2);
				}
				else if (mApp->IsEndlessScaryPotter(aDef.mChallengeMode) || mApp->IsEndlessIZombie(aDef.mChallengeMode))
				{
					SexyString aAchievement = mApp->Pluralize(aRecord, _S("[ONE_FLAG]"), _S("[COUNT_FLAGS]"));
					TodDrawString(g, aAchievement, aPosX + 48, aPosY + 48, Sexy::FONT_CONTINUUMBOLD14OUTLINE, Color::White, DS_ALIGN_CENTER);
					TodDrawString(g, aAchievement, aPosX + 48, aPosY + 48, Sexy::FONT_CONTINUUMBOLD14, Color(255, 0, 0), DS_ALIGN_CENTER);
				}
				else if (mApp->IsSurvivalEndless(aDef.mChallengeMode))
				{
					SexyString aAchievement = TodReplaceNumberString(_S("[LONGEST_STREAK]"), _S("{STREAK}"), aRecord);
					Rect aRect(aPosX, aPosY + 15, 96, 200);
					TodDrawStringWrapped(g, aAchievement, aRect, Sexy::FONT_CONTINUUMBOLD14OUTLINE, Color::White, DS_ALIGN_CENTER);
					TodDrawStringWrapped(g, aAchievement, aRect, Sexy::FONT_CONTINUUMBOLD14, Color(255, 0, 0), DS_ALIGN_CENTER);
				}
			}
			else if (aChallengeButton->mDisabled)
			{
				TodDrawImageScaledF(g, Sexy::IMAGE_LOCK, aPosX + 24, aPosY + 9, 0.7f, 0.7f);
			}
		}
		else
		{
			g->DrawImage(Sexy::IMAGE_CHALLENGE_BLANK, aPosX, aPosY);
		}
	}
}

void ChallengeScreen::Draw(Graphics* g)
{
	g->SetLinearBlend(true);
	g->DrawImage(Sexy::IMAGE_CHALLENGE_BACKGROUND, 0, 0);

	TodDrawString(g, GetPageTitle(mPageIndex), 400 + BOARD_OFFSET_X, 58 + BOARD_OFFSET_Y, Sexy::FONT_HOUSEOFTERROR28, Color(220, 220, 220), DS_ALIGN_CENTER);

	int aTrophiesGot = mApp->GetNumTrophies(mPageIndex);
	int aTrophiesTotal = mApp->GetTotalTrophies(mPageIndex);
	TodDrawString(g, aTrophiesTotal > 0 ? StrFormat(_S("%d/%d"), aTrophiesGot, aTrophiesTotal) : "None", 739 + BOARD_ADDITIONAL_WIDTH, 73 + BOARD_OFFSET_Y, Sexy::FONT_DWARVENTODCRAFT12, Color(255, 240, 0), DS_ALIGN_CENTER);
	TodDrawImageScaledF(g, Sexy::IMAGE_TROPHY, 718 + BOARD_ADDITIONAL_WIDTH, 26 + BOARD_OFFSET_Y, 0.5f, 0.5f);

	for (int aChallengeMode = 0; aChallengeMode < NUM_CHALLENGE_MODES; aChallengeMode++)
		DrawButton(g, aChallengeMode);


	int aHighestRow = 0;
	for (int aChallengeMode = 0; aChallengeMode < NUM_CHALLENGE_MODES; aChallengeMode++)
	{
		DrawButton(g, aChallengeMode);
		ChallengeDefinition& aDef = GetChallengeDefinition(aChallengeMode);
		if (aDef.mRow >= aHighestRow && aDef.mPage == mPageIndex)
			aHighestRow = aDef.mRow;
	}
	mMaxScrollPosition = max(0, (aHighestRow * mButtonYOffset) + cButtonHeight + (mButtonStartYOffset - cChallengeRect.mY) - cChallengeRect.mHeight);


	mToolTip->Draw(g);
}

void ChallengeScreen::Update()
{
	Widget::Update();
	UpdateToolTip();
	mApp->UpdateDiscordState(TodStringTranslate(GetPageTitle(mPageIndex)));
	mScrollPosition = ClampFloat(mScrollPosition += mScrollAmount * (mBaseScrollSpeed + abs(mScrollAmount) * mScrollAccel), 0, mMaxScrollPosition);
	mScrollAmount *= (1.0f - mScrollAccel);
	mSlider->SetValue(max(0.0, min(mMaxScrollPosition, mScrollPosition)) / mMaxScrollPosition);
	mSlider->mVisible = mMaxScrollPosition != 0;

	if (mUnlockStateCounter > 0) mUnlockStateCounter--;
	if (mUnlockState == UNLOCK_SHAKING)
	{
		if (mUnlockStateCounter == 0)
		{
			mApp->PlayFoley(FOLEY_PAPER);
			mUnlockState = UNLOCK_FADING;
			mUnlockStateCounter = 50;
			mLockShakeX = 0;
			mLockShakeY = 0;
		}
		else
		{
			mLockShakeX = RandRangeFloat(-2, 2);
			mLockShakeY = RandRangeFloat(-2, 2);
		}
	}
	else if (mUnlockState == UNLOCK_FADING && mUnlockStateCounter == 0)
	{
		mUnlockState = UNLOCK_OFF;
		mUnlockStateCounter = 0;
		mUnlockChallengeIndex = -1;
	}

	MarkDirty();
}

void ChallengeScreen::MouseWheel(int theDelta)
{
	mScrollAmount -= mBaseScrollSpeed * theDelta;
	mScrollAmount -= mScrollAmount * mScrollAccel;
}

SexyString ChallengeScreen::GetPageTitle(ChallengePage thePage)
{
	SexyString aTitle = "Unknown Page";
	switch (thePage)
	{
		case ChallengePage::CHALLENGE_PAGE_CHALLENGE:
			aTitle = _S("[PICK_CHALLENGE]");
		break;
		case ChallengePage::CHALLENGE_PAGE_PUZZLE:
			aTitle = _S("[SCARY_POTTER]");
			break;
		case ChallengePage::CHALLENGE_PAGE_SURVIVAL:
			aTitle = _S("[PICK_AREA]");
		break;		
		case ChallengePage::CHALLENGE_PAGE_LIMBO:
			aTitle = _S("Limbo Page");
		break;
	}
	return aTitle;
}

bool ChallengeScreen::IsPageUnlocked(ChallengePage thePage)
{
	switch (thePage)
	{
		case ChallengePage::CHALLENGE_PAGE_CHALLENGE:
			return mApp->HasFinishedAdventure() || mApp->mPlayerInfo->mHasUnlockedMinigames;
		case ChallengePage::CHALLENGE_PAGE_PUZZLE:
			return mApp->HasFinishedAdventure() || mApp->mPlayerInfo->mHasUnlockedPuzzleMode;
		case ChallengePage::CHALLENGE_PAGE_SURVIVAL:
			return mApp->HasFinishedAdventure() || mApp->mPlayerInfo->mHasUnlockedSurvivalMode;
		case ChallengePage::CHALLENGE_PAGE_LIMBO:
			return mApp->HasFinishedAdventure();
	}
	return false;
}

void ChallengeScreen::AddedToManager(WidgetManager* theWidgetManager)
{
	Widget::AddedToManager(theWidgetManager);
	AddWidget(mBackButton);
	if (HAS_PAGE_SELECTOR)
		AddWidget(mChallengesButton);
	for (ButtonWidget* aButton : mChallengeButtons) AddWidget(aButton);
	AddWidget(mSlider);
}

void ChallengeScreen::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Widget::RemovedFromManager(theWidgetManager);
	RemoveWidget(mBackButton);
	if (HAS_PAGE_SELECTOR)
		RemoveWidget(mChallengesButton);
	for (ButtonWidget* aButton : mChallengeButtons) RemoveWidget(aButton);
	RemoveWidget(mSlider);
}

void ChallengeScreen::ButtonPress(int theId)
{
	mApp->PlaySample(Sexy::SOUND_BUTTONCLICK);
}

void ChallengeScreen::ButtonDepress(int theId)
{
	if (theId == ChallengeScreen::ChallengeScreen_Back)
	{
		mApp->KillChallengeScreen();
		mApp->DoBackToMain();
	}
	else if (theId == ChallengeScreen::ChallengeScreen_Selector)
	{
		mApp->DoChallengePagesDialog();
	}

	int aChallengeMode = theId - ChallengeScreen::ChallengeScreen_Mode;
	if (aChallengeMode >= 0 && aChallengeMode < NUM_CHALLENGE_MODES)
	{
		mApp->KillChallengeScreen();
		mApp->PreNewGame((GameMode)(aChallengeMode + 1), true);
	}
}

void ChallengeScreen::UpdateToolTip()
{
	if (!mApp->mWidgetManager->mMouseIn || !mApp->mActive)
	{
		mToolTip->mVisible = false;
		return;
	}

	for (int aChallengeMode = 0; aChallengeMode < NUM_CHALLENGE_MODES; aChallengeMode++)
	{
		ChallengeDefinition& aDef = GetChallengeDefinition(aChallengeMode);
		ButtonWidget* aChallengeButton = mChallengeButtons[aChallengeMode];
		if (aChallengeButton->mVisible && aChallengeButton->mDisabled &&
			aChallengeButton->Contains(mApp->mWidgetManager->mLastMouseX, mApp->mWidgetManager->mLastMouseY) &&
			AccomplishmentsNeeded(aChallengeMode) <= 1)
		{
			mToolTip->mX = aChallengeButton->mWidth / 2 + aChallengeButton->mX;
			mToolTip->mY = aChallengeButton->mY;
			if (MoreTrophiesNeeded(aChallengeMode) > 0)
			{
				SexyString aLabel;
				if (mPageIndex == CHALLENGE_PAGE_PUZZLE)
				{
					if (IsScaryPotterLevel(aDef.mChallengeMode))
					{
						if (!mApp->HasFinishedAdventure() && aDef.mChallengeMode == GAMEMODE_SCARY_POTTER_4)
						{
							aLabel = _S("[FINISH_ADVENTURE_TOOLTIP]");
						}
						else
						{
							aLabel = _S("[ONE_MORE_SCARY_POTTER_TOOLTIP]");
						}
					}
					else if (IsIZombieLevel(aDef.mChallengeMode))
					{
						if (!mApp->HasFinishedAdventure() && aDef.mChallengeMode == GAMEMODE_PUZZLE_I_ZOMBIE_4)
						{
							aLabel = _S("[FINISH_ADVENTURE_TOOLTIP]");
						}
						else
						{
							aLabel = _S("[ONE_MORE_IZOMBIE_TOOLTIP]");
						}
					}
				}
				else if (!mApp->HasFinishedAdventure() || mApp->IsTrialStageLocked())
				{
					aLabel = _S("[FINISH_ADVENTURE_TOOLTIP]");
				}
				else if (mApp->IsSurvivalEndless(aDef.mChallengeMode))
				{
					aLabel = _S("[10_SURVIVAL_TOOLTIP]");
				}
				else if (mPageIndex == CHALLENGE_PAGE_SURVIVAL)
				{
					aLabel = _S("[ONE_MORE_SURVIVAL_TOOLTIP]");
				}
				else if (mPageIndex == CHALLENGE_PAGE_CHALLENGE)
				{
					aLabel = _S("[ONE_MORE_CHALLENGE_TOOLTIP]");
				}
				else continue;

				mToolTip->SetLabel(aLabel);
				mToolTip->mVisible = true;
				return;
			} // end if (MoreTrophiesNeeded(aChallengeMode) > 0)
		} 
	}

	mToolTip->mVisible = false;
}