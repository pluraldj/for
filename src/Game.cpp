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
    
    gui = NULL;
    location = NULL;
    world = NULL;
    player = NULL;
    
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
    activeEnts->push_back(player);
    
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
    location = world;
    
    // Vis for travelling
    player->visInfo = new Visibility(world,player);
    player->visInfo->ClearVis();
    player->visInfo->UpdateVis();
    
    // END TMP
    
    // Load item prototypes
    WeaponParser *wp = new WeaponParser;
    vector<Weapon*> *weps = wp->Load();
    delete wp;
    
    // Load tilesets
    
    gui = new Gui();
    gui->Init();
    
    gui->SetLocation(world);
    gui->SetEntities(activeEnts);
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
    target = location->GetTile(newpos.x, newpos.y);
    
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




