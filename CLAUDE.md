# Main goal: compile this graphical C project to WASM with no additional external library (No SDL2, too heavy)

## Done:
- Desktop version works with platform abstraction (platform_mlx.c)
- Web/WASM version works with platform abstraction (platform_web.c)
- Canvas 2D rendering with embedded assets

## To do next:
- Add sound for web build using Web Audio API (currently disabled, desktop uses `system("afplay ...")`)

## Build instructions

### Desktop
```bash
make
./wolf3d maps/demo
```

### Web (WASM)
```bash
# Source Emscripten environment first
source ../emsdk/emsdk_env.sh

# Build
make -f Makefile.web

# Serve locally
python3 -m http.server 8080
# Open http://localhost:8080/wolf3d.html
```

## Architecture
```
Game Logic (unchanged)
       │
       ▼
  platform.h (interface)
       │
  ┌────┴────┐
  ▼         ▼
platform_mlx.c    platform_web.c
 (desktop)          (web/WASM)
```
