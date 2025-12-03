// Modos de simulação
export const MODES = {
  NORMAL: 'normal',
  STRUCTURAL_HAZARD: 'structuralHazard',
  DATA_HAZARD: 'dataHazard',
  CONTROL_HAZARD: 'controlHazard',
  STATIC_PREDICTION: 'staticPrediction',
  DYNAMIC_PREDICTION: 'dynamicPrediction'
};

export const MODE_NAMES = {
  normal: 'Pipeline Normal',
  structuralHazard: 'Hazard Estrutural',
  dataHazard: 'Hazard de Dados',
  controlHazard: 'Hazard de Controle',
  staticPrediction: 'Predição Estática',
  dynamicPrediction: 'Predição Dinâmica (Perceptron)'
};

export const STAGE_NAMES = ['IF', 'ID', 'EX', 'MEM', 'WB'];

export const LED_STATES = {
  OFF: 'off',
  ACTIVE: 'active',
  STALL: 'stall',
  HAZARD: 'hazard'
};

export const RGB_COLORS = {
  GREEN: '#22c55e',
  YELLOW: '#eab308',
  RED: '#ef4444',
  BLUE: '#3b82f6'
};

export const generateMockData = (cycle, mode) => {
  let pipeline = generatePipelineData(cycle, mode);
  let metrics = calculateMetrics(cycle, mode, pipeline);
  let events = generateEvents(cycle, mode);
  let rgbColor = getRGBColor(mode, events);

  return {
    timestamp: Date.now(),
    mode: mode,
    cycle: cycle,
    pipeline: pipeline,
    ledMatrix: generateLEDMatrix(cycle, mode, pipeline),
    rgb: rgbColor,
    metrics: metrics,
    events: events,
    description: getDescription(mode, cycle, events)
  };
};

const generatePipelineData = (cycle, mode) => {
  const instructions = [];
  const maxInstructions = 5;
  
  for (let i = 0; i < maxInstructions; i++) {
    const instrCycle = cycle - i;
    if (instrCycle >= 0) {
      const instruction = {
        id: i,
        name: `INSTR ${i}`,
        stages: getStagesForInstruction(i, cycle, mode),
        stalled: isInstructionStalled(i, cycle, mode),
        mispredicted: isMispredicted(i, cycle, mode)
      };
      instructions.push(instruction);
    }
  }
  
  return instructions;
};

const getStagesForInstruction = (instrIndex, cycle, mode) => {
  const stages = {};
  const stageProgress = (cycle - instrIndex) % 5;
  
  STAGE_NAMES.forEach((stageName, stageIndex) => {
    if (stageProgress >= stageIndex) {
      stages[stageName] = 'completed';
    } else if (stageProgress === stageIndex - 1) {
      stages[stageName] = 'active';
    } else {
      stages[stageName] = 'pending';
    }
  });
  
  if (mode === MODES.STRUCTURAL_HAZARD && instrIndex === 1 && cycle > 3 && cycle < 7) {
    stages.EX = 'stall';
  }
  
  if (mode === MODES.DATA_HAZARD && instrIndex === 1 && cycle > 2 && cycle < 6) {
    stages.ID = 'stall';
  }
  
  if (mode === MODES.CONTROL_HAZARD && cycle > 4 && cycle < 8) {
    if (instrIndex > 0 && instrIndex < 4) {
      stages[STAGE_NAMES[0]] = 'flushed';
    }
  }
  
  return stages;
};

const isInstructionStalled = (instrIndex, cycle, mode) => {
  if (mode === MODES.STRUCTURAL_HAZARD) {
    return instrIndex === 1 && cycle > 3 && cycle < 7;
  }
  if (mode === MODES.DATA_HAZARD) {
    return instrIndex === 1 && cycle > 2 && cycle < 6;
  }
  return false;
};

const isMispredicted = (instrIndex, cycle, mode) => {
  if (mode === MODES.CONTROL_HAZARD) {
    return instrIndex > 0 && cycle === 5;
  }
  return false;
};

const calculateMetrics = (cycle, mode, pipeline) => {
  let stalls = 0;
  let flushes = 0;
  
  pipeline.forEach(instr => {
    if (instr.stalled) stalls++;
    if (instr.mispredicted) flushes += 3;
  });
  
  const totalCycles = cycle + 1;
  const totalInstructions = Math.min(cycle + 1, 10);
  const totalStalls = stalls * cycle;
  
  const completedInstructions = Math.max(1, totalInstructions - stalls);
  const cpi = totalCycles / completedInstructions;
  
  return {
    cpi: cpi,
    totalCycles: totalCycles,
    totalInstructions: totalInstructions,
    totalStalls: totalStalls,
    stalls: stalls,
    flushes: flushes,
    throughput: (completedInstructions / totalCycles).toFixed(2)
  };
};

const generateEvents = (cycle, mode) => {
  const events = [];
  
  switch(mode) {
    case MODES.STRUCTURAL_HAZARD:
      if (cycle > 3 && cycle < 7) {
        events.push({
          type: 'STRUCTURAL_HAZARD',
          message: 'Disputa pela ULA: INSTR 0 e INSTR 1 querem usar EX simultaneamente',
          severity: 'high'
        });
      }
      break;
      
    case MODES.DATA_HAZARD:
      if (cycle > 2 && cycle < 6) {
        events.push({
          type: 'DATA_HAZARD',
          message: 'Dependência de dados: INSTR 1 aguarda resultado de INSTR 0',
          severity: 'high'
        });
      }
      break;
      
    case MODES.CONTROL_HAZARD:
      if (cycle === 5) {
        events.push({
          type: 'CONTROL_HAZARD',
          message: 'Branch mispredicted! Flush de 3 instruções.',
          severity: 'high'
        });
      }
      break;
      
    case MODES.STATIC_PREDICTION:
      if (cycle === 5) {
        events.push({
          type: 'PREDICTION',
          message: 'Predição Estática: Branch always NOT taken (padrão)',
          severity: 'low'
        });
      }
      break;
      
    case MODES.DYNAMIC_PREDICTION:
      if (cycle === 5) {
        events.push({
          type: 'PREDICTION',
          message: 'Predição Dinâmica: Perceptron prediz TAKEN (histórico favorável)',
          severity: 'low'
        });
      }
      break;
  }
  
  return events;
};

const getRGBColor = (mode, events) => {
  if (events.length > 0 && events[0].severity === 'high') {
    return RGB_COLORS.RED;
  }
  
  switch(mode) {
    case MODES.STATIC_PREDICTION:
    case MODES.DYNAMIC_PREDICTION:
      return RGB_COLORS.BLUE;
    case MODES.NORMAL:
      return RGB_COLORS.GREEN;
    default:
      return RGB_COLORS.YELLOW;
  }
};

const generateLEDMatrix = (cycle, mode, pipeline) => {
  const matrix = Array(4).fill(null).map(() => Array(4).fill(LED_STATES.OFF));
  
  pipeline.forEach((instr, idx) => {
    Object.entries(instr.stages).forEach(([stage, state], stageIdx) => {
      if (state === 'active') {
        const row = idx;
        const col = stageIdx;
        if (row < 4 && col < 4) {
          matrix[row][col] = instr.stalled ? LED_STATES.STALL : LED_STATES.ACTIVE;
        }
      }
    });
  });
  
  return matrix;
};

const getDescription = (mode, cycle, events) => {
  const baseMsg = `Ciclo ${cycle}: `;
  
  if (events.length > 0) {
    return baseMsg + events[0].message;
  }
  
  return baseMsg + 'Pipeline funcionando normalmente.';
};