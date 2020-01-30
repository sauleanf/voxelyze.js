const Voxelyze = require("./Voxelyze.js");

const voxelyze = new Voxelyze.Voxelyze(2);
const m1 = voxelyze.addMaterial(100, 100);
const m2 = voxelyze.addMaterial(100, 100);
const m3 = voxelyze.addMaterial(100, 100);
const v1 = voxelyze.setVoxel(m1, 0, 0, 0);
const v2 = voxelyze.setVoxel(m1, 0, 1, 0);
const v3 = voxelyze.setVoxel(m1, 0, 1, 1);
const v4 = voxelyze.setVoxel(m1, 3, 3, 3);
voxelyze.floor = true;

voxelyze.floor = false;


voxelyze.getVoxel(3,3,3, (voxel) => {
  console.log(voxel.position());
});
