//
//  Game.cpp
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//

#include "Game.h"

Game::~Game()
{
    // do cleanup first
    Exit();
    
    if ( gui )
        delete gui;
}

void Game::Init()
{
    activeEnts = new vector<Entity*>;
    
    // TMP DBG
    // Standard player
    player = new Character();
    
    player->baseSpecial.strength = 6;
    player->baseSpecial.perception = 8;
    player->baseSpecial.endurance = 6;
    player->baseSpecial.charisma = 4;
    player->baseSpecial.intelligence = 9;
    player->baseSpecial.agility = 10;
    player->baseSpecial.luck = 4;
    
    player->SetBaseStats();
    player->SetModdedStats();
    
    player->currAP = player->modAP;
    player->currHP = player->modHP-1;
    
    // Standard dungeon
    DungeonSpec spec;
    dungeon = new Dungeon(spec);
    
    dungeon->Dump("leveldump.txt");
    dungeon->DumpVisGroups("visdump.txt");
    dungeon->DumpEdgeMask("edgedump.txt");
    
    // Spawn player into dungeon near start
    veci loc = dungeon->GetPlayerSpawnCoords();
    player->location = loc;
    
    // Add player to ents
    activeEnts->push_back(player);
    
    // Init visibility for this player and current dungeon
    player->visInfo = new Visibility(dungeon,player);
    player->visInfo->ClearVis();
    player->visInfo->UpdateVis();
    
    // END TMP
    
    // Load item prototypes
    WeaponParser *wp = new WeaponParser;
    vector<Weapon*> *weps = wp->Load();
    delete wp;
    
    gui = new Gui();
    gui->Init();
    
    gui->SetDungeon(dungeon);
    gui->SetEntities(activeEnts);
    gui->SetCharData(player, dungeon);
    gui->SetVisInfo(player->visInfo);
    
    gui->Redraw();
}

// Returns if we are to keep running
bool Game::MainLoop()
{
    // Input
    UiAction action = gui->GetInput();
    
    // Quitting?
    if ( action == UiAction::Quit )
        return false;
    
    // DOING OTHER THANG??
    bool moved = false; // Did player succesfully move?
    switch ( action )
    {
        case UiAction::MoveLeft:
            moved = AttemptCharMove(veci(-1,0));
            break;
            
        case UiAction::MoveRight:
            moved = AttemptCharMove(veci(1,0));
            break;
            
        case UiAction::MoveUp:
            moved = AttemptCharMove(veci(0,-1));
            break;
    
        case UiAction::MoveDown:
            moved = AttemptCharMove(veci(0,1));
            break;
            
        default: break;
    }
    
    // Update some stuff if we moved
    if ( moved )
        player->visInfo->UpdateVis();
    
    // Logic - update state
    
    
    // Redraw screen
    gui->FocusOnChar(player);
    gui->Redraw();
    
    return true;
}

void Game::Exit()
{
    endwin();
}

void Game::CharacterCreation()
{
    
}

bool Game::AttemptCharMove(veci rel)
{
    // New pos
    veci newpos = player->location + rel;
    
    // Can we move here?
    Tile *target = &dungeon->tiles[newpos.x][newpos.y];
    
    // Ignore attempts to go through walls
    if ( !target->clipMask )
        return false;
    
    // Otherwie move there
    player->location = newpos;
    
    return true;
}




