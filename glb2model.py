# REQUIRES:
#   pip install trimesh
#   pip install scipy

import sys
import trimesh

glb_filename = sys.argv[1]

scene = trimesh.load(glb_filename, force="scene")
mesh = scene.to_geometry()

vertices = mesh.vertices
vertex_normals = mesh.vertex_normals
texture_coordinates = mesh.visual.to_texture().uv
faces = mesh.faces

print('input file:', sys.argv[1])
print(f"There are {len(vertices)} vertices")
print(f"There are {len(vertex_normals)} vertex_normals")
print(f"There are {len(texture_coordinates)} texture_coordinates")
print(f"There are {len(faces)} faces")
print('output file:', sys.argv[2])

with open(sys.argv[2], "w") as output_file:

    output_file.write("l assets/materials/color.material\n")
    output_file.write("m 0\n")
    output_file.write("o\n")

    for (v, vn, vt) in zip(vertices, vertex_normals, texture_coordinates):
        output_file.write(f"v"
                          f" {' '.join(str(x) for x in v)}"
                          f" {' '.join(str(x) for x in vn)}"
                          f" {' '.join(str(x) for x in vt)}"
                          f"\n"
                          )

    for f in faces:
        output_file.write(f"f {' '.join(str(v) for v in f)}\n")

    output_file.write("e\n")
