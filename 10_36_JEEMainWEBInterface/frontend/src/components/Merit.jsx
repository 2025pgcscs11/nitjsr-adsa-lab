import React, { useState } from 'react';
import { getMerit } from '../api';

export default function Merit() {
  const [rows,setRows] = useState([]);
  const [loaded,setLoaded] = useState(false);

  async function load() {
    const r = await getMerit();
    if (Array.isArray(r)) {
      setRows(r);
      setLoaded(true);
    }
  }

  return (
    <div className="form-card">
      <div className="d-flex justify-content-between align-items-center mb-3">
        <h4>Merit List</h4>
        <button className="btn btn-primary btn-smooth" onClick={load}>Refresh Merit List</button>
      </div>

      {loaded && rows.length === 0 && <div className="alert alert-info">No complete results available yet.</div>}

      {rows.length > 0 && (
        <div className="table-responsive">
          <table className="table table-striped">
            <thead>
              <tr><th>#</th><th>Roll</th><th>Name</th><th>Cat</th><th>Math</th><th>Phy</th><th>Chem</th><th>Total</th></tr>
            </thead>
            <tbody>
              {rows.map((r,i) => (
                <tr key={r.roll}>
                  <td>{i+1}</td>
                  <td>{r.roll}</td>
                  <td>{r.name}</td>
                  <td>{r.category}</td>
                  <td>{r.math}</td>
                  <td>{r.phy}</td>
                  <td>{r.chem}</td>
                  <td>{r.total}</td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
      )}
      <div className="small-note mt-2">Merit sorted by total → math → physics (desc). Only students with full marks appear.</div>
    </div>
  );
}
