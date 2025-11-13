import React, { useState } from 'react';
import { updateMarks, initSample } from '../api';

export default function Staff() {
  const [roll,setRoll] = useState('');
  const [math,setMath] = useState('');
  const [phy,setPhy] = useState('');
  const [chem,setChem] = useState('');
  const [msg,setMsg] = useState(null);

  async function onUpdate(e) {
    e.preventDefault(); setMsg(null);
    const payload = { roll, math: Number(math), phy: Number(phy), chem: Number(chem) };
    const res = await updateMarks(payload);
    if (res.ok) {
      setMsg({ type:'success', text: `Updated marks for ${res.roll}` });
      setRoll(''); setMath(''); setPhy(''); setChem('');
    } else setMsg({ type:'error', text: res.error || 'Error' });
  }

  async function onSample() {
    const r = await initSample();
    if (r.ok) setMsg({ type:'success', text:'Sample data initialized' });
    else setMsg({ type:'error', text: r.error || 'Could not init sample' });
  }

  return (
    <div className="form-card">
      <h4>Staff: Enter / Update Marks</h4>
      <form onSubmit={onUpdate} className="row g-3">
        <div className="col-md-3">
          <label className="form-label">Roll</label>
          <input className="form-control" value={roll} onChange={e=>setRoll(e.target.value)} required/>
        </div>
        <div className="col-md-3">
          <label className="form-label">Math</label>
          <input className="form-control" type="number" value={math} onChange={e=>setMath(e.target.value)} required/>
        </div>
        <div className="col-md-3">
          <label className="form-label">Physics</label>
          <input className="form-control" type="number" value={phy} onChange={e=>setPhy(e.target.value)} required/>
        </div>
        <div className="col-md-3">
          <label className="form-label">Chemistry</label>
          <input className="form-control" type="number" value={chem} onChange={e=>setChem(e.target.value)} required/>
        </div>
        <div className="col-md-3 mt-2">
          <button className="btn btn-primary btn-smooth w-100" type="submit">Update Marks</button>
        </div>
        <div className="col-md-3 mt-2">
          <button className="btn btn-outline-secondary w-100" type="button" onClick={onSample}>Init Sample Data</button>
        </div>
      </form>
      {msg && <div className={`mt-3 alert ${msg.type==='success'?'alert-success':'alert-danger'}`}>{msg.text}</div>}
      <div className="small-note mt-2">Marks must be integers (0–200). Use Init Sample to add demo students.</div>
    </div>
  );
}
