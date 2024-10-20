This GeometryGame is made with the SFML C++ library

## Compilation ##
type make in terminal and then make run to run it

bin folder stuff
font folder
    contains files ttf 

images folder
    mario megaman misc folders
    contains spritesheets and images used in game    64x64.png 


assets.txt
level1.txt
level2.txt....



------------------------------------------------------------------------------------------------------------
Program Specification
------------------------------------------------------------------------------------------------------------
Assets:
- Entities in the game will be rendered using various Textures and Animations which we will be calling Assets
- Assets are loaded once at the beginning of the program and stored in the Assets class, which is stored by the GameEngine class
- All assets are defined in assets.txt, with the sytax defined below.

NOTE: 
- All entity positions denote the center of their rectangular sprite It also denoted the center of the bounding boc, if it has one 
  This is set via sprite.setOrigin() in the Animation Class constructor

Player:
- The player Entity in the game is represented by Megaman, which has several different Animations: Stand, Run, and Air.
  you must determine which state the player is currently in and assign the correct Animation.
- The player moves with the following controls:
  Left:A, Right:D, Jump:W, Shoot:Spaces
- The playercan move left and right or shoot at any time in game.
- The player can only jump if it is currently standing on a tile
- The jump key needs to be held for max jump. if the key is let go then th player should drop
- If the player moves left/right the sprite should face that direction until the opposite direction is pressed
- Bullets shot by the player travel in the direction the player is facing
- The player collides with Tile entities in the level
- The player does not collide with dec entities
- if the player falls out of the screen they should respawn
- the player should have a gravity component which constantly accelerates it downward on the screen unitl it collides with a tile
- player will have a cboundingbox of a sze specified in the level file 
- the players sprite and bounding box are centers on the players position


Animations:
- implemented by storing multiple frames insied a texture
- Animation Class handles frame advancement based on animation Speed
- you need to implement animation::update() to properly progress animations
- you need to implenment animation hasEnded() which returns true if an animation has finished its last frame, fals eotherwise
- Animations can be repeating or non repeating
- any entity with a non repeating animation should be deystroyed once its animations hasEnded() returns true


Tiles:
- Tiles are entities that define the level geometry and interact with players
- Tiles can be given any animation that is defined in the assets file
- Tiles will be given a CBoundingBox equal to the size of the animation
  tile->getComponent<CAnimation>().animation.getSize()
- The current animation displayed for a tile can be retrieved with: 
  tile->getComponent<CAnimation>().animation.getName()

- Tiles have different behavior depending on which Animation they are given.

    Brick Tiles
    - Brick tiles are given the 'Brick' Animation
    -When a brick tile collides with a bullet or is hit by player from the bottom 
        -its animation should change to 'Explosion' (non-repeat)
        -Non-repeating animation entities are deystroyed when hasEnded() is true
        - its CBOunding Box component should be removed.
    
    Question Tile
    stufffs


----------------------------------------------------------------------------------
Assets Specification File
----------------------------------------------------------------------------------

There will be three different line types in the Assets file, each of which correspond to a different type of Asset. They are as follows

Texture Asset Specification:
Texture N P
    Texture Name      N    std::string (it will have no spaces)
    Texture FilePath  P    std::string (it will have no spaces)

Animation Asset Specification:
Animation N T F S
    Animation Name    N    std::string (it wil have no spaces)
    Texture Name      T    std::string (refers to an existing texture)
    Frame Count       F    int (number of frames in the Animation)
    Anim Speed        S    int (number of game frames between anim frames)

Font Asset Specification:
Font N P
    Font Name         N    std::string (no Spaces)
    Font File Path    P    std::String (no Spaces)
 



----------------------------------------------------------------------------------
Level Specification File
----------------------------------------------------------------------------------

Game levels will be specified by a Level file, which will contain a list of entity Specifications,
one per line. It will also contain a single line which specifies properties of the player in that level. In this way, you
can define an entire elevel in the data file, rather than in programming code. The syntax of the line of the level file are as follows

NOTE: 
    All (GX,GY) positions given in the level specification file are given in 'grid' coords. the grid cells are the size 64 by 64pixels
    and the entity should be positioned such that the bottom left corner of its texture is aligned with the bottom left corner of the grid coordinate.
    The grid starts at (0,0) in the bottom-left of the screen, and can be seen by pressing the 'G' key while in the game.

Tile Entity Specification:
Tile N GX GY   (name gridX gridY)
    Animation Name  N       std:string (Animation asset name for this tile)
    GX Grid X Pos   GX      float
    GY Grid Y Pos   GY      float

Decoration Entity Spec:
Dec N X Y
    Animation Name  N        std::string (Animation asset name for this tile)
    X Position      X        float
    Y Position      Y        float

Player Spec:
PLayer GX GY CW CH SX SY SM GY B
    GX, GY, Grid Pos   X, Y    float, float (starting position for player)
    BoundingBox W/H    CW, CH  float, float
    Left/Right Speed   SX      float
    Jump Speed         SY      float
    MAx SPeed          SM      float
    Gravity            GY      float
    Bullet Animation   B       std::string (Animation asset to use for bullets)