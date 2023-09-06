# Echo-Must-Escape   https://www.youtube.com/watch?v=baRQzN4Rr2A
Game Demo focusing on  animations, sequences, melee combat and character movement, inventory system.

GameDesignPlan: Echo must Escape

Animation sequence starts: Echo is on a mission to conduct espionage on a ancient hi-security facility, she must collect information and leave the facility within a limited time before the facility explodes.

Echo walks and come close to precious object. She tries to lift a precious object and self destruct sequence starts with alarms. Robot warriors start to patrol the map and search for the intruder. Controller possess the player character.

echo has to get out of the facility within limited time, and has to fight guards while dodging their attacks. She has a inventory system. To exit the facility multiple keys must be collected from dead enemies and submitted at the door to escape the facility. She must collect treasure and food items by breaking  pots using her sword.

Animation sequence starts: As echo submits all items, animation sequence starts where she exits doors while the facility explodes with a victory music


0:12 Dynamic level start sequence + Integrated main menu
https://github.com/Saish-in3d/slash-001/blob/main/Source/Game_001/Private/HUD/MainMenuWidget.cpp

0:20 Play button clicked
https://github.com/Saish-in3d/slash-001/blob/6721d13a904bb3c232c4d53228955cc136cd854d/Source/Game_001/Private/HUD/MainMenuWidget.cpp#L17
https://github.com/Saish-in3d/slash-001/blob/6721d13a904bb3c232c4d53228955cc136cd854d/Source/Game_001/Private/WorldScript/MyLevelScriptActor.cpp#L82

0:23 Reverse timer and location distance marker
https://github.com/Saish-in3d/slash-001/blob/main/Source/Game_001/Private/HUD/ObjectiveDistanceMarker.cpp
https://github.com/Saish-in3d/slash-001/blob/6721d13a904bb3c232c4d53228955cc136cd854d/Source/Game_001/Private/HUD/SlashHUD.cpp#L27

0:31 Echo Dodge root motion animation
https://github.com/Saish-in3d/slash-001/blob/6721d13a904bb3c232c4d53228955cc136cd854d/Source/Game_001/Private/Character/SlashCharacter.cpp#L195

0:40 Press E to Equip sword
https://github.com/Saish-in3d/slash-001/blob/6721d13a904bb3c232c4d53228955cc136cd854d/Source/Game_001/Private/Character/SlashCharacter.cpp#L141


0:44 Use Sowrd to break objects (Physics)
https://github.com/Saish-in3d/slash-001/blob/6721d13a904bb3c232c4d53228955cc136cd854d/Source/Game_001/Private/Item/Weapons/Weapon.cpp
https://github.com/Saish-in3d/slash-001/blob/main/Source/Game_001/Private/Breakables/BreakableActor.cpp

0:53 First Cutscene
https://github.com/Saish-in3d/slash-001/blob/6721d13a904bb3c232c4d53228955cc136cd854d/Source/Game_001/Private/TriggerActor.cpp#L55
https://github.com/Saish-in3d/slash-001/blob/6721d13a904bb3c232c4d53228955cc136cd854d/Source/Game_001/Private/TriggerActor.cpp#L144

1:16 Enemy Logic
https://github.com/Saish-in3d/slash-001/blob/6721d13a904bb3c232c4d53228955cc136cd854d/Source/Game_001/Private/Enemy/Enemy.cpp

1:21 Enemy HealthBar
https://github.com/Saish-in3d/slash-001/blob/main/Source/Game_001/Private/HUD/HealthBar.cpp
https://github.com/Saish-in3d/slash-001/blob/main/Source/Game_001/Private/HUD/HealthBarComponent.cpp
https://github.com/Saish-in3d/slash-001/blob/6721d13a904bb3c232c4d53228955cc136cd854d/Source/Game_001/Private/Components/AttributeComponent.cpp

1:26 Pause Menu
https://github.com/Saish-in3d/slash-001/blob/main/Source/Game_001/Private/HUD/PauseMenuWidget.cpp

1:30 Game graphics Settings
BP setup

1:39 Smarter enemies
Root Motion BP setup
https://github.com/Saish-in3d/slash-001/blob/6721d13a904bb3c232c4d53228955cc136cd854d/Source/Game_001/Private/Enemy/Enemy.cpp#L376

1:58 Inventory- using food to heal up
https://github.com/Saish-in3d/slash-001/blob/6721d13a904bb3c232c4d53228955cc136cd854d/Source/Game_001/Private/InventoryComponent.cpp
https://github.com/Saish-in3d/slash-001/blob/6721d13a904bb3c232c4d53228955cc136cd854d/Source/Game_001/Private/Inventory/BaseItem.cpp
https://github.com/Saish-in3d/slash-001/blob/6721d13a904bb3c232c4d53228955cc136cd854d/Source/Game_001/Private/Inventory/FoodItem.cpp

2:05 Echo Death Logic
https://github.com/Saish-in3d/slash-001/blob/6721d13a904bb3c232c4d53228955cc136cd854d/Source/Game_001/Private/Enemy/Enemy.cpp#L354C15-L354C15

2:13 Level win logic
https://github.com/Saish-in3d/slash-001/blob/6721d13a904bb3c232c4d53228955cc136cd854d/Source/Game_001/Private/KeyItem.cpp#L24
https://github.com/Saish-in3d/slash-001/blob/6721d13a904bb3c232c4d53228955cc136cd854d/Source/Game_001/Private/Door/DoorActor.cpp

2:30 Win Sequence
https://github.com/Saish-in3d/slash-001/blob/6721d13a904bb3c232c4d53228955cc136cd854d/Source/Game_001/Private/TriggerActor.cpp#L73

