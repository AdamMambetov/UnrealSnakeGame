// Snake Game, Copyright Adam Mambetov. All Rights Reserved.

#include "Game.h"
#include "Grid.h"

DEFINE_LOG_CATEGORY_STATIC(LogGame, All, All);

using namespace Snake;

Game::Game(const Settings& settings)  //
    : c_settings(settings)
{
    m_grid = MakeShared<Grid>(settings.gridDims);
}