const API = process.env.REACT_APP_API_BASE || 'http://localhost:3002/api';

export async function registerStudent(name, category) {
  const res = await fetch(`${API}/register`, {
    method: 'POST', headers: {'Content-Type':'application/json'},
    body: JSON.stringify({ name, category })
  });
  return res.json();
}

export async function updateMarks(payload) {
  const res = await fetch(`${API}/staff/update`, {
    method: 'POST', headers: {'Content-Type':'application/json'},
    body: JSON.stringify(payload)
  });
  return res.json();
}

export async function getStudent(roll) {
  const res = await fetch(`${API}/student/${encodeURIComponent(roll)}`);
  return res.json();
}

export async function getMerit() {
  const res = await fetch(`${API}/merit`);
  return res.json();
}

export async function initSample() {
  const res = await fetch(`${API}/init-sample`, { method: 'POST' });
  return res.json();
}
