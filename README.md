![voxelyze.js](https://i.imgur.com/895X6SD.png)

[![Actions Status](https://github.com/sauleanf/voxelyze.js/workflows/Deployment%20Logs%20Jest%20Tests/badge.svg)](https://github.com/sauleanf/voxelyze.js/actions)

# What is Voxelyze.js?

Voxelyze.js is a native addon for node.js that allows users to write code for
the C++ physics simulator voxelyze in javascript.

# How to Use

Simulating soft robots in voxelyze involves the following steps:

* Create a Voxelyze instance
* Create a material
* Add voxels using this material
* Specify voxels that should be fixed in place or have force applied
Execute timesteps

```javascript

const Voxelyze = require("./Voxelyze.js");

//creates simulation
const vx = new Voxelyze.createSimulation(.005);

//creates material
const pMaterial = vx.addMaterial(1000000, 1000);

//creates three voxels
const voxel1 = vx.setVoxel(pMaterial, 0, 0, 0);
const voxel2 = vx.setVoxel(pMaterial, 1, 0, 0);
const voxel3 = vx.setVoxel(pMaterial, 2, 0, 0);

// fixes the first voxel so that it doesn't move
voxel1.setFixedAll();

// sets a force in the negative z direction on the third voxel
voxel3.setForce(0, 0, -1);

// simulates 100 time steps
for(let i = 0; i < 100; i++) {
  vx.doTimeStep();
}
```

# Original Voxelyze

If you want to give the original library a try, then go to this
[github repo](https://github.com/jonhiller/Voxelyze).
