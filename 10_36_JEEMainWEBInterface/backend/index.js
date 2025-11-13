// server.js - JEES backend (Express + SQLite)
const express = require('express');
const sqlite3 = require('sqlite3').verbose();
const bodyParser = require('body-parser');
const cors = require('cors');
const path = require('path');

const DB_FILE = path.join(__dirname, 'jees.db');
const db = new sqlite3.Database(DB_FILE);

const app = express();
app.use(cors());
app.use(bodyParser.json());

// Initialize DB tables
db.serialize(() => {
  db.run(`CREATE TABLE IF NOT EXISTS students (
    roll TEXT PRIMARY KEY,
    name TEXT NOT NULL,
    category TEXT NOT NULL,
    math INTEGER,
    phy INTEGER,
    chem INTEGER
  );`);
  db.run(`CREATE TABLE IF NOT EXISTS meta (k TEXT PRIMARY KEY, v TEXT);`);
  // ensure last_seq exists
  db.get("SELECT v FROM meta WHERE k='last_seq'", (err, row) => {
    if (!row) db.run("INSERT INTO meta(k,v) VALUES ('last_seq','0')");
  });
});

/* Utility functions */
function nextSequence() {
  return new Promise((resolve, reject) => {
    db.get("SELECT v FROM meta WHERE k='last_seq'", (err, row) => {
      if (err) return reject(err);
      let seq = parseInt(row.v || "0", 10) + 1;
      db.run("UPDATE meta SET v=? WHERE k='last_seq'", [String(seq)], (uerr) => {
        if (uerr) return reject(uerr);
        resolve(seq);
      });
    });
  });
}

function generateRoll(category, seq) {
  const prefix = (category === 'Gen') ? 'G' : 'R';
  return prefix + String(seq).padStart(5, '0');
}

/* Routes */

// Health
app.get('/api/ping', (req, res) => res.json({ ok: true }));

// Register student
app.post('/api/register', async (req, res) => {
  try {
    const { name, category } = req.body;
    if (!name || !category) return res.status(400).json({ error: 'name and category required' });
    const seq = await nextSequence();
    const roll = generateRoll(category, seq);
    db.run("INSERT INTO students(roll,name,category) VALUES(?,?,?)", [roll, name, category], function(err) {
      if (err) return res.status(500).json({ error: err.message });
      res.json({ roll, name, category });
    });
  } catch (e) {
    res.status(500).json({ error: e.message });
  }
});

// Update marks (staff)
app.post('/api/staff/update', (req, res) => {
  const { roll, math, phy, chem } = req.body;
  if (!roll) return res.status(400).json({ error: 'roll required' });
  // Validate numeric marks (0..200)
  const validMark = m => Number.isInteger(m) && m >= 0 && m <= 200;
  if (![math, phy, chem].every(validMark)) return res.status(400).json({ error: 'marks must be integers 0..200' });
  db.get("SELECT roll FROM students WHERE roll=?", [roll], (err,row) => {
    if (err) return res.status(500).json({ error: err.message });
    if (!row) return res.status(404).json({ error: 'roll not found' });
    db.run("UPDATE students SET math=?,phy=?,chem=? WHERE roll=?", [math,phy,chem,roll], function(uerr) {
      if (uerr) return res.status(500).json({ error: uerr.message });
      res.json({ ok:true, roll });
    });
  });
});

// Get single student
app.get('/api/student/:roll', (req, res) => {
  const roll = req.params.roll;
  db.get("SELECT roll,name,category,math,phy,chem FROM students WHERE roll=?", [roll], (err,row) => {
    if (err) return res.status(500).json({ error: err.message });
    if (!row) return res.status(404).json({ error: 'not found' });
    res.json(row);
  });
});

// Merit list: only students with all marks present; order by total desc, math desc, phy desc
app.get('/api/merit', (req, res) => {
  db.all(`SELECT roll,name,category,math,phy,chem,
      (math+phy+chem) as total
      FROM students
      WHERE math IS NOT NULL AND phy IS NOT NULL AND chem IS NOT NULL
      ORDER BY total DESC, math DESC, phy DESC`, [], (err, rows) => {
    if (err) return res.status(500).json({ error: err.message });
    res.json(rows);
  });
});

// List all students (admin/debug)
app.get('/api/students', (req, res) => {
  db.all("SELECT roll,name,category,math,phy,chem FROM students ORDER BY roll", [], (err, rows) => {
    if (err) return res.status(500).json({ error: err.message });
    res.json(rows);
  });
});

/* Initialize sample data endpoint (optional) */
app.post('/api/init-sample', async (req, res) => {
  const sample = [
    { name: 'Amit Kumar', category: 'Gen', math:85, phy:90, chem:80 },
    { name: 'Neha Sharma', category: 'Gen', math:92, phy:85, chem:88 },
    { name: 'Arjun Das', category: 'Resrv', math:78, phy:75, chem:80 },
    { name: 'Sonia Patel', category: 'Resrv', math:88, phy:82, chem:79 },
    { name: 'Rahul Singh', category: 'Gen', math:95, phy:91, chem:92 }
  ];
  try {
    for (const s of sample) {
      const seq = await nextSequence();
      const roll = generateRoll(s.category, seq);
      await new Promise((res, rej) => {
        db.run("INSERT INTO students(roll,name,category,math,phy,chem) VALUES(?,?,?,?,?,?)",
          [roll,s.name,s.category,s.math,s.phy,s.chem], err => err ? rej(err) : res());
      });
    }
    res.json({ ok:true });
  } catch (e) {
    res.status(500).json({ error: e.message });
  }
});

const PORT = 3002;
app.listen(PORT, () => console.log(`JEES backend running at http://localhost:${PORT}`));
