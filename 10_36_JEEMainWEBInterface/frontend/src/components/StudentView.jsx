import React, { useState } from 'react';
import { getStudent } from '../api';

export default function StudentView() {
  const [roll,setRoll] = useState('');
  const [student,setStudent] = useState(null);
  const [msg,setMsg] = useState(null);

  async function onView(e) {
    e.preventDefault(); setMsg(null);
    const res = await getStudent(roll);
    if (res && res.roll) { setStudent(res); setMsg(null); }
    else { setStudent(null); setMsg(res.error || 'Not found'); }
  }

  return (
    <div className="form-card">
      <h4>Student: View Result</h4>
      <form onSubmit={onView} className="row g-3">
        <div className="col-md-4">
          <input className="form-control" placeholder="Enter Roll (e.g. G00001)" value={roll} onChange={e=>setRoll(e.target.value)} required />
        </div>
        <div className="col-md-2">
          <button className="btn btn-primary btn-smooth w-100" type="submit">View Result</button>
        </div>
      </form>

      {msg && <div className="mt-3 alert alert-warning">{msg}</div>}

      {student && (
        <div className="mt-3">
          <h5>{student.roll} — {student.name}</h5>
          <p>Category: {student.category}</p>
          <p>Math: {student.math ?? '—'} | Physics: {student.phy ?? '—'} | Chemistry: {student.chem ?? '—'}</p>
          <p><strong>Total:</strong> { (student.math!=null && student.phy!=null && student.chem!=null) ? (student.math + student.phy + student.chem) : '—' }</p>
        </div>
      )}
    </div>
  );
}
