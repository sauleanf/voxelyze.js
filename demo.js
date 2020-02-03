const Voxelyze = require("./Voxelyze.js");

//creates simulation
const vx = new Voxelyze.createSimulation(.005);

//creates material
const pMaterial = vx.addMaterial(1000000, 1000);

//creates three voxels
const voxel1 = vx.setVoxel(pMaterial, 0, 0, 0);
const voxel2 = vx.setVoxel(pMaterial, 1, 0, 0);
const voxel3 = vx.setVoxel(pMaterial, 2, 0, 0);

//fixes the first voxel so that it doesn't move
voxel1.setFixedAll();

//sets a force in the negative z direction on the third voxel
voxel3.setForce(0, 0, -1);

//simulates 100 time steps
for(let i = 0; i < 100; i++) {
  vx.doTimeStep();
}
