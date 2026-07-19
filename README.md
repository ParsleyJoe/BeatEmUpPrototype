# Raylib Prototype
 - Outdated; I don't make games much anymore, but it will be updated soon.

This is a template-type project made to make games faster in Raylib. It includes all the functionality we would have to add in any Raylib game, like animations, player class and base enemy class. The idea is to build on top of this code and make a game.

### Notes about extending

- RlImGui
  - The library rlImgui is used to make debugging easier; to disable it, remove the rlImgui and ImGui-related code from main.cpp and remove libraries from the root CMakeLists.txt
- Player and Enemy class
  - Classes are very bare-minimum; base values are initialised from constructor member-initialiser lists; you probably would want to change the Attack() functions in both classes first, as this template has melee-based attacks.


## Build
```
    cmake -G Ninja -b build
    cmake --build build
```

## Final Note

The base for this was the raylib quickstart by meemknight: [here](https://github.com/meemknight/cmakeSetup)
