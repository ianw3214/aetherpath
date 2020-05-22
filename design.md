# Aetherpath

Earth is on the brink of collapse; In order to survive, humanity must find a new home. Command starships and gather resources to save humanity!

## Overview

**Aetherpath** is a strategy game where the player commands fleets of starships to explore the the vast and unending space. The goal of the game is to find an inhabitable planet for all humans to migrate to, and successfully move enough humans to the target planet so that humanity can continue to prosper. In order to reach the goal, the player will have to utilize their ships efficiently to gather resources from space.

This game takes massive inspiration from _Faster than Light_ in many ways; One of the biggest ways is that beating the game should be a challenge for the player. Although there is no combat in the game, the managing of resources is hard enough to lose the game many times. There aren't too many RNG elements, so the player should be able to find flaws in their gameplay and improve after each loss.

## Mechanics

### Resources

There will be many resources the player has to manage, and each will have different uses in the game.

- *Population:* The main resource that the player needs to manage to win the game
- *Oxygen:* Required for population to live
- *Fuel:*  Required for spaceships to move
- *Metal:* Used to build more ships

If scope allows, there are some other resource ideas that might enhance gameplay.

- *Food:* Used to help increase human population somehow
- *Rare metal:* Differentiate between metal for building different kinds of ships

### Asteroids

Asteroids are resource nodes that float around in space. Their resources can be collected by ships, but the amount of resources they have can not be replenished. The size of these nodes will diminish as ships collect their resources, until they disappear into nothing.

### Planets

Like asteroids, planets also contain resources. However, they will not diminish in size as their resources get mined. Instead, the player can choose to colonize the planets, transferring any kind of resources from ships to the planet. The planet can then act as an intermediate base for the player to store resources and build ships. Each planet will have a maximum capacity of resources, and potentially more different traits to add variety if scope allows.

### Ships

Ships are used to transport and gather resources. There are many different types of ships that the player can control, from mining ships to scouts to heavy storage ships. Ships can be created on planets, and they all cost different amounts of resources to create. Their stats may also differ, between storage capacity, movement speed, mining speed, transfer speed, etc... More traits can potentially be added if scope allows.

### Character System

There are characters that the player can put in charge of certain tasks, and the player can develop different relationships with these characters. These players have different traits that can provide different boosts depending on their role. The player can assign them to be ship captains or planet governors, and they will level up with each action done on the entity they are assigned to.

The characters can either be randomly spawned or spawned based on a timer. They can also be spawned on either random planets or always on earth. If scope allows, players could also obtain certain characters depending on certain situations (spawned a certain character, found a certain planet, etc..)

## Map Generation

The map is populated with asteroids and planets, including one earth as the players starting base and one (or more) *target* planets, which is the end goal of the game. The resource nodes are populated with semi-random amounts of resources, but ensured to be distributed somewhat evenly so that the player always has a chance to win.

## Replayability

The replayability of the game comes from the difficulty, beating the game should be a challenging task and not easily achievable by the player. There can be different difficulty settings so that once the player beats the game, they can still play the game on a harder difficulty.

## Art

In terms of art style, the game assets will be done with pixel art. Shaders can potentially be used to enhance certain aesthetics, but this will depend on how well it can fit with the pixel art style.

The UI needs to look clean and modern, dark backgrounds with light outlines to give it a sleek look. Since the UI is a very large part of the game, it has to be polished to look as good as possible while being as responsive as possible.

## Ship types

### Mining ship

The mining ship is used to efficiently gather resources from resource nodes.

### Scout ship

The scout ship is a fast ship meant to let the player explore quickly and efficiently.

### Mothership

The mothership is a giant ship capable of transferring massive amounts of resources between ships and colonies.

## Other mechanics

### Fog of war

Fog of war is a potential mechanic, it can really broaden the exploration aspect of the gameplay since the player wouldn't be able to see the whole map from the beginning of the game. It will also encourage the use of scout ships to explore more of the fog of war, whereas without fog of war scout ships are significantly less useful.

### Ship augmentations

Ship augmentations can add a lot of variety to the game without having to put in a lot of different ship types. Some augmentation ideas include increased mining speed, increased vision range, increased storage, emergency oxygen supply, faster movement, increased gathering amount, etc...

Another potential interaction with the game is more uses from colonies, where the ship has to dock at a colony in order to receive augmentations. This gives colonies more purpose than just a ship making factory, and players will have to decide if they want to spend resources to return a ship to a colony.

### Research

Research can potentially work really well with the augmentation system, where players have to research augmentations before it is available to them. It will most likely be time based, and the player can choose things to research from a _research tree_ based on their playstyle.

### Moving asteroids / Ship health

Potentialy dangers to ships can also make gameplay a lot more interesting - planets and ships can have a health value so that asteroids that ram into them will cause damage.

This will have to be carefully tuned though, since the player cannot watch over all their ships/planets at once. One potential solution is a feature where asteroids have their paths projected, and if it might hit a ship or planet the player can be alerted.

This might also allow for an 'attack' type of ship, where it can destroy asteroids very quickly but not a lot of resources are gathered from it.
