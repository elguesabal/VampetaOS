const ws = new WebSocket(`ws://${window.location.host}/webterminal`);

ws.onopen = () => {
	console.log("WebSocket: Connected");
};

ws.onmessage = (event) => {
	console.log("Server:", event.data);
};

ws.onerror = (error) => {
	console.error("WebSocket Error:", error);
};

ws.onclose = () => {
	console.log("WebSocket: Disconnected");
};