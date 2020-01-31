const Voxelyze = require("./Voxelyze.js");

describe("Voxelyze simulation", () => {
  let Vx;
  let voxelSize = .5
  beforeEach(() => {
    Vx = new Voxelyze.createSimulation(voxelSize);
  });

  it("sets the voxel size to the right value", () => {
    expect(Vx.getVoxelSize()).toEqual(voxelSize);
  });

  it("has no materials in the simulation", () => {
    expect(Vx.materialCount()).toEqual(0);
  });

  describe("Material", () => {

    const range = (length) => Array.from(Array(length).keys());

    describe("Adding one material", () => {
      let testMaterial;
      let youngsModulus = 100000;
      let density = 5000;

      beforeEach(() => {
        testMaterial = Vx.addMaterial(youngsModulus, density);
      });

      it("is added to the simulation", () => {
        expect(Vx.materialCount()).toEqual(1);
      });

      it("has the right index", () => {
        expect(testMaterial.index).toEqual(0);
      });
    });

    describe("Adding multiple materials", () => {
      let testMaterials = [];
      let startYoungsModulus = 10000;
      let startDensity = 1000;
      let iterations = 12;

      beforeEach(() => {
        testMaterials = range(iterations).map((index) => Vx.addMaterial(
          index * startYoungsModulus, index * startDensity))
      });

      it("all is added to the simulation", () => {
        expect(Vx.materialCount()).toEqual(iterations);
      });

      it("all has the right index", () => {
        testMaterials.forEach((material, index) => {
          expect(material.index).toEqual(index);
        });
      });
    })
  });
});
