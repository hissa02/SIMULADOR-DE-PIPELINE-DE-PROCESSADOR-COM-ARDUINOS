import React, { useState, useEffect } from 'react';
import { generateMockData, MODES } from './utils/mockData';
import { SimulationControl } from './components/SimulationControl';
import { LEDMatrix } from './components/LEDMatrix';
import { RGBStatus } from './components/RGBStatus';
import { PipelineVisualization } from './components/PipelineVisualization';
import { Metrics } from './components/Metrics';
import { EventLog } from './components/EventLog';
import './App.css';

function App() {
  const [currentMode, setCurrentMode] = useState(MODES.NORMAL);
  const [isRunning, setIsRunning] = useState(false);
  const [cycle, setCycle] = useState(0);
  const [pipelineData, setPipelineData] = useState(null);

  useEffect(() => {
    if (!isRunning) {
      setCycle(0);
      return;
    }

    const interval = setInterval(() => {
      setCycle(prev => prev + 1);
    }, 1000);

    return () => clearInterval(interval);
  }, [isRunning]);

  useEffect(() => {
    const data = generateMockData(cycle, currentMode);
    setPipelineData(data);
  }, [cycle, currentMode]);

  const handleModeChange = (mode) => {
    setCurrentMode(mode);
    if (!isRunning) {
      setCycle(0);
    }
  };

  const handlePlayPause = () => {
    setIsRunning(!isRunning);
  };

  const handleReset = () => {
    setCycle(0);
    setIsRunning(false);
  };

  if (!pipelineData) {
    return <div className="app-loading">Carregando...</div>;
  }

  return (
    <div className="app-container">
      <header className="app-header">
        <div className="header-content">
          <h1>Pipeline Simulator Dashboard</h1>
          <p className="header-subtitle">Simulador didático de pipeline de processadores</p>
        </div>
      </header>

      <main className="app-main">
        <section className="content-section">
          <SimulationControl
            currentMode={currentMode}
            onModeChange={handleModeChange}
            isRunning={isRunning}
            onPlayPause={handlePlayPause}
            onReset={handleReset}
            cycle={cycle}
          />
        </section>

        <div className="content-grid">
          <div className="grid-column">
            <section className="content-section">
              <LEDMatrix
                matrix={pipelineData.ledMatrix}
                cycle={cycle}
              />
            </section>

            <section className="content-section">
              <RGBStatus
                color={pipelineData.rgb}
                mode={pipelineData.mode}
              />
            </section>
          </div>

          <div className="grid-column">
            <section className="content-section">
              <Metrics metrics={pipelineData.metrics} />
            </section>

            <section className="content-section">
              <EventLog
                events={pipelineData.events}
                description={pipelineData.description}
              />
            </section>
          </div>
        </div>

        <section className="content-section full-width">
          <PipelineVisualization
            pipeline={pipelineData.pipeline}
            cycle={cycle}
          />
        </section>
      </main>

      <footer className="app-footer">
        <p>ARQUITETURA DE COMPUTADORES | Simulador de Pipeline com Arduino</p>
      </footer>
    </div>
  );
}

export default App;