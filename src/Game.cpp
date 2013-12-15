//
//  Game.cpp
//  forogue
//
//  Created by Lasse Carstensen on 29/11/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//
// This file is part of FOR.
//
// FOR is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// FOR is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FOR (see file LICENSE).  If not, see <http://www.gnu.org/licenses/>.


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
    gui = NULL;
    currLocation = NULL;
    world = NULL;
    player = NULL;
    locations = NULL;
    
    locations = new vector<Dungeon*>;
    
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
    Dungeon *dungeon = new Dungeon(spec);
    
    dungeon->Dump("leveldump.txt");
    dungeon->DumpVisGroups("visdump.txt");
    dungeon->DumpEdgeMask("edgedump.txt");
    
    // Spawn player into dungeon near start
    veci loc = dungeon->GetPlayerSpawnCoords();
    player->location = loc;
    
    // Add player to ents
    dungeon->activeEnts->push_back(player);
    
    // Init visibility for this player and current dungeon
    player->visInfo = new Visibility(dungeon,player);
    player->visInfo->ClearVis();
    player->visInfo->UpdateVis();
    
    // Create wasteland
    world = new World( WorldSpec() );
    world->Dump("worlddump.txt");
    
    // Start in overworld
    isInDungeon = false;
    player->location = veci(10,10);
    currLocation = world;
    
    // Vis for travelling
    player->visInfo = new Visibility(world,player);
    player->visInfo->ClearVis();
    player->visInfo->UpdateVis();
    
    // END TMP
    
    // Load item prototypes
    WeaponParser *wp = new WeaponParser;
    vector<Weapon*> *weps = wp->Load();
    delete wp;
    
    gui = new Gui();
    gui->Init();
    
    gui->SetLocation(world);
    gui->SetEntities(dungeon->activeEnts);
    gui->SetCharData(player, world);
    gui->SetVisInfo(player->visInfo);
    
    gui->PostMessage("Welcome to FOR.");
    
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
    
    // First attempt resizing if term has changed
    gui->Resize();
    
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

// Returns true if we moved, false if we were blocked
bool Game::AttemptCharMove(veci rel)
{
    // New pos
    veci newpos = player->location + rel;
    
    Tile *target = NULL;
    
    // World or dungeon
    target = currLocation->GetTile(newpos.x, newpos.y);
    
    // NULL if out of bounds, can't move
    if ( !target )
        return false;
    
    // Ignore attempts to go through walls/impenetrable objects
    if ( !target->clipMask )
        return false;
    
    // Otherwie move there
    player->location = newpos;
    
    return true;
}




