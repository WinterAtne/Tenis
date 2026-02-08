# ¡Tenis!
I made this simple game based on the hit 1972 game Pong. I created it to test out the Raylib library and Emscripten tool chain for web (really good experience, a bit hard to get bootstrapped).

Player #1 (left side) can use the W and S keys to move up and down respectively | Player #2 can use I and K.

The ball will accelerate slightly as the rounds go on, although it wont get faster than a certain speed.

Can be played on [itch.io](https://winteratne.itch.io/tenis)

### Usage
Install [emscripten](https://emscripten.org/), and build [raylib](https://www.raylib.com/) for [web](https://terminalroot.com/how-to-install-raylib-with-web-support/). Clone this repo, and take libraylib.a from raylib/raylib, and place it into a lib directory in the Tenis repository. Run `make clean` and `make`, then your browser will open and you'll be playing ¡Tenis!
