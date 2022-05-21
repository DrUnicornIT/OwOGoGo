//? Base main UI

#include "ui.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "audio.h"
#include "game.h"
#include "helper.h"
#include "map.h"
#include "render.h"
#include "res.h"
#include "storage.h"
#include "text.h"
#include "types.h"

extern LinkList animationsList[];
extern bool hasMap[MAP_SIZE][MAP_SIZE];
extern Text texts[TEXTSET_SIZE];
extern SDL_Renderer* renderer;
extern int renderFrames;
extern SDL_Color WHITE;
extern Texture textures[];
extern Effect effects[];
extern Weapon* weapons[WEAPONS_SIZE];
extern Texture textures[TEXTURES_SIZE];
extern LinkList animationsList[ANIMATION_LINK_LIST_NUM];

//--- Start Chose option ---//
int cursorPos;
bool moveCursor(int optsNum)
{
  SDL_Event e;
  bool quit = false;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      quit = true;
      cursorPos = optsNum;
      return quit;
    }
    else if (e.type == SDL_KEYDOWN)
    {
      int keyValue = e.key.keysym.sym;
      switch (keyValue)
      {
      case SDLK_UP:
        cursorPos--;
        playAudio(AUDIO_INTER1);
        break;
      case SDLK_DOWN:
        cursorPos++;
        playAudio(AUDIO_INTER1);
        break;
      case SDLK_RETURN:
        quit = true;
        break;
      case SDLK_ESCAPE:
        quit = true;
        cursorPos = optsNum;
        playAudio(AUDIO_BUTTON1);
        return quit;
        break;
      }
    }
  }
  cursorPos += optsNum;
  cursorPos %= optsNum;
  return quit;
}
int chooseOptions(int optionsNum, Text** options)
{
  cursorPos = 0;
  Snake* player = createSnake(2, 0, LOCAL);
  appendSpriteToSnake(player, SPRITE_KNIGHT, SCREEN_WIDTH / 2,
    SCREEN_HEIGHT / 2, UP);
  int lineGap = FONT_SIZE + FONT_SIZE / 2,
    totalHeight = lineGap * (optionsNum - 1);
  int startY = (SCREEN_HEIGHT - totalHeight) / 2;
  while (!moveCursor(optionsNum))
  {
    Sprite* sprite = (Sprite*)player->sprites->head->element;
    sprite->ani->at = AT_CENTER;
    sprite->x = SCREEN_WIDTH / 2 - options[cursorPos]->width / 2 - UNIT / 2;
    sprite->y = startY + cursorPos * lineGap;
    updateAnimationOfSprite(sprite);
    renderUi();
    for (int i = 0; i < optionsNum; i++)
    {
      renderCenteredText(options[i], SCREEN_WIDTH / 2, startY + i * lineGap, 1);
    }
    SDL_RenderPresent(renderer);
    renderFrames++;
  }
  playAudio(AUDIO_BUTTON1);
  destroySnake(player);
  destroyAnimationsByLinkList(&animationsList[RENDER_LIST_SPRITE_ID]);
  return cursorPos;
}

//--- End Chose option ---//

//-- Start Render UI ---//

void baseUi(int w, int h)
{
  initRenderer();
  initBlankMap(w, h);
  pushMapToRender();
}

//-- End Render UI ---//

//-- Start Play Game --//
bool chooseLevelUi()
{
  baseUi(30, 12);
  int optsNum = 3;
  Text** opts = (Text**)malloc(sizeof(Text*) * optsNum);
  for (int i = 0; i < optsNum; i++)
    opts[i] = texts + i + 5;
  int opt = chooseOptions(optsNum, opts);
  if (opt != optsNum)
    setLevel(opt);
  //! Cần chỉnh để game dễ chơi hơn
  clearRenderer();
  return opt != optsNum;
}

void launchLocalGame(int localPlayerNum)
{
  Score** scores = startGame(localPlayerNum, 0, true);
  rankListUi(localPlayerNum, scores);
  for (int i = 0; i < localPlayerNum; i++)
    updateLocalRanklist(scores[i]);
  destroyRanklist(localPlayerNum, scores);
}

//-- End Play Game --//

//-- Start HowToPlay --//
void helpHowtoPlayGameUi()
{
  baseUi(30, 12);
  playBgm(0);
  int optsNum = 5;
  Text** opts = (Text**)malloc(sizeof(Text*) * optsNum);
  for (int i = 0; i < optsNum; i++)
    opts[i] = texts + i + 8;
  int opt = chooseOptions(optsNum, opts);
  free(opts);

  clearRenderer();
}
//-- End HowToPlay --//

//-- Start RankList --//

void rankListUi(int count, Score** scores)
{
  baseUi(30, 12 + MAX(0, count - 4));
  playBgm(0);
  Text** opts = (Text**)malloc(sizeof(Text*) * count);
  char buf[1024];
  for (int i = 0; i < count; i++)
  {
    sprintf(buf, "Score: %-6.0lf Got: %-6d Kill: %-6d Damage: %-6d Stand: %-6d",
      scores[i]->rank, scores[i]->got, scores[i]->killed,
      scores[i]->damage, scores[i]->stand);
    opts[i] = createText(buf, WHITE);
  }

  chooseOptions(count, opts);

  for (int i = 0; i < count; i++)
    destroyText(opts[i]);
  free(opts);
  clearRenderer();
}


void localRankListUi()
{
  int count;
  Score** scores = readRanklist(STORAGE_PATH, &count);
  rankListUi(count, scores);
  destroyRanklist(count, scores);
}

//-- End RankList --//

//-- Start UI --//


int OptionIntroduce(int optionsNum, Text** options)
{
  cursorPos = 0;
  Snake* Snake[optionsNum];
  Texture weaponItem[optionsNum];

  Snake[0] = createSnake(2, 0, LOCAL);
  appendSpriteToSnake(Snake[0], SPRITE_KNIGHT, SCREEN_WIDTH / 2,
    SCREEN_HEIGHT / 2, UP);
  weaponItem[0] = textures[RES_HOLY_SWORD];

  Snake[1] = createSnake(2, 0, LOCAL);
  appendSpriteToSnake(Snake[1], SPRITE_ELF, SCREEN_WIDTH / 2,
    SCREEN_HEIGHT / 2, UP);
  weaponItem[1] = textures[RES_POWERFUL_BOW];

  Snake[2] = createSnake(2, 0, LOCAL);
  appendSpriteToSnake(Snake[2], SPRITE_WIZZARD, SCREEN_WIDTH / 2,
    SCREEN_HEIGHT / 2, UP);
  weaponItem[2] = textures[RES_FIREBALL];

  Snake[3] = createSnake(2, 0, LOCAL);
  appendSpriteToSnake(Snake[3], SPRITE_LIZARD, SCREEN_WIDTH / 2,
    SCREEN_HEIGHT / 2, UP);
  weaponItem[3] = textures[RES_CLAWFX];

  int lineGap = FONT_SIZE + FONT_SIZE / 2,
    totalHeight = lineGap * (optionsNum - 1);
  int startY = (SCREEN_HEIGHT - totalHeight) / 2;


  while (!moveCursor(optionsNum))
  {
    Sprite* sprite[optionsNum];
    for (int i = 0; i < optionsNum; i++) {
      sprite[i] = (Sprite*)Snake[i]->sprites->head->element;
      sprite[i]->ani->at = AT_CENTER;
      sprite[i]->x = SCREEN_WIDTH / 2 - options[i]->width / 2 - UNIT / 2;
      sprite[i]->y = startY + i * lineGap;
      Animation* ani = createAndPushAnimation(
        &animationsList[RENDER_LIST_EFFECT_ID], &weaponItem[i], NULL,
        LOOP_INFI, 3, sprite[i]->x + SCREEN_WIDTH / 2, sprite[i]->y + 100, SDL_FLIP_NONE, 0,
        AT_BOTTOM_CENTER);
      bindAnimationToSprite(ani, sprite[i], true);
      updateAnimationOfSprite(sprite[i]);
    }
    renderUi();
    for (int i = 0; i < optionsNum; i++)
    {
      renderCenteredText(options[i], SCREEN_WIDTH / 2, startY + i * lineGap, 1);
    }
    SDL_RenderPresent(renderer);
    renderFrames++;
  }
  playAudio(AUDIO_BUTTON1);
  for (int i = 0; i < optionsNum; i++) {
    destroySnake(Snake[i]);
  }
  destroyAnimationsByLinkList(&animationsList[RENDER_LIST_SPRITE_ID]);
  return cursorPos;
}


void Introduce() {
  baseUi(30, 12);
  
  playBgm(0);
  int optsNum = 4;
  Text** opts = (Text**)malloc(sizeof(Text*) * optsNum);
  for (int i = 0; i < optsNum; i++)
    opts[i] = texts + i + 13;
  int opt = OptionIntroduce(optsNum, opts);
  free(opts);

  clearRenderer();
}

void mainUi()
{
  baseUi(30, 12);
  playBgm(0);
  int optsNum = 5;
  Text** opts = (Text**)malloc(sizeof(Text*) * optsNum);
  for (int i = 0; i < optsNum; i++)
    opts[i] = texts + i;
  int opt = chooseOptions(optsNum, opts);
  free(opts);

  clearRenderer();
  switch (opt)
  {
  case 0:
    if (!chooseLevelUi())
      break;
    launchLocalGame(1);
    break;
  case 1:
    Introduce();
    break;
  case 2:
    helpHowtoPlayGameUi();
    break;
  case 3:
    localRankListUi();
    break;
  case 4:
    break;
  }
  if (opt == optsNum)
    return;
  if (opt != 4)
  {
    mainUi();
  }
}

//-- End UI --//
