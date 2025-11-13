import React, { useState } from 'react';
import { registerStudent } from '../api';

export default function Register() {
  const [name,setName] = useState('');
  const [cat,setCat] = useState('Gen');
  const [msg,setMsg] = useState(null);

  async function onRegister(e) {
    e.preventDefault();
    setMsg(null);
    const res = await registerStudent(name, cat);
    if (res && res.roll) {
      setMsg({ type:'success', text:`Registered. Roll: ${res.roll}` });
      setName('');
    } else {
      setMsg({ type:'error', text: res.error || 'Error' });
    }
  }

  return (
    <div className="form-card">
      <h4>Register Student</h4>
      <form onSubmit={onRegister} className="row g-3">
        <div className="col-md-6">
          <label className="form-label">Name</label>
          <input className="form-control" value={name} onChange={e=>setName(e.target.value)} required />
        </div>
        <div className="col-md-3">
          <label className="form-label">Category</label>
          <select className="form-select" value={cat} onChange={e=>setCat(e.target.value)}>
            <option value="Gen">Gen</option>
            <option value="Resrv">Resrv</option>
          </select>
        </div>
        <div className="col-md-3 align-self-end">
          <button className="btn btn-primary btn-smooth w-100" type="submit">Register</button>
        </div>
      </form>
      {msg && <div className={`mt-3 alert ${msg.type==='success'?'alert-success':'alert-danger'}`}>{msg.text}</div>}
      <div className="small-note mt-2">Roll number is auto-generated and reflects category (G/R + 5-digit seq).</div>
    </div>
  );
}
