This GeometryGame is made with the SFML C++ library

## Compilation ##
type make in terminal and then make run to run it


----------------------------------------------------------------------------------
Assets Specification File
----------------------------------------------------------------------------------

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