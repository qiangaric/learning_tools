cmake_minimum_required(VERSION 3.26)
project(PVZ)

set(CMAKE_CXX_STANDARD 17)
set(EasyX_DIR D:\\c++easyx)
include_directories(${EasyX_DIR}/include)
link_directories(${EasyX_DIR}/lib64)

link_libraries(libEasyX.a libgdi32.a libole32.a)

set(WinLib_DIR C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.19041.0\\um\\x64)
link_directories(${WinLib_DIR})
link_libraries(WinMM.Lib MSImg32.Lib)

add_executable(PVZ main.cpp
        m_local_resources.h
        models/Land.h
        models/SunshineBall.h
        models/Zombie.h
        models/Bullet.h
        models/GameStatus.h
        tools/tools.h
        tools/tools.cpp
        models/Plant.h
        models/Plant.cpp
        models/plants/Peashooter.h
        models/plants/Sunflower.h
        models/plants/RepeaterPea.h
        models/plants/PotatoMine.h
        models/plants/SnowPea.h
        models/plants/WallNut.h)
