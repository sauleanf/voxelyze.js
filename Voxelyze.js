const addon = require('bindings')('Voxelyze');

const linkDirection = {
  X_POS: 0,
  X_NEG: 1,
  Y_POS: 2,
  Y_NEG: 3,
  Z_POS: 4,
  Z_NEG: 5,
};

/* Object.defineProperties(addon.Voxelyze.prototype, {
  voxelSize: {
    get() {
      return this.getVoxelSize();
    },
    set(voxelSize) {
      this.setVoxelSize(voxelSize);
    }
  },
  floor: {
    get() {
      return this.isFloorEnabled();
    },
    set(enabled) {
      this.enableFloor(enabled);
    }
  },
  gravity: {
    get() {
      return this.getGravity();
    },
    set(gravity) {
      this.setGravity(gravity);
    }
  }
}); */

module.exports = {
  Simulation: addon.Voxelyze,
  linkDirection,
};
