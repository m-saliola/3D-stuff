import bpy, bmesh
import sys


def export_to_custom_format():

    obj = bpy.context.object
    assert obj.type == 'MESH'
    
    depsgraph = bpy.context.evaluated_depsgraph_get()

    if obj.mode != 'OBJECT':
        bpy.ops.object.mode_set(mode='OBJECT')
        
    temp_mod = obj.modifiers.new(name="__temp_triangulate__", type='TRIANGULATE')
    eval_obj = obj.evaluated_get(depsgraph)
    tri_mesh = eval_obj.to_mesh()

    for poly in tri_mesh.polygons:
        assert len(poly.vertices) == 3

    mesh = tri_mesh

    extension = 'model'
    filename = obj.name.replace(" ", "_") + '.' + extension
    print(filename)
    
    with open(filename, "w") as output_file:
        output_file.write("l assets/materials/color.material\n")
        output_file.write("m 0\n")
        output_file.write("o\n")
        
        for v in mesh.vertices:
            output_file.write(f"v"
                              f" {' '.join(str(x) for x in v.co)}"
                              f" {' '.join(str(x) for x in v.normal)}"
                              f" {' '.join(str(x) for x in [0, 0])}"
                              f"\n")
        

        for face in mesh.polygons:
            output_file.write(f"f {' '.join(str(v) for v in face.vertices)}\n")
            
        output_file.write("e\n")
                    
        
if __name__ == "__main__":
    export_to_custom_format()