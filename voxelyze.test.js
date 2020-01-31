const Voxelyze = require("./Voxelyze.js");

describe("voxelyze simulation", () => {
  let vx;
  let voxelSize = .5
  beforeEach(() => {
    vx = new Voxelyze.createSimulation(voxelSize);
  });

  it("sets the voxel size to the right value", () => {
    expect(vx.getVoxelSize()).toEqual(voxelSize);
  });

  it("allows you to reset the voxel size", () => {
    let newVoxelSize = .05;
    vx.setVoxelSize(newVoxelSize);
    expect(vx.getVoxelSize()).toEqual(newVoxelSize);
  });

  it("has no materials in the simulation", () => {
    expect(vx.materialCount()).toEqual(0);
  });

  describe("material", () => {
    const range = (length) => Array.from(Array(length).keys());

    describe("Adding one material", () => {
      let testMaterial;
      let youngsModulus = 100000;
      let density = 5000;

      beforeEach(() => {
        testMaterial = vx.addMaterial(youngsModulus, density);
      });

      it("is added to the simulation", () => {
        expect(vx.materialCount()).toEqual(1);
      });

      it("has the right index", () => {
        expect(testMaterial.index).toEqual(0);
      });
    });

    describe("adding multiple materials", () => {
      let testMaterials = [];
      let startYoungsModulus = 10000;
      let startDensity = 1000;
      let iterations = 12;

      beforeEach(() => {
        testMaterials = range(iterations).map((index) => vx.addMaterial(
          index * startYoungsModulus, index * startDensity))
      });

      it("all is added to the simulation", () => {
        expect(vx.materialCount()).toEqual(iterations);
      });

      it("all has the right index", () => {
        testMaterials.forEach((material, index) => {
          expect(material.index).toEqual(index);
        });
      });
    });

    describe("adding one voxel", () => {
      let voxelMaterial;
      let youngsModulus = 100000;
      let density = 5000;
      let voxel;

      test("has zero voxels", () => {
        expect(vx.voxelCount()).toEqual(0);
      });

      beforeEach(() => {
        voxelMaterial = vx.addMaterial(youngsModulus, density);
      });

      test("adds voxel to simulation using the material index", () => {
        voxel = vx.setVoxel(voxelMaterial.index, 0, 0, 0);
        expect(vx.voxelCount()).toEqual(1);
      })

      test("adds voxel to simulation using the material", () => {
        voxel = vx.setVoxel(voxelMaterial, 0, 0, 0);
        expect(vx.voxelCount()).toEqual(1);
      });

      describe("properties of voxels", () => {
        test("has no initial force", () => {
          expect(voxel.getForce()).toEqual([0, 0, 0]);
        })

        const testSettingForce = (x, y, z, axis) => {
          test(`setForce on a voxel on the ${axis} axis`, () => {
            voxel.setForce(x, y, z);
            expect(voxel.getForce()).toEqual([x, y, z]);
          });
        };

        testSettingForce(1, 0, 0, "positive x axis");

        testSettingForce(0, 1, 0, "positive y axis");

        testSettingForce(0, 0, 1, "positive z axis");

        testSettingForce(-1, 0, 0, "negative x axis");

        testSettingForce(0, -1, 0, " negative y axis");

        testSettingForce(0, 0, -1, "negative z axis");

        testSettingForce(1, 2, -1, "all the axes");



      });
    });
  });
});
