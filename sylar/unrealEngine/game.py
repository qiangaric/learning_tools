'''
Descripttion: 
version: 
Author: Gao
Date: 2023-12-28 15:18:01
LastEditors: Gao
LastEditTime: 2023-12-28 15:21:36
'''


import unreal

# ��ȡ��ǰ�༭������
world = unreal.EditorLevelLibrary.get_editor_world()

# �����������λ�úʹ�С
cube_location = unreal.Vector(0, 0, 0)
cube_size = unreal.Vector(100, 100, 100)

# ����һ����̬�����壨�����壩
cube_actor = unreal.EditorLevelLibrary.spawn_actor_from_class(unreal.StaticMeshActor, cube_location)
cube_component = cube_actor.get_static_mesh_component()
cube_component.set_static_mesh(unreal.EditorAssetLibrary.load_asset("/Game/Path/To/Your/CubeMesh.CubeMesh"))

# ���������������
cube_actor.set_actor_scale3d(cube_size)

# ��ʾһЩ��־��Ϣ
unreal.log("Created a cube at {}".format(cube_location))

# ����������ӵ�����
unreal.EditorLevelLibrary.add_actor_to_level(cube_actor, world.current_level)

# ��������
unreal.SystemLibrary.save_current_level()
