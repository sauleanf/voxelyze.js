{
  "targets": [{
    "target_name": "Voxelyze",
    "cflags!": ["-fno-exceptions"],
    "cflags_cc!": ["-fno-exceptions"],
        "conditions": [
            ["OS=='mac'", {
              "xcode_settings": {
                "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
              }
            }]
          ],
    "sources": [
      "VoxelyzeExport.cc",
      "Voxelyze.cc",
      "Voxelyze/CVoxelyze.cc",
      "Voxelyze/VX_Collision.cc",
      "Voxelyze/VX_External.cc",
      "Voxelyze/VX_LinearSolver.cc",
      "Voxelyze/VX_Link.cc",
      "Voxelyze/VX_Material.cc",
      "Voxelyze/VX_MaterialLink.cc",
      "Voxelyze/VX_MaterialVoxel.cc",
      "Voxelyze/VX_MeshRender.cc",
      "Voxelyze/VX_Voxel.cc",
      "Array3D.h",
      "Quat3D.h",
      "Vec3D.h"
    ],
    "include_dirs": [
      "<!@(node -p \"require('node-addon-api').include\")"
    ],
    'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],
  }]
}
