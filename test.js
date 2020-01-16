const Voxelyze = require("./Voxelyze.js");

const voxelyze = new Voxelyze.Voxelyze(2);
const m1 = voxelyze.addMaterial(100, 100);
const m2 = voxelyze.addMaterial(100, 100);
const m3 = voxelyze.addMaterial(100, 100);
console.log(voxelyze.materialCount());
const v1 = voxelyze.setVoxel(m1, 0, 0, 0);
console.log(v1);
console.log(voxelyze.materialCount());
