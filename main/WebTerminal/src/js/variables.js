const terminal = document.getElementById("terminal");
const input = document.getElementById("input");
const ws = new WebSocket(`ws://${window.location.host}/webterminal`);
let history = [];
let posHistory = history.length;
let currentCommand = "";