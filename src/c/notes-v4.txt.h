#if defined(these_are_notes_dont_compile_this)


Spike blocks = Down->die, up/side->solid
  Bridge blocks = Down=Solid, up/side=passable



============
   To Add
============
Warp Blocks:
  Invisible, completely passable (like 0 empty block).
  Moves Players Map X position to previous Warp Block
  Does nothing if it's the first warp block (for further-right blocks to warp to)'


Levels are a PNG 16px high, multiple of 32px wide
  
16 Block Types:
  0 = Block: empty
  1 = Block: Ground Type Block
  2 = Block: Brick
  3 = Block: ?
  4 = Block: Metal (Used ? Block)
  5 = PipePart (adjacent parts use proper sprites)
  6 = Cloud/Bush (y pos and level type denotes which) (adjacent parts use proper sprites)
  7 = Coin
  8 = Mushroom
  9 = Star
  A = 1UP
  B = 
  C = Enemy Type 1
  D = Enemy Type 2
  E = Enemy Type 3
  F = Enemy Type 4

    
  Empty
    
  Blocks:
    Ground
    Brick
    Question
    Metal (Used ? Block)
    Cloud
    Pipe
    
    Background: Hill
      Cloud
      Bush
      Mushroom Stalk
      Spike Bar
      Tree
      Fence
      Water
      Falling Platform
      Bridge
      
      
      Bullet
      Goomba
      Beetle
      Koopa
      Spiney
      
      
      Mushroom
      Flower
      Star
      1UP
      Coin
      
      
      
X = 0:
  (0, 0 - 0xF) = Color 0-0xF
    (The left edge should be the colors 0-0xF so pebble knows what colors coorelate to which blocks)

X = 1: 
  (1, Y) = 15: Mario Start Y position
  (1, 0) = Level type (night, fire, water, looping?)
    

    
    
SMB1:
Level 1-1:
  224 x 3384 px = 28 x 423 (8x8 px) blocks
  28 blocks high -> 16 blocks high * 423 blocks = 6768 blocks @1B/blk = 6768 bytes per level
  
Level 1-2:
  3056 x 224px
 Level 1-3:
2632 x 224px

---------
 Notes
---------
All Enemy and Player Sprites have a width of 16px
Even technically all blocks have a width of 16px
But heights can vary:
8px: Bridge and hit P-Blocks, Fireball
16px: Most Things
24px: Koopa Troopas, Piranha Plants
32px: Full-size Mario

  
  
  
=================================================================================
  More Notes 2017/02/15
=================================================================================
  Level images will be vertical. 
    This is so continous chunks can be loaded into memory for the current screen
  Levels will be 10px wide
  Need to determine if color images can be saved on B&W Pebbles
    If not, may need to load as a blob
  Local levels will be loaded as a blob 
  Remote levels will be downloaded as PNG files via JS
  
  
  Level Blob/PNG:
    image  width: 10px wide (rotated, levels will be 10 blocks high)
    image height: Different per level
      image height max: I dunno... say, 256px high which = 256 blocks wide.  Most SBM1 levels are 210 to 240 blocks wide.
    each pixel will be 1 byte
    Each Pixel will coorelate to a uint8_t which determines what that spot will be
    First 10px row will contain level data:
      0: Player Start Height
      1: Background color
      2: Foreground color
      3: Level Type (Determines physics)
      4: 
      5: 
      6: 
      7: 
      8: 
      9: 
      
      
  Ideas (may not implement):
   Level Data Compression:
     Level array will be a uint8 array of length LEVEL_LENGTH
     Each uint8 of the array will point to another uint8 array of [10, x]
       10 being the 10 uint8 blocks for that column
       x being how many unique columns
#endif
  