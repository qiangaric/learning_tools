'''
Descripttion: 
version: 
Author: Gao
Date: 2023-12-28 15:18:01
LastEditors: Gao
LastEditTime: 2023-12-28 15:21:36
'''


import unreal

# 获取当前编辑的世界
world = unreal.EditorLevelLibrary.get_editor_world()

# 定义立方体的位置和大小
cube_location = unreal.Vector(0, 0, 0)
cube_size = unreal.Vector(100, 100, 100)

# 创建一个静态网格体（立方体）
cube_actor = unreal.EditorLevelLibrary.spawn_actor_from_class(unreal.StaticMeshActor, cube_location)
cube_component = cube_actor.get_static_mesh_component()
cube_component.set_static_mesh(unreal.EditorAssetLibrary.load_asset("/Game/Path/To/Your/CubeMesh.CubeMesh"))

# 设置立方体的缩放
cube_actor.set_actor_scale3d(cube_size)

# 显示一些日志信息
unreal.log("Created a cube at {}".format(cube_location))

# 将立方体添加到世界
unreal.EditorLevelLibrary.add_actor_to_level(cube_actor, world.current_level)

# 保存世界
unreal.SystemLibrary.save_current_level()
