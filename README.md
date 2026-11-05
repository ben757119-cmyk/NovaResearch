# NovaResearch

**CS2 Architectural Visual Research Demo**

A self-contained C++ research application that simulates Counter-Strike 2 style entity rendering, ESP overlays, radar, tracers, chams, and environment controls using ImGui + GLFW + OpenGL.

This is a **purely offline simulation / architectural demo**. It does not interact with any game process, memory, or network.

## Features

- Live simulated entities with movement
- Configurable ESP (boxes, names, health bars)
- Tracers with origin selection
- 2D Radar overlay
- Chams material simulation
- Sky / world color overrides
- FOV and misc visual toggles
- Clean ImGui research dashboard

## Requirements

- Windows 10/11 (x64)
- Visual Studio 2022 (or Build Tools) with C++ desktop workload
- CMake 3.20+
- Git

## Building (Local)

```bash
git clone https://github.com/ben757119-cmyk/NovaResearch.git
cd NovaResearch
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

The executable will be at `build/bin/Release/NovaResearch.exe`.

## Building with GitHub Actions

Pushing a tag in the form `v*` (e.g. `v1.0.0`) automatically:

1. Builds a Release Windows x64 executable
2. Creates a GitHub Release
3. Attaches `NovaResearch.exe` as a release asset

## Project Structure

```
NovaResearch/
├── CMakeLists.txt
├── include/
│   ├── Core/
│   ├── Rendering/
│   └── UI/
├── src/
│   ├── main.cpp
│   ├── Core/
│   ├── Rendering/
│   └── UI/
└── .github/workflows/build-release.yml
```

## License

MIT License – see [LICENSE](LICENSE)
