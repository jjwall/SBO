# SBO
___

This is a side project to practice networking techniques as well improve my overall knowledge of TypeScript and C++. It is a multi-player browser based game built with a C++ back-end. The end result is going to be some sort of 2d [MOBA](https://en.wikipedia.org/wiki/Multiplayer_online_battle_arena) game.

Technologies include:
+ [WebSocket++](https://github.com/zaphoyd/websocketpp)
+ [JSON For Modern C++](https://github.com/nlohmann/json)
+ [PixiJS](https://github.com/pixijs/pixi.js)

### To build the project
Using CMake, Ninja, and versions of GCC or MSVC that support C++ 14 and above, make a build directory and run:
```
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
```

___
#### To run the project
```
npm install
node server.js
```

Alternatively, you can manually spin up processes of ``sbo.exe`` by running:
```
./sbo.exe 9001
```

Be sure to append the URL parameters ``?port=9001&loginUserId=100000`` at the end of your file path to ``game.html``.  Running the project this way bypasses the lobby system and allows for direct testing of the game engine.