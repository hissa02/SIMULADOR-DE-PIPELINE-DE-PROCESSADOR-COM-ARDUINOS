// Dados temporários - serão substituídos por dados reais do Arduino

export const MODES = {
  NORMAL: 'normalStatus'
};

export const MODE_NAMES = {
  normalStatus: 'Pipeline Normal'
};

export const STAGE_NAMES = ['IF', 'ID', 'EX', 'MEM'];

export const RGB_COLORS = {
  GREEN: 'green'
};

export const generateMockData = (cycle, mode) => {
  return {
    timestamp: Date.now(),
    mode: mode,
    cycle: cycle,
    pipeline: [],
    rgb: 'green',
    hazard: { active: false },
    prediction: { taken: null },
    metrics: { cpi: 1.0, totalCycles: cycle, totalStalls: 0, totalInstructions: 0 },
    event: null
  };
};