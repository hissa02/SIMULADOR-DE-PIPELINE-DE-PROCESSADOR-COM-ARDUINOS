import React from 'react';
import '../styles/EventLog.css';

export function EventLog({ events = [], description = '' }) {
  return (
    <div className="event-log-container">
      <h3>Eventos e Logs</h3>

      {description && (
        <div className="current-event">
          <p className="event-description">{description}</p>
        </div>
      )}

      {events.length > 0 ? (
        <div className="events-list">
          {events.map((event, idx) => (
            <div
              key={idx}
              className={`event-item severity-${event.severity}`}
            >
              <div className="event-header">
                <span className="event-type">{event.type}</span>
                <span className={`event-badge badge-${event.severity}`}>
                  {event.severity === 'high' ? '⚠ Alto' : 'ℹ Info'}
                </span>
              </div>
              <p className="event-message">{event.message}</p>
            </div>
          ))}
        </div>
      ) : (
        <div className="no-events">
          <p>Nenhum evento no momento</p>
        </div>
      )}
    </div>
  );
}
