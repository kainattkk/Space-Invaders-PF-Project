# Introduction

A 2D arcade-style alien shooter game developed as a course project. Inspired by classic games like Space Invaders, this game challenges the player to destroy a grid of invading aliens, manage lives and scores, and progress through increasingly difficult levels.

# Core Gameplay
## Dynamic Scoring System

Score for killing an alien decreases over time until a minimum threshold is reached.

Encourages quick action and reflex-based gameplay.

## Player Lives

Starts with 3 lives.

Life decreases upon:

Getting hit by alien bullets.

Colliding with aliens.

Game Over when lives reach 0.

## Alien Grid

5x10 grid of aliens moves horizontally and slowly descends.

If any alien reaches the bottom, it's Game Over.

Randomized alien bullet attacks toward the player.

## Player Movement & Shooting

Player ship can move in all 4 directions: ↑ ↓ ← →

Can fire 1 bullet at a time upward to destroy aliens.

Bullet disappears upon collision or reaching the screen top.

## Pause Menu

Toggle pause with ESC.

## Pause Menu Options:

Resume Game

Save Game

Quit Game

## Save State
Game progress can be saved to a .txt file.

Resume game later by loading saved state.

## High Score Table
Top 5 high scores maintained in a persistent file.

Not lost on game exit or restart.

## Game Levels

### Easy Level:
least movement of aliens and frequency of shooting.

### Medium Level:
Standard alien speed and bullet frequency.

### Hard Level:
Faster aliens and bullet firing rate.

# Addiotional Information
help.h is used for gaphics which mainly uses windows.h.

put it in the same project.

run the text editor as adminitrator to make it work.
