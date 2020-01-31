const Voxelyze = require("./Voxelyze.js");

const vx = new Voxelyze.createSimulation(.05);
const pMaterial = vx.addMaterial(100000, 1000);

const voxel1 = vx.setVoxel(pMaterial, 0, 0, 0);
const voxel2 = vx.setVoxel(pMaterial, 1, 0, 0);
const voxel3 = vx.setVoxel(pMaterial, 2, 0, 0);

voxel1.setFixedAll();
voxel3.setForce(0, 0, -2);
console.log(Object.getOwnPropertyNames(voxel1))
console.log(voxel3.getForce())
console.log(vx.getVoxelSize())

vx.enableFloor(false);

Array(120).fill(0).forEach((i) => {
  vx.doTimeStep();
});
