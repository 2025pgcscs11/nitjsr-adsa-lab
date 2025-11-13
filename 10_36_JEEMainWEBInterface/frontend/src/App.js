import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
import './index.css';
import Register from './components/Register';
import Staff from './components/Staff';
import StudentView from './components/StudentView';
import Merit from './components/Merit';

function NavBar() {
  return (
    <nav className="navbar navbar-expand-lg navbar-light bg-white mb-3">
      <div className="container-fluid app-container">
        <a className="navbar-brand" href="/">JEES</a>
        <div className="navbar-nav">
          <a className="nav-link" href="#register">Register</a>
          <a className="nav-link" href="#staff">Staff</a>
          <a className="nav-link" href="#student">Student</a>
          <a className="nav-link" href="#merit">Merit</a>
        </div>
      </div>
    </nav>
  );
}

function App() {
  return (
    <div>
      <NavBar />
      <div className="container app-container">
        <section id="register" className="mb-4"><Register /></section>
        <hr />
        <section id="staff" className="mb-4"><Staff /></section>
        <hr />
        <section id="student" className="mb-4"><StudentView /></section>
        <hr />
        <section id="merit" className="mb-4"><Merit /></section>
        <div className="footer">JEES — JEE Examination System UI</div>
      </div>
    </div>
  );
}

export default App;
