# LUDUM DARE 46

This game is made as a compo entry for ludum dare 46 - the theme is **keeping it alive**

## SUMMARY

In this game, you will have to manage humanity to ensure its survival. While earth is falling into ruins, you command spaceships to gather resources no longer available to earth in hopes that humanity can survive.

## IDEAS

- How will the game end?
  - Research based - spend certain amount of resources to 'unlock' humanities survival
  - Exploration based - find a habitable planet for humanity
  - Why not both? alternate endings :D

## GAME DESIGN NOTES

- Each unit of oxygen will sustain 100 people per day
- Each day will be set as an arbitrary amount of time irl (5 minutes or something)

## TODOs (if I ever work on this again)

- Store ships within other ships
- More UI interactivity
  - Change cursor icon
  - Highlight buttons
  - blinking icons
- Collision system
  - Asteroids can damage earth, have to destroy asteroids w/ ship
- Ship health
- More visuals
  - Mining visuals
  - Transfer resource visuals
  - Icons for ships in planets/hangars
  - Icons over ships when sufficiently zoomed out
- Time speed up system
- Better tutorial
- Have ships face directions + animations
- LOD system so art doesn't look janky zoomed out
- Optimize (split into 'chunks' and only update/render chunks that the player are in
- Engine: Render pushes things onto queue - easily separate engine/render thread
- Engine: Batch rendering (for things like stars)
- Ship automation (commands)
- More variety in things to explore
- Event system
  - Random events that could help/hurt the player
